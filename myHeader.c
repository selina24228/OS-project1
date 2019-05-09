#include"myHeader.h"
#include<string.h>
#include<linux/time.h>
#define timespec linux_timespec
#include<time.h>
#undef timespec
typedef int assert_same_size[sizeof(struct linux_timespec) == sizeof(timespec) ? 1 : -1];
typedef int assert_same_alignment[__alignof(struct linux_timespec) == __alignof(timespec) ? 1 : -1];
typedef int assert_same_tv_sec[offsetof(struct linux_timespec, tv_sec) == offsetof(struct timespec, tv_sec) ? 1 : -1];
typedef int assert_same_tv_nsec[offsetof(struct linux_timespec, tv_nsec) == offsetof(struct timespec, tv_nsec) ? 1 : -1];
#include<sched.h>
#include<stdlib.h>
#include<assert.h>

struct timespec getTime(void){
	struct timespec time;
	getnstimeofday(&time);
	return time;
}
int setCPU(void){
	cpu_set_t mask;
	CPU_ZERO(&mask);
	CPU_SET(0, &mask);
	return sched_setaffinity(0, sizeof(mask), &mask);
} 
Queue* initQue(void){
	Queue* root=(Queue*)malloc(sizeof(Queue));
	assert(root!=NULL);
	return root; 
}
int isEmpty(Queue que){
	return ((que.n==0)?1:0);
}
pid_t pop(Queue que){
	if(que.n==-1){
		return -1;
	}
	pid_t result=que.task[0].pid;
	que.n-=1;
	que.task[0]=que.task[que.n];
	heapifly_min(0,&que);
	return result;
}
void push(Node pid,Queue* que){
	que->task[que->n]=que->task[0];
	que->task[0]=pid;
	heapifly_min(0,que);
	que->n++;	
}
void heapifly_min(int n,Queue* que){
	int left=2*n;
	int right=2*n+1;
	int min;
	if(que->task[n].priority<que->task[left].priority){
		min=n;
	}
	else min=left;
	if(que->task[min].priority>que->task[right].priority){
		min=right;
	}
	if(min!=n){
		Node tmp=que->task[n];
		que->task[n]=que->task[min];
		que->task[min]=tmp;
		heapifly_min(min,que);
	}
	return;
}
void heapifly_max(int n,Queue* que){
	int left=2*n;
	int right=2*n+1;
	int max;
	if(que->task[n].priority>que->task[left].priority){
		max=n;
	}
	else max=left;
	if(que->task[max].priority<que->task[right].priority){
		max=right;
	}
	if(max!=n){
		Node tmp=que->task[n];
		que->task[n]=que->task[max];
		que->task[max]=tmp;
		heapifly_max(max,que);
	}
	return;
}
