#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include"myHeader.h"
typedef struct process{
	char name[32];
	int R;
	int T;
	pid_t pid;
	struct timespec ts_start;
	struct timespec ts_end;
}Process;

int check_type(char type[]);
int compare(const void* prt1,const void* ptr2);

int main(int argc,char* argv[]){
	//io
	char type[8];
	scanf("%s",type);
	int N;
	scanf("%d",&N);
	Process tasks[MAXTASK];
	for(int i=0;i<N;i++){
		scanf("%s%d%d",tasks[i].name,&tasks[i].R,&tasks[i].T);
	}
	
	//fork schedular
	qsort(tasks,N,sizeof(Process),compare);
	int type_num;
	int fd[2];
	pid_t pid;
	if(pipe(fd)<0){
		err_sys("pipe error");
	}
	if((type_num=check_type(type))<0){
		err_sys("invalid type");
	}
	else{
		if((pid=fork())<0){
			err_sys("fork child error");
		}
		else if(pid==0){
			close(fd[1]);
			if(type_num==1)
				execlp("./fifo","./fifo",N,"\0");
			else if(type_num==2)
				execlp("./rr","./rr",N,"\0");
			else if(type_num==3)
				execlp("./sjf","./sjf",N,"\0");
			else execlp("./psjf","./psjf",N,"\0");
		}
		else{
			close(fd[0]);
		}
	}

	//clock
	int counter=0,index=0;
	while(index!=N){
		while(counter<tasks[index].R){
			volatile unsigned long i;
			for(i=0;i<1000000UL;i++);
			counter++;
		}
		pid_t tpid;
		if((tpid=fork())<0){
			err_sys("fork child error");
		}
		else if(tpid==0){
			execlp("./child","./child",tasks[index].name,tasks[index].T,"\0");
		}
		else{
			tasks[index].pid=tpid;
			index++;
		}
	}
	for(int i=0;i<N;i++){
		waitpid(tasks[i].pid,NULL,0);
	}
	waitpid(pid,NULL,0);
	return 0;
}

int check_type(char type[]){
	if(strcmp(type,"FIFO")==0){
		return 1;
	}
	if(strcmp(type,"RR")==0){
		return 2;
	}
	if(strcmp(type,"SJF")==0){
		return 3;
	}
	if(strcmp(type,"PSJF")==0){
		return 4;
	}
	return -1;
}

int compare(const void* prt1,const void* ptr2){
	Process* a=(Process*)ptr1;
	Process* b=(Process*)ptr2;
	if(a->R<b->R) return -1;
	else if(a->R>b->R) return 1;
	else return 0;
}

