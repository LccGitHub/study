/*************************************************************************
	> File Name: test_pointer.c
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Thu 16 Nov 2017 10:01:28 AM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>



int main()
{
	printf("%s,%d\n", __func__, __LINE__);

	char a[100] = "helloword";
	char *b = &a;
	printf("%s,%d, b=[%s], a=[%s]\n", __func__, __LINE__, b, a);

	a[2] = '7';
	printf("%s,%d, b=[%s], a=[%s]\n", __func__, __LINE__, b, a);
	
	b[3] = '7';
	printf("%s,%d, b=[%s], a=[%s]\n", __func__, __LINE__, b, a);

	char a1[5] = {0x22,0x80};

	printf("%s,%d, a1=[%s]\n", __func__, __LINE__, a1);

	a1[0] = 0x2E;
	printf("%s,%d, a1=[%s]\n", __func__, __LINE__, a1);
	return 0;
}
