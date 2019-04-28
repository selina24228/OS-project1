#include"myHeader.h"
#include<string.h>
#include<linux/ktime.h>
#include<linux/timekeeping.h>

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
 
int isEmpty(Queue que){
	return ((que.n==0)?1:0);
}
pid_t pop(Queue que){
	pid_t result=que.task[0];
	que.n-=1;
	que.task[]=que.task[que.n];
	return result;
}
