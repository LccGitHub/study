/*************************************************************************
	> File Name: file_wr.c
	> Created Time: Sun 10 Sep 2017 05:54:10 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>
int fp_ptr = 0;
const char file_path[] = "fopen_file";


bool fopenFile(void);
void fcloseFile(void);
bool fwriteFile(const char *write_str);



bool fopenFile(void)
{
	bool res = false;
	fp_ptr = open(file_path, O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
	if (fp_ptr < 0) {
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
	if (fp_ptr == 0) {
		printf("%s,%d, fp have close, value is NULL\n", __func__, __LINE__);
	}
	else {
		close(fp_ptr);
		fp_ptr = 0;
	}
}

bool fwriteFile(const char *write_str)
{
	bool res = false;
	if (write_str == NULL) {
		printf("%s,%d, input is NULL\n", __func__, __LINE__);
		res = false;
	}
	else if (write(fp_ptr, write_str, strlen(write_str)) == -1) {
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

	struct stat sb;
	ssize_t size = 0;
	lseek(fp_ptr, 0L, 0);
	if (fstat(fp_ptr, &sb) < 0) {
		printf("%s,%d, fstat failed\n", __func__, __LINE__);
		res = false;
	}
	else {
		size = sb.st_size;
		printf("%s,%d, size=[%zd]\n", __func__, __LINE__, size);
		cnt = read(fp_ptr, read_str, size );
		if (cnt == -1) {
			printf("%s,%d, read failed, errno[%d]!\n", __func__, __LINE__, errno);
			res = false;
		}
		else {
			printf("%s,%d, cnt=[%zd]\n", __func__, __LINE__, cnt);
			printf("read buff is:\n[%s]\n", read_str);
			res = true;
		}
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

