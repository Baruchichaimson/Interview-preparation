#define _GNU_SOURCE
#include "ext2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BASE_OFFSET 1024


struct ext2_super_block {
    uint32_t s_inodes_count;
    uint32_t s_blocks_count;
    uint32_t s_r_blocks_count;
    uint32_t s_free_blocks_count;
    uint32_t s_free_inodes_count;
    uint32_t s_first_data_block;
    uint32_t s_log_block_size;
    uint32_t s_log_frag_size;
    uint32_t s_blocks_per_group;
    uint32_t s_frags_per_group;
    uint32_t s_inodes_per_group;
    uint32_t s_mtime;
    uint32_t s_wtime;
    uint16_t s_mnt_count;
    uint16_t s_max_mnt_count;
    uint16_t s_magic;
    uint16_t s_state;
    uint16_t s_errors;
    uint16_t s_minor_rev_level;
    uint32_t s_lastcheck;
    uint32_t s_checkinterval;
    uint32_t s_creator_os;
    uint32_t s_rev_level;
    uint16_t s_def_resuid;
    uint16_t s_def_resgid;
    uint32_t s_first_ino;
    uint16_t s_inode_size;
    uint16_t s_block_group_nr;
    uint32_t s_feature_compat;
    uint32_t s_feature_incompat;
    uint32_t s_feature_ro_compat;
    uint8_t  s_uuid[16];
    char     s_volume_name[16];
    char     s_last_mounted[64];
    uint32_t s_algorithm_usage_bitmap;
} __attribute__((packed));

struct ext2_group_desc {
    uint32_t bg_block_bitmap;
    uint32_t bg_inode_bitmap;
    uint32_t bg_inode_table;
    uint16_t bg_free_blocks_count;
    uint16_t bg_free_inodes_count;
    uint16_t bg_used_dirs_count;
    uint16_t bg_pad;
    uint8_t  bg_reserved[12];
} __attribute__((packed));

struct ext2_inode {
    uint16_t i_mode;
    uint16_t i_uid;
    uint32_t i_size;
    uint32_t i_atime;
    uint32_t i_ctime;
    uint32_t i_mtime;
    uint32_t i_dtime;
    uint16_t i_gid;
    uint16_t i_links_count;
    uint32_t i_blocks;
    uint32_t i_flags;
    uint32_t i_osd1;
    uint32_t i_block[15]; 
    uint32_t i_generation;
    uint32_t i_file_acl;
    uint32_t i_dir_acl;
    uint32_t i_faddr;
    uint8_t  i_osd2[12];
} __attribute__((packed));

struct ext2_dir_entry_2 {
    uint32_t inode;
    uint16_t rec_len;
    uint8_t  name_len;
    uint8_t  file_type;
    char     name[]; 
} __attribute__((packed));

struct ext2_fs {
    int fd;
    char *device_path;
    struct ext2_super_block sb;
    uint32_t block_size;
    uint32_t groups_count;
    struct ext2_group_desc *group_desc; 
};

static ssize_t pread_retry(int fd, void *buf, size_t count, off_t offset) 
{
    ssize_t r;
    size_t got = 0;
    char *p = buf;
    while (got < count) 
    {
        r = pread(fd, p + got, count - got, offset + got);
        if (r < 0) 
        {
            if (errno == EINTR) continue;
            return -1;
        }
        if (r == 0) break;
        got += r;
    }
    return got;
}

static uint32_t compute_block_size(const struct ext2_super_block *sb) 
{
    return 1024u << sb->s_log_block_size;
}

static uint32_t compute_groups_count(const struct ext2_super_block *sb) 
{
    uint32_t inodes = sb->s_inodes_count;
    uint32_t per = sb->s_inodes_per_group;
    return (inodes + per - 1) / per;
}

ext2_fs_t *ext2_open(const char *device_path) 
{
    ext2_fs_t *fs = calloc(1, sizeof(*fs));
    if (!fs) return NULL;
    fs->device_path = strdup(device_path);
    fs->fd = open(device_path, O_RDONLY);
    if (fs->fd < 0) 
    {
        perror("open device");
        free(fs->device_path);
        free(fs);
        return NULL;
    }

    if (pread_retry(fs->fd, &fs->sb, sizeof(fs->sb), BASE_OFFSET) != sizeof(fs->sb)) 
    {
        perror("read superblock");
        close(fs->fd);
        free(fs->device_path);
        free(fs);
        return NULL;
    }
    fs->block_size = compute_block_size(&fs->sb);
    fs->groups_count = compute_groups_count(&fs->sb);

    size_t gd_table_size = fs->groups_count * sizeof(struct ext2_group_desc);

    
    uint32_t gd_start_block = fs->sb.s_first_data_block + 1;
    off_t gd_offset = (off_t)gd_start_block * fs->block_size;
   

    fs->group_desc = malloc(gd_table_size);
    if (!fs->group_desc) {
        perror("malloc group_desc");
        close(fs->fd);
        free(fs->device_path);
        free(fs);
        return NULL;
    }
    if (pread_retry(fs->fd, fs->group_desc, gd_table_size, gd_offset) != (ssize_t)gd_table_size) {
        off_t alt = BASE_OFFSET + fs->block_size;
        if (pread_retry(fs->fd, fs->group_desc, gd_table_size, alt) != (ssize_t)gd_table_size) {
            perror("read group descriptor table");
            free(fs->group_desc);
            close(fs->fd);
            free(fs->device_path);
            free(fs);
            return NULL;
        }
    }

    return fs;
}

void ext2_close(ext2_fs_t *fs) {
    if (!fs) return;
    if (fs->fd >= 0) close(fs->fd);
    free(fs->device_path);
    if (fs->group_desc) free(fs->group_desc);
    free(fs);
}

int ext2_read_super(ext2_fs_t *fs, ext2_super_block_t *out) {
    if (!fs || !out) return -1;
    memcpy(out, &fs->sb, sizeof(fs->sb));
    return 0;
}

int ext2_read_group_desc(ext2_fs_t *fs, unsigned int group, ext2_group_desc_t *out) {
    if (!fs || !out) return -1;
    if (group >= fs->groups_count) return -1;
    memcpy(out, &fs->group_desc[group], sizeof(*out));
    return 0;
}

int ext2_read_inode(ext2_fs_t *fs, uint32_t inode_no, ext2_inode_t *out) {
    if (!fs || !out) return -1;
    if (inode_no == 0 || inode_no > fs->sb.s_inodes_count) return -1;

    uint32_t inodes_per_group = fs->sb.s_inodes_per_group;
    uint32_t group = (inode_no - 1) / inodes_per_group;
    uint32_t index = (inode_no - 1) % inodes_per_group;

    if (group >= fs->groups_count) return -1;

    uint32_t inode_table_block = fs->group_desc[group].bg_inode_table;
    uint32_t inode_size = fs->sb.s_inode_size ? fs->sb.s_inode_size : sizeof(struct ext2_inode);
    off_t inode_offset = (off_t)inode_table_block * fs->block_size + (off_t)index * inode_size;

    if (pread_retry(fs->fd, out, inode_size, inode_offset) != (ssize_t)inode_size) {
        perror("pread inode");
        return -1;
    }
    return 0;
}

int ext2_path_resolve(ext2_fs_t *fs, const char *path, uint32_t *inode_no_out) {
    if (!fs || !path || !inode_no_out) return -1;
    if (path[0] != '/') return -1; 

    uint32_t curr_inode = 2;
    if (strcmp(path, "/") == 0) { *inode_no_out = curr_inode; return 0; }

    char *copy = strdup(path);
    if (!copy) return -1;
    char *p = copy;
    char *token;
    if (*p == '/') p++;
    token = strtok(p, "/");
    while (token) {
        struct ext2_inode inode;
        if (ext2_read_inode(fs, curr_inode, &inode) != 0) { free(copy); return -1; }

        if (!(inode.i_mode & 0x4000)) 
        {
            free(copy);
            return -1;
        }

        int found = 0;
        size_t block_size = fs->block_size;
        for (int bi = 0; bi < 12 && inode.i_block[bi] != 0 && !found; ++bi) 
        {
            off_t block_offset = (off_t)inode.i_block[bi] * block_size;
            uint8_t *block = malloc(block_size);
            if (!block) 
            { 
                free(copy); 
                return -1; 
            }
            if (pread_retry(fs->fd, block, block_size, block_offset) != (ssize_t)block_size) 
            {
                free(block);
                free(copy);
                return -1;
            }
            size_t off = 0;
            while (off < block_size) 
            {
                struct ext2_dir_entry_2 *de = (struct ext2_dir_entry_2 *)(block + off);
                if (de->inode != 0) {
                    int name_len = de->name_len;
                    char name[256];
                    if (name_len > 255) name_len = 255;
                    memcpy(name, (char*)de->name, name_len);
                    name[name_len] = '\0';
                    if (strncmp(name, token, 255) == 0) {
                        curr_inode = de->inode;
                        found = 1;
                        break;
                    }
                }
                if (de->rec_len < 4) break; 
                off += de->rec_len;
            }
            free(block);
        }
        if (!found) {
            free(copy);
            return -1; 
        }
        token = strtok(NULL, "/");
    }

    free(copy);
    *inode_no_out = curr_inode;
    return 0;
}

ssize_t ext2_read_file_direct(ext2_fs_t *fs, uint32_t inode_no, void *buf, size_t max_bytes) 
{
    if (!fs || !buf) return -1;
    struct ext2_inode inode;
    if (ext2_read_inode(fs, inode_no, &inode) != 0) return -1;

    size_t to_read = inode.i_size;
    if (to_read > max_bytes) to_read = max_bytes;

    size_t block_size = fs->block_size;
    size_t total_read = 0;
    for (int bi = 0; bi < 12 && total_read < to_read; ++bi) 
    {
        uint32_t b = inode.i_block[bi];
        if (b == 0) break;
        off_t off = (off_t)b * block_size;
        size_t need = to_read - total_read;
        size_t read_len = need < block_size ? need : block_size;
        if (pread_retry(fs->fd, (char*)buf + total_read, read_len, off) != (ssize_t)read_len) 
        {
            ssize_t rr = pread(fs->fd, (char*)buf + total_read, read_len, off);
            if (rr <= 0) break;
            total_read += rr;
            break;
        }
        total_read += read_len;
    }
    return (ssize_t)total_read;
}

void ext2_print_summary(ext2_fs_t *fs) {
    if (!fs) return;
    struct ext2_super_block *sb = &fs->sb;
    printf("SUPERBLOCK:\n");
    printf("  inodes_count: %u\n", sb->s_inodes_count);
    printf("  blocks_count: %u\n", sb->s_blocks_count);
    printf("  first_data_block: %u\n", sb->s_first_data_block);
    printf("  log_block_size: %u (block size %u)\n", sb->s_log_block_size, fs->block_size);
    printf("  inodes_per_group: %u\n", sb->s_inodes_per_group);
    printf("  inode_size: %u\n", sb->s_inode_size);
    printf("GROUPS: %u\n", fs->groups_count);
    if (fs->groups_count > 0) {
        struct ext2_group_desc *gd = &fs->group_desc[0];
        printf("GROUP 0 descriptor:\n");
        printf("  block bitmap: %u\n", gd->bg_block_bitmap);
        printf("  inode bitmap: %u\n", gd->bg_inode_bitmap);
        printf("  inode table: %u\n", gd->bg_inode_table);
    }
}
