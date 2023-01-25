#include "pid.h"

int main()
{
    allocate_map();
    int get_pid = allocate_pid();
    release_pid(get_pid);
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
        printf("allocate pid successful, PID = %d\n",pid);
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
    printf("Successful release of pid = %d \n",p_r);
}

int random_number(void)
{
    srand((unsigned)time(NULL));
    int temp_pid = rand()%4700+301;
    return temp_pid;
}