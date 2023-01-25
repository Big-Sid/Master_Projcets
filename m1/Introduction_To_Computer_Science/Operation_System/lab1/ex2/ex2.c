#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/stat.h>

void message_1(int sig);
void message_2(int sig);


int main(void) {
    const int SIZE = 4096;
    const int STD_SIZE = 1024;
    const char *name = "OS";
    int shm_fd;
    char *ptr;
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    if (shm_fd < 0) {
        perror("sham_fd is error");
        return 1;
    }
    ftruncate(shm_fd, SIZE);
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork Failed");
        return 1;
    } else if (pid > 0) //parents
    {
        signal(SIGUSR2, message_2);
        while (1) {
            int loop =1;
            strcpy(ptr,"");
            printf("Now let's chat with 2 and type 0 lonely to finish your message! \n");

            do {
                fgets(ptr+strlen(ptr),STD_SIZE,stdin);
                scanf("%d",&loop);
            }while(loop);
            kill(pid, SIGUSR1);
            pause();
            printf("Read the Message from 2 : %s",ptr);
            if ('^' == ptr[0]) {
                kill(pid, SIGUSR1);
                break;
            }
        }
    } else // child
    {
        pid_t parent_id = getppid();
        signal(SIGUSR1, message_1);
        int len;
        while (1) {
            pause();
            printf("Read the Message from 1 : %s",ptr);
            printf("\n");
            strcpy(ptr,"");
            printf("Now let's chat with 1 and type 0 lonely to finish your message! \n");
            int loop = 1;
            do {
                fgets(ptr+strlen(ptr),STD_SIZE,stdin);
                scanf("%d",&loop);
            }while(loop);
            kill(parent_id, SIGUSR2);
            if ('^' == ptr[0]) {
                kill(parent_id, SIGUSR2);
                break;
            }
        }
        return 0;
    }
}
    void message_1(int sig)
    {
        if(SIGUSR1 == sig)
        {
            printf("1 have sent the messages\n");

        }
    }
    void message_2(int sig)
    {
        if(SIGUSR2 == sig)
        {
            printf("2 have sent the messages\n");
        }

    }

