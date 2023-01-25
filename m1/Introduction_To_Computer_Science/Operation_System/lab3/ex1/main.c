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


int main(void) {
    char *args[MAX_ARGS]; /* command line arguments */
    int should_run = 1; /* flag to determine when to exit program */
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
        unsigned long length = strlen(line)-1;
        if(line[length-1] =='&')
        {
            is_at[0]=1;
            line[length-1]='\0';
            if(length-2 == ' ')
            {
                line[length-2]='\0';
            }
        }
        if (strcmp(line, "exit\n") == 0) {
            should_run = 0;
        }
        pid_t pid;
        pid = fork();
        if(pid< 0)
        {
            fprintf(stderr,"Fork Failed");
            return 1;
        }
        else if(pid == 0) //child
        {
            int count =0 ;
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
    return 0;
}