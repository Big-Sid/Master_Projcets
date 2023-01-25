#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MIN_PID 300
#define MAX_PID 5000

int pid_map[4700];
int pid;

// You can declare other important variables and/or structures here

int allocate_map(void);
int allocate_pid(void);
void release_pid(int pid);
int random_number(void);