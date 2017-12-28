#include<stdio.h>

int FindEmptyFile(int * test)
{
	int empty_file = 0;
	int i = 0;
	int j = 0;
	for (j = 1; (j <= 32) && (empty_file == 0); j++) {
		printf("%s, %d, i = %d, j=%d\n", __func__, __LINE__, i, j);
		for (i = 0; (i < 32) && (test[i] != j); i++) {
			//printf("%s, %d\n", __func__, __LINE__);

		}
		if (i == 32) {
			empty_file = j;
		}
		else {
		}
//		printf("%s, %d, i = %d, j = %d, empty_file=%d\n", __func__, __LINE__, i, j, empty_file);
	}
	return empty_file;
}

int CharToNum(char c)
{
	int res = 0;
	res = c -'0' + 0;
	//printf("c=%c, res = %d\n", c, res);
	return res;
}

int StringToNum(char * str)
{
	int res = 0;
	int i = 0;
	int len = strlen(str);
	for (i = 0; i < len; i++) {
        res = res*10 + CharToNum(str[i]) ; 
	}
	return res;
}

int main(int argc, char * argv[])
{
	int expect[32] = {0};
	int test[32] = {0};
	int i = 0;
	for (i = 0; i< 32; i++)
	{
		expect[i] = i + 1;
		test[i] = 0;
	}

	int k = StringToNum(argv[1]);
	//printf("argv = %s\n", argv[1]);
	//printf("k = %d\n", k);
#if 1
	for ( i = 0; i < k + 1; i++) {
	    test[i] = i+1;
//		printf("test[%d] = %d\n", i, test[i]);
	}
	int res = FindEmptyFile(test);
	printf("res = %d\n", res);
#endif
}
