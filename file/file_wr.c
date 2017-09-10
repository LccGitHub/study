/*************************************************************************
	> File Name: file_wr.c
	> Created Time: Sun 10 Sep 2017 05:54:10 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<errno.h>
FILE* fp_ptr = NULL;
const char file_path[] = "fopen_file";


bool fopenFile(void);
void fcloseFile(void);
bool fwriteFile(const char *write_str);



bool fopenFile(void)
{
	bool res = false;
	fp_ptr = fopen(file_path, "wbr+");
	if (fp_ptr == NULL) {
		printf("%s,%d, fopen failed ,errno[%d]\n", __func__, __LINE__, errno);
		res = false;
	}
	else {
		res = true;
	}
	return res;
}

void fcloseFile(void)
{
	if (fp_ptr == NULL) {
		printf("%s,%d, fp have close, value is NULL\n", __func__, __LINE__);
	}
	else {
		fclose(fp_ptr);
		fp_ptr = NULL;
	}
}

bool fwriteFile(const char *write_str)
{
	bool res = false;
	if (write_str == NULL) {
		printf("%s,%d, input is NULL\n", __func__, __LINE__);
		res = false;
	}
	else if (fwrite(write_str, strlen(write_str), 1, fp_ptr) != 1) {
		printf("%s,%d,  fwrite failed, errno[%d]\n", __func__, __LINE__, errno);
		res = false;
	}
	else {
		res = true;
	}
	return res;
}

bool freadFile(void)
{
	bool res = false;
	size_t cnt = 0;
	char read_str[1024] = {0};
	memset(read_str, 0, sizeof(read_str));
	fseek(fp_ptr, 0L, SEEK_END);
	cnt = ftell(fp_ptr);

	fseek(fp_ptr, 0L, SEEK_SET);
	if (fread(read_str, 1, cnt +1 , fp_ptr) <= 0) {
		printf("%s,%d, fread failed!\n", __func__, __LINE__);
		res = false;
	}
	else {
		printf("read buff is:\n[%s]\n", read_str);
		res = true;
	}
	return res;
}

int main(void)
{
	char str[128] = "How are you!\n";
	if (fopenFile() == false) {
		printf("%s,%d, open file failed\n", __func__, __LINE__);
	}
	else if (fwriteFile(str) == false){
		printf("%s,%d, write faile failed\n", __func__, __LINE__);
	}
	else if (freadFile() == false) {
		printf("%s,%d, read faile failed\n", __func__, __LINE__);
	}
	else {
		printf("%s,%d, read success\n", __func__, __LINE__);
		fcloseFile();
	}
	return 0;
}

