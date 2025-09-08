#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

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

    sigaction(SIGUSR2, &sa, NULL);

    pid_t pid = fork();
    if (pid == 0) 
    {
        execl("./b.out", "pong", NULL);
        perror("exec failed");
        exit(1);
    }

    sleep(1);
    
    kill(pid, SIGUSR1);

    while (time) 
    {
        pause();
        if (got_signal == SIGUSR2) 
        {
            printf("Ping received SIGUSR2, sending SIGUSR1\n");
            kill(pid, SIGUSR1);
            got_signal = 0;
        }
        time--;
    }
}
