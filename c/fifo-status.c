/*************************************************************************
	> File Name: fifo.c
	> Created Time: Sun 17 Dec 2017 04:18:45 PM CST
	> this is static queue, by a parameter to judy queue is impty
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>


#define MAX_SIZE 10
typedef struct _status_
{
	int next_out;
	int next_in;
	int counter;
}t_status;

int data[MAX_SIZE]= {0};
static t_status status = {};
static overwritten = 0;
void StoreData()
{
	data[status.next_in] =  1 + status.next_in;
	if (status.counter == MAX_SIZE) {
		status.next_out = (status.next_out + 1) % MAX_SIZE;
		status.counter = status.counter;
		overwritten = 1;
	}
	else {
		status.counter = status.counter + 1;
	}
	status.next_in = (status.next_in + 1) % MAX_SIZE;
}

void DeletData()
{
	if (overwritten == 1) {
		printf("data have over written!!!\n");
	}
	else {
		data[status.next_out] = 0;
		status.next_out = (status.next_out + 1) % MAX_SIZE;
		status.counter = status.counter - 1;
	}
}

void DeleteData()
{
	if (status.counter == 0) {
		printf("data is empty!!!");
	}
	else {
		data[status.next_out] = 0;
		status.next_out = (status.next_out + 1) % MAX_SIZE;
		status.counter = status.counter - 1;
	}
}

void InitData()
{
	int i = 0;
	for (i = 0; i < MAX_SIZE; i++)
	{
		data[i] = 0;
	}
	status.next_in = 0;
	status.next_out = 0;
	status.counter = 0;
}

void PrintMsg()
{
	//printf("in=%d,out=%d,counter=%d\n", status.next_in, status.next_out, status.counter);
	int i = 0;
	printf("[");
	for (i = 0; i< MAX_SIZE; i++) {
		if (i != MAX_SIZE -1) {
			printf("%d, ",data[i]);
		}
		else {
			printf("%d]\n",data[i]);
		}
	}
	printf("in=%d,out=%d,counter=%d\n", status.next_in, status.next_out, status.counter);
}

int main(int argc, char * argv[])
{
	
	InitData();
	PrintMsg();
	while(1) {
		int store = 0, delete = 0;
		printf("please input store delete:");
		scanf("%d %d", &store, &delete);
		int i = 0;
		/* store a data */
	    if (store == 1) {
			StoreData();
			PrintMsg();
		}

		/* delete a vaule */
	    if (delete == 1) {
			DeleteData();
			PrintMsg();
		}

	}

	return 0;
}
