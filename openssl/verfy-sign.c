#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/x509_vfy.h>
#include  <errno.h>

#define certfile "secondary.crt"
#define image_file "image.cwe"
#define signature_file "signature"

unsigned char sig_buf[4096] = {0};
int main()
{
    EVP_MD_CTX     md_ctx;
    EVP_PKEY *      pkey;
    FILE *          fp;
    X509 *	x509;
    int err;
    int sig_len;
    FILE* fp_update = fopen(signature_file,"rb");
	if (fp_update == NULL) {
		printf("%s,%d\n", __func__, __LINE__);
	}
    //    fseek(fp_update, 0L, 512*8);
    long ret = fread(sig_buf, 1, 2048, fp_update);
    printf("%s,%d\n", __func__, __LINE__);
    printf("%s,%d, ret = %ld\n",  __func__, __LINE__, ret);
    sig_len = ret;
    printf("%s,%d, sig_len = %d\n",  __func__, __LINE__, sig_len);
    fclose(fp_update);
    printf("%s,%d\n", __func__, __LINE__);

    /* Read public key */

    /* openssl x509 -in secondary.crt -pubkey -noout > secondary_public.pem */
    fp = fopen (certfile, "rb");
    if (fp == NULL)
        printf("%s,%d\n", __func__, __LINE__);
    x509 = (X509 *)(PEM_ASN1_read ((char *(*)())d2i_X509, PEM_STRING_X509, fp, NULL, NULL, NULL));
    if (x509 == NULL) {
        ERR_print_errors_fp (stderr);
        printf("%s,%d\n", __func__, __LINE__);
    }
    fclose (fp);

    /* Get public key - eay */
    pkey=X509_extract_key(x509);
    if (pkey == NULL) {
        ERR_print_errors_fp (stderr);
        exit (1);
    }

    /* Verify the signature */
   /* openssl dgst -sha256 -verify secondary_public.pem -signature signature image.cwe*/
    unsigned char *data = NULL;
    FILE* fp_image = fopen(image_file, "rb");
	if (fp_image == NULL) {
		printf("%s,%d, fopen failed \n", __func__, __LINE__);
	}
 	else  {
		fseek(fp_image, 0L, SEEK_END);
		size_t sz = ftell(fp_image);
		rewind(fp_image);
		data = malloc((size_t)sz);
		printf("%s,%d, sz = %zd\n",  __func__, __LINE__, sz);
		ret = fread(data, 1, sz, fp_image);
		fclose(fp_image);
		printf("%s,%d, ret = %ld\n",  __func__, __LINE__, ret);
		
		EVP_MD_CTX* m_RSAVerifyCtx = EVP_MD_CTX_create();
		EVP_DigestVerifyInit(m_RSAVerifyCtx, NULL, EVP_sha256(), NULL, pkey);
		EVP_DigestVerifyUpdate(m_RSAVerifyCtx, data, sz);
		err = EVP_DigestVerifyFinal(m_RSAVerifyCtx, sig_buf, sig_len);
		
		if (err != 1) {
			printf("%s,%d, err = %d\n", __func__, __LINE__, err);
			ERR_print_errors_fp (stderr);
		}
		else {
			printf ("Signature Verified Ok.\n");
		}
		EVP_PKEY_free (pkey);
	}
	return 0;
}

