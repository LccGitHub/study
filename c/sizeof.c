/*************************************************************************
	> File Name: sizeof.c
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Wed 20 Dec 2017 07:27:55 PM CST
 ************************************************************************/

#include<stdio.h>


int main()
{
	printf("long int siezof=%d\n", sizeof(long));
	printf("int siezof=%d\n", sizeof(int));
	printf("float siezof=%d\n", sizeof(float));
	printf("double siezof=%d\n", sizeof(double));
	printf("long long siezof=%d\n", sizeof(long long));
	int vaule = 0x45BA;
	
	printf("vaule=0x%x, %d, %d\n", vaule, vaule, sizeof(vaule));
	vaule = 32767;
	
	printf("vaule=0x%x, %d, %d\n", vaule, vaule, sizeof(vaule));
	return 0;
}
