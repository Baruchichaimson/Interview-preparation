#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

volatile sig_atomic_t got_signal = 0;
volatile sig_atomic_t pong_pid = 0;

void sigPing(int sig , siginfo_t* info, void* uncontext) 
{ 
    (void)uncontext;
	got_signal = 1;
	pong_pid = (sig_atomic_t)info->si_pid;

}

int main() 
{
    struct sigaction sa = {0};

    printf("Ping PID: %d\n", getpid());

    sa.sa_sigaction = sigPing;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO; 

    if (-1 == sigaction(SIGUSR1, &sa, NULL))
	{
	    perror("sigaction ping");
	    return 1;
	}	

    while (1)
    {
        while (!got_signal)
        {
            pause();
            sleep(1);
            printf("Ping received SIGUSR1, sending SIGUSR2\n");
            got_signal = 0;
            kill((pid_t)pong_pid, SIGUSR2);		
        }
    }		
    return 0;
}
