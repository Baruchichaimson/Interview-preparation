#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

pid_t child_pid;
pid_t parent_pid;

volatile sig_atomic_t got_signal = 0;

void handler(int sig) 
{
    got_signal = sig;
}

int main() 
{
    int time = 5;

    struct sigaction sa;

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    parent_pid = getpid();

    child_pid = fork();
    if (child_pid < 0) 
    {
        perror("fork failed");
        exit(1);
    }

    if (child_pid == 0) 
    {
        while (time) 
        {
            pause(); 
            if (got_signal == SIGUSR1) 
            {
                printf("\n-> child received SIGUSR1, sending SIGUSR2 to parent ->\n");
                kill(parent_pid, SIGUSR2);
                got_signal = 0;
            }
            time--;
        }
    } 
    else 
    {
        sleep(1); 
        printf("Parent sending SIGUSR1 to child\n");
        kill(child_pid, SIGUSR1);

        while (time) 
        {
            pause();
            if (got_signal == SIGUSR2) 
            {
                printf("\n<- parent received SIGUSR2, sending SIGUSR1 to child <-\n");
                kill(child_pid, SIGUSR1);
                got_signal = 0;
            }
            time--;
        }
    }
}
