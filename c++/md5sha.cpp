#include <openssl/md5.h>
#include"md5sha.h"

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
        UI_8 md5_buf[MD5_CBL_bufOCK+1] = {0};
        memset(md5_buf, 0, sizeof(md5_buf));
        MD5_CTX mdContext;
        MD5_Init (&mdContext);
        MD5_Update (&mdContext, inStr, (size_t)strlen((const char*)inStr));
        MD5_Final (md5_buf, &mdContext);
        md5_buf[strlen(md5_buf)] = 0;
        int i = 0;
        for(i=0; i< MD5_DIGEST_LENGTH; i++)
        {
            snprintf((char*)md5_buf + i*2, (size_t)3, "%02x", md5_buf[i]);
        }
        printf("%s,%d, md5 = [%s]\n", __func__, __LINE__, md5_buf);
    }
    return result;
}

int Md5Sha::GetSha1(const char *inStr, unsigned char* outStr)
{
}

int Md5Sha::GetSha256(const char *inStr, unsigned char* outStr)
{
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
            UI_8 md5_buf[MD5_CBL_bufOCK+1] = {0};
            char pData[512] = {0};
            memset(md5_buf, 0, sizeof(md5_buf));
            MD5_CTX mdContext;
            MD5_Init (&mdContext);

            while(fread(pData, 1, 1, fd) > 0) {
                MD5_Update (&mdContext, pData, (size_t)strlen((const char*)pData));
            }
            MD5_Final (md5_buf, &mdContext);
            md5_buf[strlen(md5_buf)] = 0;
            int i = 0;
            for(i=0; i< MD5_DIGEST_LENGTH; i++)
            {
                snprintf((char*)md5_buf + i*2, (size_t)3, "%02x", md5_buf[i]);
            }
            printf("%s,%d, md5 = [%s]\n", __func__, __LINE__, md5_buf);
        }
    }
    return result;
}

int Md5Sha::GetSha1File(const char *inStr)
{
}

