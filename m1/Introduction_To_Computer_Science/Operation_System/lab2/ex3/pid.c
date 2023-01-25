#include "pid.h"
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

int main()
{
    allocate_map();
    printf("How man threads you want to create ? ");
    scanf("%d",&count);
    if(pthread_mutex_init(&lock,NULL)!=0)
    {
        perror("");
    }
    pthread_t t[count];
    for(int i = 0 ; i < count ; i++)
    {
        pthread_create(t,NULL,t_process,(void*)i);
        sleep(2);
    }
    if(pthread_mutex_destroy(&lock)!=0)
    {
        perror("");
    }
    printf("All good, bye!\n");
}

int allocate_map(void) {
    for(int i = MIN_PID;i <=MAX_PID;i++)
    {
        pid_map[i] = 1;
        if(pid_map[i] != 1)
        {
            printf("allocate map error!\n");
            return -1;
        }
    }
    printf("allocate map successful!\n");
    return 1;
}

int allocate_pid(void) {
    int pid_0 = random_number();
    if(pid_0 <300 || pid_0 >5000)
    {
        printf("allocating error \n");
        return -1;
    }
    if(pid_map[pid_0] == 1)
    {
        pid = pid_0;
        pid_map[pid_0]=0;
        return pid;
    }
    else
    {
        printf("fail to allocate,it is in use\n");
        return -1;
    }
}

void release_pid(int p_r) {
    pid_map[p_r] = 1;
}

void *t_process(void *arg)
{
    int i = (int)arg;
    if(pthread_mutex_lock(&lock)!=0)
    {
        perror("");
    }
    pid = allocate_pid();
    printf("%dth thread with PID = %d \n",i+1,pid);
    sleep(2);
    release_pid(pid);
    if(pthread_mutex_unlock(&lock)!=0)
    {
        perror("");
    }
}

int random_number(void)
{
    srand((unsigned)time(NULL));
    int temp_pid = rand()%4700+301;
    return temp_pid;
}