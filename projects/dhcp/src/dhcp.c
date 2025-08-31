/************************************
 * Exercise: DHCP server
 * Date: 27/08/25
 * Developer: Baruch Haimson
 * Reviewer: Avi
 * Status: In Progress
 ************************************/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <string.h>

#include "dhcp.h" /* dhcp_t */
#include "trie.h" /* TrieCreate */

struct dhcp
{
    trie_t *trie;
    unsigned int net_ip;
    size_t mask;
};

#define BITS (32)

/* ================ helper functions ======================================= */

static unsigned int BytesToUInt(const unsigned char ip[BYTES_IN_IPV4]);
static void UIntToBytes(unsigned int ip, unsigned char out[BYTES_IN_IPV4]);
static unsigned int MaskToUInt(size_t mask);
static unsigned int NetworkAddress(unsigned int ip, size_t mask);

/* ========================================================================== */

dhcp_t* DHCPCreate(const unsigned char netip[BYTES_IN_IPV4], size_t mask)
{
    dhcp_t *dhcp;
    unsigned int dummy = 0;
    unsigned int subnet_bits = BITS - mask;
    unsigned int broadcast_host;
    
    dhcp = (dhcp_t*)malloc(sizeof(dhcp_t));
    if (!dhcp) 
    {
        return NULL;
    }
    
    dhcp->trie = TrieCreate(subnet_bits);
    if (!dhcp->trie)
    {
        free(dhcp);
        return NULL;
    }
    
    dhcp->mask = mask;
    dhcp->net_ip = NetworkAddress(BytesToUInt(netip), mask);
    
    /* Reserve network address (0) */
    TrieInsert(dhcp->trie, 0, &dummy);
    
    broadcast_host = (1U << subnet_bits) - 1;

    /* Reserve second-to-last address (254 for /24) */
    TrieInsert(dhcp->trie, broadcast_host - 1, &dummy);
    
    /* Reserve broadcast address (255 for /24) */
    TrieInsert(dhcp->trie, broadcast_host, &dummy);
    
    return dhcp;
}

void DHCPDestroy(dhcp_t* dhcp)
{
    assert(dhcp);
   
    TrieDestroy(dhcp->trie);
    free(dhcp);
}

dhcp_status_e DHCPAllocateIP(dhcp_t* dhcp, unsigned char allocated_ip[BYTES_IN_IPV4], const unsigned char requested_ip[BYTES_IN_IPV4])
{
    unsigned int subnet_bits = 0;
    unsigned int broadcast_host = 0;
    unsigned int host_part = 0;
    unsigned int alloc_host = 0;
    unsigned int req_ip = 0;
    unsigned int netaddr = 0;
    int is_zero_request = 0;
    /*unsigned int i = 1;*/
    unsigned char zero[BYTES_IN_IPV4] = {0, 0, 0, 0};

    assert(dhcp);

    subnet_bits = BITS - dhcp->mask;
    broadcast_host = (1U << subnet_bits) - 1;
    
    is_zero_request = (memcmp(requested_ip, zero, BYTES_IN_IPV4) == 0);
    
    if (is_zero_request)
    {
        for (host_part = 1; host_part < broadcast_host - 1; ++host_part)
        {
            if (TrieInsert(dhcp->trie, host_part, &alloc_host))
            {
                UIntToBytes(dhcp->net_ip | host_part, allocated_ip);
                return SUCCESS;
            }
        }
        return NO_IP_AVAILABLE;
    }
    
    req_ip = BytesToUInt(requested_ip);
    netaddr = NetworkAddress(req_ip, dhcp->mask);
    host_part = req_ip & broadcast_host;
    
    if (netaddr != dhcp->net_ip)
    {
        return NO_IP_AVAILABLE;
    }
    
    if (host_part == 0 || host_part == broadcast_host - 1 || host_part == broadcast_host)
    {
        for (host_part = 1; host_part < broadcast_host - 1; ++host_part)
        {
            if (TrieInsert(dhcp->trie, host_part, &alloc_host))
            {
                UIntToBytes(dhcp->net_ip | host_part, allocated_ip);
                return IP_OCCUPIED_ALLOCATED_ANOTHER;
            }
        }
        return NO_IP_AVAILABLE;
    }
    
    if (TrieInsert(dhcp->trie, host_part, &alloc_host))
    {
        UIntToBytes(dhcp->net_ip | host_part, allocated_ip);
        return SUCCESS;
    }
    
    for (host_part = host_part + 1; host_part < broadcast_host - 1; ++host_part)
    {
        if (TrieInsert(dhcp->trie, host_part, &alloc_host))
        {
            UIntToBytes(dhcp->net_ip | host_part, allocated_ip);
            return IP_OCCUPIED_ALLOCATED_ANOTHER;
        }
    }
    
    /*host_part = req_ip & broadcast_host;
    for (i = 1; i < host_part; ++i)
    {
        if (TrieInsert(dhcp->trie, i, &alloc_host))
        {
            UIntToBytes(dhcp->net_ip | i, allocated_ip);
            return IP_OCCUPIED_ALLOCATED_ANOTHER;
        }
    }*/
    
    return NO_IP_AVAILABLE;
}

dhcp_status_e DHCPFreeIP(dhcp_t* dhcp, const unsigned char ip[BYTES_IN_IPV4])
{
    unsigned int ip_num = 0;
    unsigned int host_part = 0;
    unsigned int netaddr = 0;
    unsigned int subnet_bits = 0;
    unsigned int broadcast_host = 0;
    
    assert(dhcp);
    
    subnet_bits = BITS - dhcp->mask;
    ip_num = BytesToUInt(ip);
    netaddr = NetworkAddress(ip_num, dhcp->mask);
    host_part = ip_num & ((1U << subnet_bits) - 1);
    
    broadcast_host = (1U << subnet_bits) - 1;

    if (netaddr != dhcp->net_ip)
    {
        return IP_NOT_FOUND;
    }

    if (host_part == 0 || host_part == broadcast_host - 1 || host_part == broadcast_host)
    {
        abort();
    }
    
    if (!TrieRemove(dhcp->trie, host_part))
    {
        return DOUBLE_FREE; 
    } 

    return SUCCESS;
}

size_t DHCPCountFree(const dhcp_t* dhcp)
{
    assert(dhcp);

    return TrieCountFree(dhcp->trie);
}

/* ================ helper functions ======================================= */

static unsigned int BytesToUInt(const unsigned char ip[BYTES_IN_IPV4])
{
    return ((unsigned int)ip[0] << 24) |
           ((unsigned int)ip[1] << 16) |
           ((unsigned int)ip[2] << 8) |
           ((unsigned int)ip[3]);
}

static void UIntToBytes(unsigned int ip, unsigned char out[BYTES_IN_IPV4])
{
    out[0] = (unsigned char)((ip >> 24) & 0xFF);
    out[1] = (unsigned char)((ip >> 16) & 0xFF);
    out[2] = (unsigned char)((ip >> 8) & 0xFF);
    out[3] = (unsigned char)(ip & 0xFF);
}

static unsigned int MaskToUInt(size_t mask)
{
    if (mask == 0) return 0;
    return (~0U << (BITS - mask));
}

static unsigned int NetworkAddress(unsigned int ip, size_t mask)
{
    return ip & MaskToUInt(mask);
}