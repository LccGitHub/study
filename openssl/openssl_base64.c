/*************************************************************************
	> File Name: opessl-base64.c
	> Created Time: Mon 17 Apr 2017 08:17:54 PM CST
 ************************************************************************/

#include<stdio.h>

#include <stdio.h>  
#include <string.h>  
#include <unistd.h>  
  
#include <openssl/pem.h>  
#include <openssl/bio.h>  
#include <openssl/evp.h>  



char unsigned output[4096] = {0};
char unsigned input[4096] = {0};



void print_it(const char* label, const char* buff, size_t len)
{
   printf("%s,%d\n", __func__, __LINE__);
    if(!buff || !len) {
        printf("%s,%d\n", __func__, __LINE__);
        return;
    }
    
    if(label)
        printf("%s: ,len is %zd\n", label, len);
    size_t i=0;   
    for(i=0; i < len; ++i)
        printf("%02X", buff[i]);
    
    printf("\n");
}

  
int base64_encode(char *in_str, int in_len, char *out_str)  
{  
    BIO *b64, *bio;  
    BUF_MEM *bptr = NULL;  
    size_t size = 0;  
  
    if (in_str == NULL || out_str == NULL)  
        return -1;  
  
    b64 = BIO_new(BIO_f_base64());  
    bio = BIO_new(BIO_s_mem());  
    bio = BIO_push(b64, bio);  
  
    BIO_write(bio, in_str, in_len);  
    BIO_flush(bio);  
  
    BIO_get_mem_ptr(bio, &bptr);  
    memcpy(out_str, bptr->data, bptr->length);  
    out_str[bptr->length] = '\0';  
    size = bptr->length;  
  
    BIO_free_all(bio);  
    return size;  
}  
  
int base64_decode(char *in_str, int in_len, char *out_str)  
{ 
    printf("%s,%d\n", __func__, __LINE__);
    BIO *b64, *bio;  
    BUF_MEM *bptr = NULL;  
    int counts;  
    int size = 0;  
  
    if (in_str == NULL || out_str == NULL)  { 
        printf("%s,%d, str is NULL!!!\n", __func__, __LINE__);
        return -1; 
} 
  
    b64 = BIO_new(BIO_f_base64());  
    //BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);  
  
    bio = BIO_new_mem_buf(in_str, in_len);  
    bio = BIO_push(b64, bio);  
  
    size = BIO_read(bio, out_str, in_len);  
    out_str[size] = '\0';  
  
    BIO_free_all(bio);  
    return size;  
}  

int main()
{

    printf("%s,%d\n", __func__, __LINE__);
    FILE* fp_ser = fopen("signature.64","rb");
	if (fp_ser == NULL) {
		printf("%s,%d, fopen failed\n", __func__, __LINE__);
	}
	else {
		long ret_1 = fread(input, 1, 4096, fp_ser);
		fclose(fp_ser);
		base64_decode(input,strlen(input), output);
		//print_it("decode", output, strlen(output));
		printf("decode secondary.64, len = %zd\n", strlen(output));
		printf("%s\n", output);
		
		memset(input, 0, sizeof(input));
		FILE* fp_crt = fopen("signature","rb");
		if (fp_crt == NULL) {
			printf("%s,%d, fopen failed\n", __func__, __LINE__);
		}
		else {
			ret_1 = fread(input, 1, 4096, fp_crt);
			fclose(fp_crt);
			printf("second.crt, len = %zd\n", strlen(input));
			printf("%s\n", input);
		}
    //print_it("decode second.crt", input, strlen(input));
	}


return 0;
}

