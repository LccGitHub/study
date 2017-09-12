/*************************************************************************
	> File Name: phread_cond_wait.c
	> Created Time: Tue 12 Sep 2017 10:24:17 AM CST
	gcc pthread_cond_wait.c -o pthread_cond_wait -lpthread
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *thread1(void*);
void *thread2(void*);

int i = 1;

void *thread1(void * func)
{
	for(i = 1; i < 10; i++) {
		pthread_mutex_lock(&mutex);
		printf("%s,%d, thread1 was called \n", __func__, __LINE__);
		if (i %3 == 0) {
			pthread_cond_signal(&cond); /* send signal    */
		}
		else {
			printf("%s,%d, thread1:%d \n", __func__, __LINE__, i);
		}
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}

void *thread2(void * func)
{
	while(i < 9) {
		pthread_mutex_lock(&mutex);
		printf("%s,%d, thread2 was called \n", __func__, __LINE__);
		if (i %3 != 0) {
			pthread_cond_wait(&cond, &mutex); /* wait    */
			printf("%s,%d, thread2:%d \n", __func__, __LINE__, i);
		}
		else {
			printf("%s,%d, thread2:%d \n", __func__, __LINE__, i);
		}
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}
int main()
{
	pthread_t t_a;
	pthread_t t_b;

	/* creat two thread */
	pthread_create(&t_a, NULL, thread2, (void*)NULL);
	pthread_create(&t_b, NULL, thread1,(void*)NULL);

	pthread_join(t_b, NULL); //wait thread1 finish
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);

	printf("%s,%d, main have finished!\n", __func__, __LINE__);
	return 0;
}
