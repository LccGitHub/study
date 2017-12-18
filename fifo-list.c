/*************************************************************************
	> File Name: fifo.c
	> Created Time: Sun 17 Dec 2017 04:18:45 PM CST
	> this is static queue, by a parameter to judy queue is impty
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 5

typedef struct LinkNode
{
	int vaule;
	struct LinkMode *next;
}LinkNode;

typedef struct _LinkQueue_
{
	LinkNode* next_out;
	LinkNode* next_in;
}LinkQueue;

LinkQueue Q1;
LinkQueue *Q = &Q1;
static overwritten = 0;

int GetLenght();


void StoreData(int val)
{
#if 0
	if (GetLenght() == MAXSIZE) {
		overwritten = 1;
		LinkNode *p = Q->next_out->next;
		Q->next_out->next = p->next;
		if (p == Q->next_in) {
			Q->next_in = Q->next_out;
		}
		free(p);
	}
#endif
	LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
	p->vaule = val;
	p->next = NULL;
	Q->next_in ->next = p;
	Q->next_in = p;

#if 0
	if (GetLenght() == MAXSIZE) {
		overwritten = 1;
		DeleteData();

		LinkNode *p = Q->next_out->next;
		Q->next_out->next = p->next;
		if (p == Q->next_in) {
			Q->next_in = Q->next_out;
		}
		free(p);
	}
#endif
}

void DeleteData()
{
	if (Q->next_in == Q->next_out /*|| overwritten == 1*/) {
		printf("Queue is empty!!!\n");
	}
	else {
		LinkNode *p = Q->next_out->next;
		Q->next_out->next = p->next;
		if (p == Q->next_in) {
			Q->next_in = Q->next_out;
		}
		free(p);
	}
}


void InitData()
{
	Q->next_in = Q->next_out = (LinkNode *)malloc(sizeof(LinkNode));
	Q->next_in->next = NULL;
}
#if 1
int GetLenght()
{
	int lenght = 0;
	if (Q->next_out == NULL) {
		lenght = 1;
		printf("lenght is 0 \n");
	}
	else {
	LinkNode *p = Q->next_out->next;
	for (p = Q->next_out->next; p <= Q->next_in && p != NULL; p = p->next) {
		lenght = lenght + 1;
	}
	}
	return lenght;
}
#endif
void PrintMsg()
{
	if (Q->next_out == NULL || Q->next_out->next ==  NULL) {
		printf("queue is empty, lenght=%d \n", GetLenght());
	}
	else {
	LinkNode* p = Q->next_out->next;
	printf("[");
	while(p < Q->next_in, p->next != NULL) {
		printf("%d,", p->vaule);
		p = p->next;
	}
	printf("%d]\n", p->vaule);
	printf("in=%p, out=%p, lenght=%d\n", Q->next_in, Q->next_out, GetLenght());
	}

}

int main(int argc, char * argv[])
{
	static cnt_vaule = 1;
	InitData();
	PrintMsg();
	while(1) {
		int store = 0, delete = 0;
		printf("please input store delete:");
		scanf("%d %d", &store, &delete);
		int i = 0;
		/* store a data */
	    if (store == 1) {
			StoreData(cnt_vaule);
			PrintMsg();
			cnt_vaule = cnt_vaule + 1;
		}

		/* delete a vaule */
	    if (delete == 1) {
			DeleteData();
			PrintMsg();
		}

	}

	return 0;
}
