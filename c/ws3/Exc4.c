#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/***************************
 Exercise:  WS3
 Date: 	    05/08/25
 Developer: Baruch Haimson
 Reviewer:  
 Status:    Approved
***************************/
char **copy_env(char **envp) 
{
    int count = 0;
    char **p = envp;
    while (*p++)
    { 
        count++;
    }

    char **copy = malloc((count + 1) * sizeof(char *));
    if (!copy) 
    {
        return NULL;
    }

    char **dest = copy;
    p = envp;
    while (*p) 
    {
        *dest = strdup(*p); 
        dest++;
        p++;
    }
    
    *dest = NULL;
    return copy;

}

void to_lower_env(char **env) 
{
    for (char **p = env; *p; p++) 
    {
        for (char *s = *p; *s; s++) 
        {
            *s = tolower((unsigned char)*s);
        }
    }
}

void print_env(char **env) 
{
    for (char **p = env; *p; p++) 
    {
        puts(*p);
    }
}

void free_env(char **env) 
{
    char **p = env;
    while (*p) 
    {
        free(*p);
        p++;
    }
    free(env);
}

int main(int argc, char **argv, char **envp) 
{
    (void)argc; 
    (void)argv;
    char **env_copy = copy_env(envp);
    if (!env_copy) 
    {
    	printf("Memory allocation failed\n");
        return 1;
    }
    to_lower_env(env_copy);
    print_env(env_copy);
    free_env(env_copy);

    return 0;
}

