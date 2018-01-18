#include<openssl/rsa.h>
#include<openssl/pem.h>
#include<openssl/err.h>
#include"pkcs8.h"

Pkcs8::Pkcs8()
{
    printf("Pkcs8::%s \n", __func__);
}
Pkcs8::~Pkcs8()
{
    printf("Pkcs8::%s \n", __func__);
}
int Pkcs8::enCryptoPkcs8(const unsigned char *inStr, unsigned char* outStr, int outStrSize)
{
    int result = 0;
    if ((inStr == NULL) || (outStr == NULL)) {
        result = 1;
    }
    else {

    }
    return result;
}

int Pkcs8::deCryptoPkcs8(const unsigned char *inStr, unsigned char* outStr, int outStrSize)
{
    int result = 0;
    if ((inStr == NULL) || (outStr == NULL)) {
        result = 1;
    }
    else {
        long inStrLen = 0, len = 0;
        inStrLen = strlen((const char*)inStr);


        outStr[strlen((const char*)outStr) + 1] = 0;

    }
    return result;
}

int Pkcs8::enCryptoPkcs8Ssl(const unsigned char *inStr, unsigned char* outStr, int outStrSize)
{
    int result = 0;
    if ((inStr == NULL) || (outStr == NULL)) {
        result = 1;
    }
    else {
        BIO *bio_err = NULL;
        BIO *in = NULL;
        BIO *out = NULL;
        OpenSSL_add_all_algorithms();
        OpenSSL_add_all_ciphers();
        ERR_load_crypto_strings();

        if (bio_err == NULL) {
            if ((bio_err = BIO_new(BIO_s_file())) != NULL) {
                BIO_set_fp(bio_err, stderr, BIO_NOCLOSE | BIO_FP_TEXT);
            }
            else {
                /* do nothing */
            }
        }
        else {
            /* do nothing */
        }

        in = BIO_new(BIO_s_mem());
        if (in == NULL) {
            ERR_print_errors(bio_err);
            printf("BIO_new failed \n");
        }
        else {
            int count = BIO_write(in, inStr, strlen((const char*)inStr));
            if (count < 0) {
                printf("BIO_write failed\n");
            }
            else {
                printf("BIO_write count=[%d]\n", count);
                EVP_PKEY *pkey_pk1 = NULL;
                pkey_pk1 = PEM_read_bio_PrivateKey(in, NULL,NULL, NULL);
                out = BIO_new(BIO_s_mem());
                if (out == NULL) {
                    printf("%s,%d, BIO_new failed\n",__func__, __LINE__);
                }
                else {
                    unsigned char crypt_password[20] = "111111";
                    int i =PEM_write_bio_PKCS8PrivateKey(out, pkey_pk1,EVP_des_ede3_cbc(), NULL, 0, 0, crypt_password);
                    if (i == 0) {
                        ERR_print_errors(bio_err);
                        printf("%s,%d, PEM_write_bio_PKCS8PrivateKey failed!!\n",__func__, __LINE__);
                    }
                    else {
                        int read_cnt = BIO_read(out, outStr, 4096);
                        printf("%s,%d, read_cnt =[%d]\n",__func__, __LINE__, read_cnt);
                        if (read_cnt > 0) {
                            result = 0;
                        }
                        else {
                            result = 3;
                        }
                    }
                    BIO_free_all(out);
                }
            }
            BIO_free_all(in);
        }
        BIO_free_all(bio_err);

    }
    return result;
}

int Pkcs8::deCryptoPkcs8Ssl(const unsigned char *inStr, unsigned char* outStr, int outStrSize)
{
    int result = 0;
    if ((inStr == NULL) || (outStr == NULL)) {
        result = 1;
    }
    else {
        BIO *bio_err = NULL;
        BIO *in = NULL;
        BIO *out = NULL;

        OpenSSL_add_all_algorithms();
        OpenSSL_add_all_ciphers();
        ERR_load_crypto_strings();

        if (bio_err == NULL) {
            if ((bio_err = BIO_new(BIO_s_file())) != NULL) {
                BIO_set_fp(bio_err, stderr, BIO_NOCLOSE | BIO_FP_TEXT);
            }
            else {
                /* do nothing */
            }
        }
        else {
            /* do nothing */
        }

        in = BIO_new(BIO_s_mem());
        if (in == NULL) {
            ERR_print_errors(bio_err);
            printf("BIO_new failed \n");
        }
        else {
            int count = BIO_write(in, inStr, strlen((const char*)inStr));
            if (count < 0) {
                printf("BIO_write failed\n");
            }
            else {
                printf( "BIO_write count=[%d]\n", count);
                RSA *rsa = RSA_new ();
                if (rsa == NULL) {
                    printf("RSA_new failed\n");
                }
                else {
                    unsigned char crypt_password[20] = "111111";
                    rsa = PEM_read_bio_RSAPrivateKey(in, &rsa,NULL, crypt_password);
                    out = BIO_new(BIO_s_mem());
                    if (out == NULL) {
                        printf( "%s,%d, BIO_new failed\n",__func__, __LINE__);
                    }
                    else {
                        int i =PEM_write_bio_RSAPrivateKey(out, rsa,NULL, NULL, 0, NULL, NULL);
                        if (i == 0) {
                            ERR_print_errors(bio_err);
                            printf("%s,%d, PEM_write_bio_RSAPublicKey failed!!\n",__func__, __LINE__);
                        }
                        else {
                            int read_cnt = BIO_read(out, outStr, 4096);
                            printf("%s,%d, read_cnt =[%d]\n",__func__, __LINE__, read_cnt);
                            if (read_cnt > 0) {
                                result = 0;
                            }
                            else {
                                result = 3;
                            }
                        }
                        BIO_free_all(out);
                    }
                    RSA_free(rsa);
                }
            }
            BIO_free_all(in);
        }
        BIO_free_all(bio_err);
    }
    return result;
}

int Pkcs8::enCryptoPkcs8File(const unsigned char *inStr)
{
    int result = 0;
    if (inStr == NULL) {
        printf("input parameter is NULL \n");
        result = 1;
    }
    else {
        long fileSize = 0;
        FILE* fp = fopen((const char*)inStr, "rb");
        if (NULL == fp) {
            printf("fopen failed!!! \n");
            result = 2;
        }
        else {
            fseek(fp, 0, SEEK_END);/* location end */
            fileSize = ftell(fp); /* get file size */
            fseek(fp, 0, SEEK_SET);
            unsigned char* inStr = NULL;
            unsigned char* outStr = NULL;
            inStr = (unsigned char*)malloc(fileSize + 1);
            outStr = (unsigned char*)malloc(5000);
            if ((inStr == NULL) || (outStr == NULL)) {
                printf("malloc failed!!! \n");
                result = 2;
            }
            else {
                fread(inStr, (size_t)1, (size_t)fileSize, fp);
                fclose(fp);
                enCryptoPkcs8Ssl((const unsigned char*)inStr,outStr, (fileSize/ 3 +1 ) * 4 + 1 );
                printf("inStr =[%s], outStr=[%s] \n", inStr, outStr);
                fp = NULL;
                fp = fopen("enpri.pem", "wb+");
                fwrite(outStr, (size_t)1, (size_t)strlen((const char*)outStr), fp);
                fclose(fp);
                free(inStr);
                free(outStr);
            }
        }
    }
    return result;
}

int Pkcs8::deCryptoPkcs8File(const unsigned char *inStr)
{
    int result = 0;
    if (inStr == NULL) {
        printf("input parameter is NULL \n");
        result = 1;
    }
    else {
        long fileSize = 0;
        FILE* fp = fopen((const char*)inStr, "rb");
        if (NULL == fp) {
            printf("fopen failed!!! \n");
            result = 2;
        }
        else {
            fseek(fp, 0, SEEK_END);/* location end */
            fileSize = ftell(fp); /* get file size */
            fseek(fp, 0, SEEK_SET);
            unsigned char* inStr = NULL;
            unsigned char* outStr = NULL;
            inStr = (unsigned char*)malloc(fileSize + 1);
            outStr = (unsigned char*)malloc(5000);
            if ((inStr == NULL) || (outStr == NULL)) {
                printf("malloc failed!!! \n");
                result = 2;
            }
            else {
                fread(inStr, (size_t)1, (size_t)fileSize, fp);
                fclose(fp);
                deCryptoPkcs8Ssl((const unsigned char*)inStr,outStr, (fileSize/ 3 +1 ) * 4 + 1 );
                printf("inStr =[%s], outStr=[%s] \n", inStr, outStr);
                fp = NULL;
                fp = fopen("depri.pem", "wb+");
                fwrite(outStr, (size_t)1, (size_t)strlen((const char*)outStr), fp);
                fclose(fp);
                free(inStr);
                free(outStr);
            }
        }
    }
    return result;
}

int main()
{

    Pkcs8 pkcs8;
#if 0
    unsigned char enResult[512] = {0};
    base64.encodeBase64((const unsigned char*)"hello world", enResult, sizeof(enResult));
    printf("encode result =[%s] \n", enResult);

    memset(enResult, 0, sizeof(enResult));
    base64.encodeBase64Ssl((const unsigned char*)"hello world", enResult, sizeof(enResult));
    printf("encode ssl result =[%s] \n", enResult);


    unsigned char deResult[512] = {0};
    base64.decodeBase64((const unsigned char*)enResult, deResult, sizeof(deResult));
    printf("decode result =[%s] \n", deResult);

    memset(deResult, 0, sizeof(deResult));
    base64.decodeBase64Ssl((const unsigned char*)enResult, deResult, sizeof(deResult));
    printf("decode ssl result =[%s] \n", deResult);
#endif
    pkcs8.enCryptoPkcs8File((const unsigned char*)"pri.pem");
    pkcs8.deCryptoPkcs8File((const unsigned char*)"enpri.pem");

    return 0;
}

