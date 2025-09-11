#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>

sem_t *sem = NULL;
const char *sem_name = NULL;
ssize_t undo_delta = 0; 
int undo_used = 0;

/* -------------------- Undo Handler -------------------- */
void undo_handler(void) 
{
    int sval = 0;
    ssize_t i = 0;

    if (sem && undo_used)
    {
        sem_getvalue(sem, &sval);

        if (0 < undo_delta) 
        {
            for (i = 0; i < undo_delta; i++)
            {
                sem_wait(sem);
            }
        } 
        else if(0 > undo_delta)
        {
            for (i = 0; i < -undo_delta; i++)
            {
                sem_post(sem);
            }
        }
        printf("UNDO applied: semaphore restored by %ld\n", undo_delta);
    }

    if (sem)
    {
        sem_close(sem);
        sem = NULL;
    }
}

/* -------------------- Main -------------------- */
int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        printf("add a semaphore name!\n");
        return 1;
    }

    sem_name = argv[1];

    atexit(undo_handler);  

    sem = sem_open(sem_name, O_CREAT, 0644, 0);
    if (sem == SEM_FAILED) 
    {
        perror("sem_open");
        return 1;
    }

    char line[256];
    while (1) 
    {
        printf("semaphore by baruchi :) > ");

        fflush(stdout);

        if (!fgets(line, sizeof(line), stdin))
            break;

        char cmd;
        int num = 0;
        char undo_str[16] = {0};

        int args = sscanf(line, "%c %d %s", &cmd, &num, undo_str);

        int undo = (args == 3 && strcmp(undo_str, "undo") == 0);

        if (cmd == 'X')
            break;
        else if (cmd == 'V')
        {
            int sval;
            if (sem_getvalue(sem, &sval) == -1)
                perror("sem_getvalue");
            else
                printf("Semaphore value: %d\n", sval);
        }
        else if ((cmd == 'D' || cmd == 'I') && args >= 2)
        {
            if (cmd == 'D')
            {
                for (int i = 0; i < num; i++)
                    sem_wait(sem);

                if (undo)
                {
                    undo_delta -= num;  
                    undo_used = 1;
                }
            }
            else if (cmd == 'I')
            {
                for (int i = 0; i < num; i++)
                    sem_post(sem);

                if (undo)
                {
                    undo_delta += num;  
                    undo_used = 1;
                }
            }

            printf("%c %d executed%s\n", cmd, num, undo ? " with undo" : "");
        }
        else
        {
            printf("Invalid command\n");
        }
    }

    return 0;
}
