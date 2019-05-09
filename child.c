#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<time.h>
#include"myHeader.h"
#define err_sys(a) {perror(a);exit(0);}
#define input_num 3 //./child name time 
static volatile sig_atomic_t sigflag;
sigset_t zeromask,oldmask;

static void sig_usr(int signo);
void WAIT_PARENT(void);

int main(int argc,char* argv[]){
	if(argc!=input_num){
		err_sys("wrong input");
	}
	if(setCPU()<0){
		err_sys("setCPU err");
	}
	if(signal(SIGUSR1,sig_usr)==SIG_ERR){
		err_sys("signal(SIGUSR1) err");
	}
	WAIT_PARENT();
	struct timespec start=getTime();
	printf("%s %ld\n",argv[1],getpid());
	volatile unsigned long i;
	for(int t=0;t<atoi(argv[2]);t++){
		for(i=0;i<1000000UL;i++);
	}
	struct timespec end=getTime();
	printk("[Project1] %ld %ld.%ld %ld.%ld\n",getpid(),start.tv_sec,start.tv_nsec,end.tv_sec,end.tv_nsec);
	return 0;
}

void WAIT_PARENT(void){
	sigemptyset(&zeromask);
	sigprocmask(SIG_SETMASK,NULL,&oldmask);
	while(sigflag==0){
		sigsuspend(&zeromask);
	}
	sigflag=0;
	if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0){
		err_sys("SIG_SETMASK err");
	}
	return;
}
static void sig_usr(int signo){
	sigflag=1;
}
