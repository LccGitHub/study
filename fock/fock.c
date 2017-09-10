/*************************************************************************
	> File Name: fock.c
	> Created Time: Sun 10 Sep 2017 03:51:45 PM CST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>

void ForkSingle(void)
{
	pid_t fpid = -1;
	int cnt = 0;
	fpid = fork();

	if (fpid < 0) {
		printf("%s,%d, fork failed\n", __func__, __LINE__);
	}
	else if (fpid == 0) {
		printf("This is child process, pid: [%d], ppid: [%d], fpid: [%d]\n", getpid(), getppid(), fpid);
		cnt++;
//		printf("%s,%d, cnt = [%d]\n", __func__, __LINE__, cnt);
	}
	else {
		printf("This is parents process, pid: [%d], ppid: [%d], fpid: [%d]\n", getpid(), getppid(), fpid);
		cnt++;
//		printf("%s,%d, cnt = [%d]\n", __func__, __LINE__, cnt);
	}
		printf("%s,%d, end!!\n", __func__, __LINE__);
}
int main()
{
	int i = 0;
   //ppid指当前进程的父进程pid  
   //pid指当前进程的pid,  
   //fpid指fork返回给当前进程的值  
   for(i=0;i<2;i++){  
	   pid_t fpid=fork();  
       if(fpid==0)  
		   printf("%d child  %4d %4d %4d\n",i,getppid(),getpid(),fpid);  
       else  
           printf("%d parent %4d %4d %4d\n",i,getppid(),getpid(),fpid);
	   printf("############%d############\n", i);
   }  
	return 0;
}
