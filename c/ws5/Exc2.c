#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

enum status {CORRECT , ERROR , EXIT};

struct CommandHandler
{
    char* keyword;
    int (*match)(char* keyword, const char* input);
    enum status (*action)(const char*, const char*);
};

/***************************************
actions functions
***************************************/
enum status action_add(const char* filename, const char* input) 
{
    FILE* f = fopen(filename, "a");
    if (!f) 
    {
    	perror("Error opening file for add");
    	return ERROR;
    }

    fprintf(f, "%s\n", input);
    fclose(f);
    return CORRECT;
}
enum status action_remove(const char* filename, const char* input) 
{
    if (remove(filename) == 0)
    {
        printf("File deleted.\n");
        return CORRECT;
    }
    else
    {
        perror("Failed to delete file");
        return ERROR;
    }
}

enum status action_count(const char* filename, const char* input) 
{
   int lines = 0;
   char line[SIZE];
   FILE* f = fopen(filename, "r");
   if (!f) 
   {
    	perror("Error opening file for count");
    	return ERROR;
   }
   
   while (fgets(line, sizeof(line), f) != NULL) 
   {
       lines++;
   } 
    
   fclose(f);
   printf("Total lines in file: %d\n", lines);
   return CORRECT;
}

enum status action_prefix(const char* filename, const char* input) 
{
    FILE* f = fopen(filename, "r");
    char existing_content[10000] = "";
    char line[SIZE];
    
    if (f) 
    {
        while (fgets(line, sizeof(line), f) != NULL) 
        {
            strcat(existing_content, line);
    	}
        fclose(f);
    }
    
    f = fopen(filename, "w");
    if (!f) {
        perror("Error opening file for writing");
        return ERROR;
    }
    
    fprintf(f, "%s\n", input + 1); 
    
    fprintf(f, "%s", existing_content);
    
    fclose(f);
    printf("Added prefix line: %s\n", input + 1);
    return CORRECT;
}

enum status action_exit() 
{
    printf("Exiting...\n");
    return EXIT;
}

/***************************************
matches functions
***************************************/
int match_remove(char* keyword, const char* input) 
{
    return strcmp(input, keyword) == 0;
}

int match_count(char* keyword ,const char* input) 
{
    return strcmp(input, keyword) == 0;
}

int match_exit(char* keyword ,const char* input) 
{
    return strcmp(input, keyword) == 0;
}

int match_prefix(char* keyword ,const char* input) 
{
    return strncmp(input, keyword, 1) == 0;
}


int main(int argc, char* argv[]) 
{ 
    enum status result;	
    if (argc < 2) 
    {
    	fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    	return 1;
    }
    const char* filename = argv[1];
    char buffer[SIZE];
    struct CommandHandler handlers[] = 
    {
	{"<", match_prefix, action_prefix},
	{"-remove", match_remove, action_remove},
	{"-count", match_count, action_count},
	{"-exit", match_exit, action_exit},
    };
    
    while (1) 
    {
    	printf("Logger running... Enter string:\n");
        fgets(buffer, sizeof(buffer), stdin);
	buffer[strcspn(buffer, "\n")] = 0;

        if (strlen(buffer) == 0)
        { 
        	break;
        }

        int handled = 0;
        int len = sizeof(handlers) / sizeof(handlers[0]);
        for (int i = 0; i < len; ++i) 
        {
            if(handlers[i].match(handlers[i].keyword , buffer)) 
            {
        	result = handlers[i].action(filename, buffer);
                if (result == ERROR) 
                {
        		fprintf(stderr, "Command failed: %s\n", buffer);
    		}
                handled = 1;
                break;
            }
        }
        if (!handled) 
        {
            result = action_add(filename, buffer);
        }
	switch (result)
	{
		case ERROR:
			fprintf(stderr, "Action failed. Please try again.\n");
			break;
		case EXIT:
			exit(0);
		case CORRECT:
			break;
	}
    }
    return 0;
}
