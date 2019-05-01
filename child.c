#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#define err_sys(a) {perror(a);exit(0);}
#define input_num 3 //./child name time
int main(int argc,char* argv[]){
	if(argc!=input_num){
		err_sys("wrong input");
	}
	if(setCPU()<0){
		err_sys("setCPU err");
	}
	wait_parrent();
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
wait_parrent(){
	sigset_t waitMask;
	sigemptyset(waitMask);
	sigsuspend()
}
