#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

volatile sig_atomic_t got_signal = 0;
volatile sig_atomic_t ping_pid = 0;

void sigPong(int sig , siginfo_t* info, void* uncontext) 
{ 
    (void)uncontext;
	got_signal = 1;
	ping_pid = (sig_atomic_t)info->si_pid;

}

int main(int argc, char* argv[]) 
{
    pid_t ping_pid = 0;
    time_t start = time(NULL);
    struct sigaction sa = {0};

    if (argc < 2) 
    {
        fprintf(stderr, "Usage: %s <ping_pid>\n", argv[0]);
        return 1;
    }

    ping_pid = (pid_t)atoi(argv[1]);

    sa.sa_sigaction = sigPong;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO; 

    if (-1 == sigaction(SIGUSR2, &sa, NULL))
	{
	    perror("sigaction pong");
	    return 1;
	}
            
    kill(ping_pid, SIGUSR1);

    while (time(NULL) - start < 20)
	{
        while (!got_signal && time(NULL) - start < 20)
        {
            pause();
            sleep(1);
            printf("Pong received SIGUSR2, sending SIGUSR1\n");
            got_signal = 0;
            kill(ping_pid, SIGUSR1);
        }
    }
    kill(ping_pid, SIGTERM);	
    return 0;
}
