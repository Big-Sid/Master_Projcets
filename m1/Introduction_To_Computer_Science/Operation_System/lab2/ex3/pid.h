#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#define MIN_PID 300
#define MAX_PID 5000


int pid_map[4700];
int pid;
int count;
pthread_mutex_t lock;


int allocate_map(void);
int allocate_pid(void);
void release_pid(int pid);
void *t_process(void *arg);
int random_number(void);