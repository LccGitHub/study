#include <openssl/md5.h>
#include <openssl/sha.h>
#include"md5sha.h"
#include"Base64.h"

Md5Sha::Md5Sha()
{
}
Md5Sha::~Md5Sha()
{
}
int Md5Sha::GetMd5(const char *inStr, unsigned char* outStr)
{
    int result = 0;
    if ((inStr == NULL) || (outStr == NULL)) {
        result = 1;
    }
    else {
        unsigned char md5_buf[MD5_CBLOCK+1] = {0};
        memset(md5_buf, 0, sizeof(md5_buf));
        MD5_CTX mdContext;
        MD5_Init (&mdContext);
        MD5_Update (&mdContext, inStr, (size_t)strlen((const char*)inStr));
        MD5_Final (md5_buf, &mdContext);
        md5_buf[strlen((const char*)md5_buf)] = 0;
        int i = 0;
        for(i=0; i< MD5_DIGEST_LENGTH; i++)
        {
            snprintf((char*)outStr + i*2, (size_t)3, "%02x", md5_buf[i]);
        }
        outStr[strlen((const char*)outStr)] = 0;
        printf("%s,%d, md5 = [%s]\n", __func__, __LINE__, outStr);
    }
    return result;
}

int Md5Sha::GetSha1(const char *inStr, unsigned char* outStr)
{
    int result = 0;
    if ((inStr == NULL) || (outStr == NULL)) {
        result = 1;
    }
    else {
        unsigned char md5_buf[SHA_DIGEST_LENGTH+1] = {0};
        memset(md5_buf, 0, sizeof(md5_buf));
        SHA_CTX mdContext;
        SHA1_Init (&mdContext);
        SHA1_Update (&mdContext, inStr, (size_t)strlen((const char*)inStr));
        SHA1_Final (md5_buf, &mdContext);
        md5_buf[strlen((const char*)md5_buf)] = 0;
        int i = 0;
        for(i=0; i< SHA_DIGEST_LENGTH; i++)
        {
            snprintf((char*)outStr + i*2, (size_t)3, "%02x", md5_buf[i]);
        }
        outStr[strlen((const char*)outStr)] = 0;
        printf("%s,%d, sha1 = [%s]\n", __func__, __LINE__, outStr);
    }
    return result;
}

int Md5Sha::GetSha256(const char *inStr, unsigned char* outStr)
{
    int result = 0;
    if ((inStr == NULL) || (outStr == NULL)) {
        result = 1;
    }
    else {
        unsigned char md5_buf[SHA256_DIGEST_LENGTH+1] = {0};
        memset(md5_buf, 0, sizeof(md5_buf));
        SHA256_CTX mdContext;
        SHA256_Init (&mdContext);
        SHA256_Update (&mdContext, inStr, (size_t)strlen((const char*)inStr));
        SHA256_Final (md5_buf, &mdContext);
        md5_buf[strlen((const char*)md5_buf)] = 0;
        int i = 0;
        for(i=0; i< SHA256_DIGEST_LENGTH; i++)
        {
            snprintf((char*)outStr + i*2, (size_t)3, "%02x", md5_buf[i]);
        }
        outStr[strlen((const char*)outStr)] = 0;
        printf("%s,%d, sha1 = [%s]\n", __func__, __LINE__, outStr);
    }
    return result;
}

int Md5Sha::GetMd5File(const char *inStr, unsigned char* outStr)
{
    int result = 0;
    if ((inStr == NULL) || (outStr == NULL)) {
        result = 1;
    }
    else {
        FILE *fd=fopen(inStr,"r");
        if (NULL == fd) {
            printf("fopen file failed \n");
            result = 2;
        }
        else {
            unsigned char md5_buf[MD5_CBLOCK+1] = {0};
            char pData[512] = {0};
            memset(md5_buf, 0, sizeof(md5_buf));
            MD5_CTX mdContext;
            MD5_Init (&mdContext);

            while(fread(pData, 1, 1, fd) > 0) {
                MD5_Update (&mdContext, pData, (size_t)strlen((const char*)pData));
            }
            MD5_Final (md5_buf, &mdContext);
            md5_buf[strlen((const char*)md5_buf)] = 0;
            int i = 0;
            for(i=0; i< MD5_DIGEST_LENGTH; i++)
            {
                snprintf((char*)outStr + i*2, (size_t)3, "%02x", md5_buf[i]);
            }
            outStr[strlen((const char*)outStr)] = 0;
            printf("%s,%d, md5 = [%s]\n", __func__, __LINE__, outStr);
        }
    }
    return result;

}

int Md5Sha::GetSha1File(const char *inStr, unsigned char* outStr)
{
    int result = 0;
    if ((inStr == NULL) || (outStr == NULL)) {
        result = 1;
    }
    else {
        FILE *fd=fopen(inStr,"r");
        if (NULL == fd) {
            printf("fopen file failed \n");
            result = 2;
        }
        else {
            unsigned char md5_buf[SHA_DIGEST_LENGTH+1] = {0};
            char pData[512] = {0};
            memset(md5_buf, 0, sizeof(md5_buf));
            SHA_CTX mdContext;
            SHA1_Init (&mdContext);

            while(fread(pData, 1, 1, fd) > 0) {
                SHA1_Update (&mdContext, pData, (size_t)strlen((const char*)pData));
            }
            SHA1_Final (md5_buf, &mdContext);
            md5_buf[strlen((const char*)md5_buf)] = 0;
            int i = 0;
            for(i=0; i< SHA_DIGEST_LENGTH; i++)
            {
                snprintf((char*)outStr + i*2, (size_t)3, "%02x", md5_buf[i]);
            }
            outStr[strlen((const char*)outStr)] = 0;
            printf("%s,%d, SHA = [%s]\n", __func__, __LINE__, outStr);
        }
    }
    return result;
}

int main()
{
    Md5Sha md5sha;
    unsigned char outStr[SHA256_DIGEST_LENGTH*2+1] = {0};
    md5sha.GetMd5((const char *)"hello world", outStr);
    memset(outStr, 0, sizeof(outStr));
    md5sha.GetMd5File((const char *)"test.txt", outStr);
    memset(outStr, 0, sizeof(outStr));
    md5sha.GetSha1((const char *)"hello world", outStr);
    memset(outStr, 0, sizeof(outStr));
    md5sha.GetSha1File((const char *)"test.txt", outStr);
    memset(outStr, 0, sizeof(outStr));
    md5sha.GetSha256((const char *)"hello world", outStr);


    Base64 base64;
    unsigned char enResult[512] = {0};
    base64.encodeBase64((const unsigned char*)"hello world", enResult, sizeof(enResult));
    printf("encode result =[%s] \n", enResult);


}

