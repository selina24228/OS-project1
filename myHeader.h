#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

#define err_sys(a){perror(a);exit(0);}
#define MAXTASK 1000

struct timespec getTime(void);
int setCPU(void);

typedef struct node{
	pid_t pid;
	int priority;
}Node;
typedef struct queue{
	Node task[MAXTASK];
	int n;
}Queue;

Queue* initQue(void);
int isEmpty(Queue que);
pid_t pop(Queue que);
void push(Node pid,Queue* que);
void heapifly_min(int n,Queue* que);
void heapifly_max(int n,Queue* que);

