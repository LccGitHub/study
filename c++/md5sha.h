/*************************************************************************
	> File Name: md5.h
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Thu 18 Jan 2018 05:31:32 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

class Md5Sha
{
	public:
        Md5Sha();
        ~Md5Sha();
        int GetMd5(const char *inStr, unsigned char* outStr);
        int GetSha1(const char *inStr, unsigned char* outStr);
        int GetSha256(const char *inStr, unsigned char* outStr);
        int GetMd5File(const char *inStr, unsigned char *outStr);
        int GetSha1File(const char *inStr);

}

