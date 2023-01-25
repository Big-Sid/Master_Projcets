#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAX_LINE 1024 /* The maximum length command */
#define MAX_ARGS 128 /* The maximum number of arguments */
static char line[MAX_LINE];
int is_at[1];
char history[10][20];
void initial_history(void);
void update_history(void);
void display_h(void);


int main(void) {
    char *args[MAX_ARGS]; /* command line arguments */
    int should_run = 1; /* flag to determine when to exit program */
    initial_history();
    while (should_run) {
        is_at[0]=0;
        *args=NULL;
        printf("lldm>");
        fflush(stdout);
        /* Read a command line */
        if (!fgets(line, 1024, stdin))
        {
            return 0;
        }
        if(strcmp(line,"history\n")!=0)
        {
            update_history();
            strcpy(history[0],line);
        }
        unsigned long length = strlen(line)-1;
        if(line[length-1] =='&')
        {
            is_at[0]=1;
                line[length-1]='\0';
            if(line[length-2]==' ')
            {
                line[length-2]='\0';
            }
        }
        if (strcmp(line, "exit\n") == 0) {
            should_run = 0;
        }
        if(strcmp(line, "history\n") == 0)
        {
            if(strcmp(history[0],"\0")==0)
            {
                printf("No history now\n");
            }
            else
            {
                display_h();
            }

        }
        else
        {
            pid_t pid;
            pid = fork();
            if(pid< 0)
            {
                fprintf(stderr,"Fork Failed");
                return 1;
            }
            else if(pid == 0) //child
            {
                int count =0;
                for(int i = 0; i < strlen(line);i++)
                {
                    if(line[i]==32)
                    {
                        count++;
                    }
                }
               if(count == 0 && is_at[0]==0)
               {
                    line[strlen(line)-1] = '\0';
               }
                args[0] = strtok(line," ");
                int i;
                for(i = 1; i<=count; i++)
                {
                    if(i == count)
                    {
                        args[i] = strtok(NULL," \n");
                    }
                    else
                    {
                        args[i] = strtok(NULL," ");
                    }
                }
                if(execvp(args[0],args) == -1)
                {
                    printf("\n Something went wrong :(...\n");
                    exit(0);
                }
                exit(0);
            }
            else if(pid == 1)//parent
            {
               if(is_at[0]==1)
               {
                    wait(NULL);
               }
            }
        }
    }
    return 0;
}

void initial_history(void)
{
    for(int i = 0; i<=9 ; i++)
    {
        strcpy(history[i],"\0");
    }
}

void update_history(void)
{
    for(int i = 9; i >=0 ; --i)
    {
        strcpy(history[i],history[i-1]);
    }
}

void display_h(void)
{
    printf("Here is the history record from the most recent:\n");
    for(int i =0; i <=9 ;i++)
    {
        if(strcmp(history[i],"\0")!=0)
        {
            printf("%d: %s",i+1,history[i]);
        }
    }
}
