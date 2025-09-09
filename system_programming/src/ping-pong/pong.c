#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t got_signal = 0;

void handler(int sig) 
{ 
    got_signal = sig; 
}

int main() 
{
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGUSR1, &sa, NULL);

    pid_t parent_pid = getppid();

    while (1) 
    {
        pause();
        if (got_signal == SIGUSR1) 
        {
            printf("Pong received SIGUSR1, sending SIGUSR2\n");
            kill(parent_pid, SIGUSR2);
            got_signal = 0;
        }
    }
}
