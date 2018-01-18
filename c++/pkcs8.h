/*************************************************************************
	> File Name: pkcs8.h
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Thu 18 Jan 2018 02:38:20 PM CST
 ************************************************************************/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

class Pkcs8
{
    public:
        Pkcs8();
        ~Pkcs8();
        int enCryptoPkcs8(const unsigned char *inStr, unsigned char* outStr, int outStrSize);
        int deCryptoPkcs8(const unsigned char *inStr, unsigned char* outStr, int outStrSize);
        int enCryptoPkcs8Ssl(const unsigned char *inStr, unsigned char* outStr, int outStrSize);
        int deCryptoPkcs8Ssl(const unsigned char *inStr, unsigned char* outStr, int outStrSize);
        int enCryptoPkcs8File(const unsigned char *inStr);
        int deCryptoPkcs8File(const unsigned char *inStr);
};

