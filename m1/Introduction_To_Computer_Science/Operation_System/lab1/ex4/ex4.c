#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<pthread.h>

void err(const char *str)
{
        perror(str);
        exit(1);
}

int main()
{
        pid_t pid;
        pid = fork();
        if(pid>0)
        {
                exit(0);
        }

        setsid();
        if(pid == -1)
        {
                err("setsid error");
        }
        int ret = chdir("/home");
        if (ret == -1)
        {
		err("chdir error");
        }

        umask(0022);
        close(STDIN_FILENO);
        int fd =open("/dev/null",O_RDWR);
        if(fd == -1)
        {
                err("open error");
        }
        dup2(fd,STDOUT_FILENO);
        dup2(fd,STDERR_FILENO);

        while(1);
	
	return 0;

}

