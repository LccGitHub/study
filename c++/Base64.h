/*************************************************************************
	> File Name: Base64.h
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Wed 17 Jan 2018 01:55:31 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


class Base64
{
	public:
		Base64();
		~Base64();
        int encodeBase64(const unsigned char *inStr, unsigned char* outStr, int outStrSize);
        int decodeBase64(const unsigned char *inStr, unsigned char* outStr, int outStrSize);
        int encodeBase64File(const unsigned char *inStr);
        int decodeBase64File(const unsigned char *inStr);

	private:
        static const unsigned char s_enBaseTable64[65];
        static const unsigned char s_deBaseTable64[256];
};

