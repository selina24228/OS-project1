#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

#define err_sys(a){perror(a);exit(0);}
#define MAXTASK 1000

struct timespec getTime(void);


typedef struct queue{
	pid_t task[MAXTASK];
	int n;
}Queue;

void initQue(Queue* que);
int isEmpty(Queue que);
pid_t pop(Queue que);
void push(pid_t pid,Queue que);

