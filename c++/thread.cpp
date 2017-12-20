/*************************************************************************
	> File Name: thread.c
	> pthread_exit: thread slef exit 
	> pthread_cancel: other thread cancel this thread
	> pthread_join:main thread wait for subthread exit and release resource
	> Created Time: Wed 20 Dec 2017 04:17:55 PM CST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void * Run(void* pthr);

class Thread
{
	public:
		Thread();
		~Thread();
		int Start(void);
		int Stop(void);
		//void* Run(void* ptr);
	public:
		pthread_t m_threadId;
};

Thread::Thread()
	:m_threadId(-1)
{
	printf("this is construct function \n");
}
Thread::~Thread()
{
	//pthread_attr_destory(&m_threadId);
	printf("this is Deconstruct function \n");
}

int Thread::Start(void)
{
	int res = -1;
	res = pthread_create(&m_threadId, NULL, Run, NULL );
	if (res == 0) {
		printf("thread creat success \n");
	}
	else {
		printf("thread creat failed \n");
	}
	return res;
}

int Thread::Stop(void)
{
	char str[128] = "thread exit!";
	printf("thread stop\n");
	pthread_cancel(m_threadId);
	return 0;
}

void* /*Thread::*/Run(void* ptr)
{
	int i = 0;
	while(1) {
		printf("run %d \n", i + 1);
		if (i == 50) {
			pthread_exit(NULL);
		}
		i = i + 1;
		sleep(1);
	}
}

int main(int argc, char* argv[])
{
	Thread thread1, thread2;

	int thr = 0;
	int isStart = 0;
	while(1)
	{
		printf("please input thread_id and isStart\n");
		scanf("%d %d",&thr, &isStart);
		if (thr == 1) {
			if (isStart == 1) {
				thread1.Start();
			}
			else {
				thread1.Stop();
			}
		}
		else if (thr == 2) {
			if (isStart == 1) {
				thread2.Start();
			}
			else {
				thread2.Stop();
			}
		}
		else {
			printf("please input vaild vaule \n");
		}
		thr = 0;
		isStart = 0;
	}

	pthread_join(thread1.m_threadId,NULL); //wait child thread exit
	pthread_join(thread2.m_threadId,NULL);
	return 0;
}
