#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#define err_sys(a) {perror(a);exit(0);}
#define input_num 3  //./child name time
int main(int argc,char* argv[]){
	if(argc!=input_num){
		err_sys("wrong input");
	}
	wait_parrent();
	printf("%s %ld\n",argv[1],getpid());
	volatile unsigned long i;
	for(int t=0;t<atoi(argv[2]);t++){
		for(i=0;i<1000000UL;i++);
	}
	return 0;
}
wait_parrent(){
	sigset_t waitMask;
	sigemptyset(waitMask);
	sigsuspend()
}
