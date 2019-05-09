#include"myHeader.h"
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<sche.h>
#define err_sys(a) {perror(a);exit(0);}
#define cycle 8 
static Queue que;

static void sig_usr1(int signo);

int main(int argc,char* argv[]){
	if(setCPU()<0){
		err_sys("set CPU err");
	}
	if(signal(SIGUSR1,sig_usr1)==SIG_ERR){
		err_sys("signal(SIGUSR1) error");
	}
	int n=atoi(argv[1]);
	if(n<0){
		err_sys("task number err");
	}

	int counter=0;
	while(counter<n){
		if(!isEmpty(que)){
			pid_t pid=pop(&que);
			struct sched_param param;
			param.sched_priority=sched_get_priority_max(SCHED_FIFO);
			if(sched_setschedular(pid,SCHED_RR,param)<0){
				err_sys("setschedular denied");
			}
		}
	}	
	return 0;
}
static void sig_usr1(int signo){
	Node node;
	scanf("%ld %d",node.pid_t,node.priority);
	push(node,&que);
}
		
