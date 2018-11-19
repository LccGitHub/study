#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/err.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


#define CACERT_FILE_PATH "cacert.pem"
const char cert_filestr[] = "secondary.crt";
EVP_PKEY *fwpdate_pkey = NULL;

/*===========================================
|*==                    G                  ==
|*==    Validating secondary certificate   ==
|*===========================================
|*openssl verify -CAfile cacert.pem secondary.crt*/
static bool FwUpdateVerfySecCert(void)
{
    printf("%s, %d\n", __FUNCTION__, __LINE__);
    bool result = false;
    BIO              *certbio = NULL;
    BIO               *outbio = NULL;
    X509          *error_cert = NULL;
    X509                *fwupdat_cert = NULL;
    X509_NAME    *certsubject = NULL;
    X509_STORE         *store = NULL;
    X509_STORE_CTX  *vrfy_ctx = NULL;
    int64_t ret = -1;

    /* ---------------------------------------------------------- */
    /* These function calls initialize openssl for correct work.  */
    /* ---------------------------------------------------------- */
    OpenSSL_add_all_algorithms();
    ERR_load_BIO_strings();
    ERR_load_crypto_strings();

    /* ---------------------------------------------------------- */
    /* Create the Input/Output BIO's.                             */
    /* ---------------------------------------------------------- */
    certbio = BIO_new(BIO_s_file());
    outbio  = BIO_new_fp(stdout, BIO_NOCLOSE);

    /* ---------------------------------------------------------- */
    /* Initialize the global certificate validation store object. */
    /* ---------------------------------------------------------- */
    store=X509_STORE_new();
    if (store == NULL) {
        BIO_printf(outbio, "Error creating X509_STORE_CTX object\n");
    }
    else {

        /* ---------------------------------------------------------- */
        /* Create the context structure for the validation operation. */
        /* ---------------------------------------------------------- */
        vrfy_ctx = X509_STORE_CTX_new();

        /* ---------------------------------------------------------- */
        /* Load the certificate and cacert chain from file (PEM).     */
        /* ---------------------------------------------------------- */
        ret = BIO_read_filename(certbio, cert_filestr);
        fwupdat_cert = PEM_read_bio_X509(certbio, NULL, 0, NULL);
        if (fwupdat_cert  == NULL) {
            BIO_printf(outbio, "Error loading cert into memory\n");
            result = false;
        }
        else {

            ret = X509_STORE_load_locations(store, CACERT_FILE_PATH, NULL);
            if (ret != 1) {
                BIO_printf(outbio, "Error loading CA cert or chain file\n");
            }
            else {
                /* do nothing*/
            }

            /* ---------------------------------------------------------- */
            /* Initialize the ctx structure for a verification operation: */
            /* Set the trusted cert store, the unvalidated cert, and any  */
            /* potential certs that could be needed (here we set it NULL) */
            /* ---------------------------------------------------------- */
            X509_STORE_CTX_init(vrfy_ctx, store, fwupdat_cert, NULL);

            /* ---------------------------------------------------------- */
            /* Check the complete cert chain can be build and validated.  */
            /* Returns 1 on success, 0 on verification failures, and -1   */
            /* for trouble with the ctx object (i.e. missing certificate) */
            /* ---------------------------------------------------------- */
            ret = X509_verify_cert(vrfy_ctx);
            BIO_printf(outbio, "Verification return code: %ld\n", ret);
            if (ret == 1) {
                result = true;
            }
            else {
                result = false;
            }


            if((ret == 0) || (ret == 1)) {
                BIO_printf(outbio, "Verification result text: %s\n",
                           X509_verify_cert_error_string(vrfy_ctx->error));
            }
            else {
                /*Do Nothing */
            }

            /* ---------------------------------------------------------- */
            /* The error handling below shows how to get failure details  */
            /* from the offending certificate.                            */
            /* ---------------------------------------------------------- */
            if(ret == 0) {
                /*  get the offending certificate causing the failure */
                error_cert  = X509_STORE_CTX_get_current_cert(vrfy_ctx);
                certsubject = X509_NAME_new();
                certsubject = X509_get_subject_name(error_cert);
                BIO_printf(outbio, "Verification failed cert:\n");
                /*  polyspace< JUST-MISRA-8.1 :depend on openssl format. No modification: Justify > */
                X509_NAME_print_ex(outbio, certsubject, 0, (uint64_t)XN_FLAG_MULTILINE);
                BIO_printf(outbio, "\n");
            }
        }

        /* ---------------------------------------------------------- */
        /* Free up all structures                                     */
        /* ---------------------------------------------------------- */
        X509_STORE_CTX_free(vrfy_ctx);
        X509_STORE_free(store);
        X509_free(fwupdat_cert);
        BIO_free_all(certbio);
        BIO_free_all(outbio);
    }
    /*BIO_free_all(certbio);*/
    /*BIO_free_all(outbio);*/
    printf("%s, %d, result =%d \n", __FUNCTION__, __LINE__, result);
    return result;
}


/*======================================================================================
|*==                  H                                                               ==
|*==            Extracting secondary keys                                             ==
|*==   openssl x509 -in secondary.crt -pubkey -noout > secondary_public.pem           ==
|*======================================================================================*/

static bool FwExtracSecondaryKeys(void)
{
    printf("%s, %d\n", __FUNCTION__, __LINE__);
    bool result = false;
    BIO *certbio = NULL;
    BIO *outbio = NULL;
    X509 *fwpdate_cert = NULL;

    /* ---------------------------------------------------------- */
    /* These function calls initialize openssl for correct work.  */
    /* ---------------------------------------------------------- */
    OpenSSL_add_all_algorithms();
    ERR_load_BIO_strings();
    ERR_load_crypto_strings();

    /* ---------------------------------------------------------- */
    /* Create the Input/Output BIO's.                             */
    /* ---------------------------------------------------------- */
    certbio = BIO_new(BIO_s_file());
    /*  polyspace< JUST-MISRA-8.1 :need output error information. No modification: Justify > */
    outbio  = BIO_new_fp(stdout, BIO_NOCLOSE);

    /* ---------------------------------------------------------- */
    /* Load the certificate from file (PEM).                      */
    /* ---------------------------------------------------------- */
    if (BIO_read_filename(certbio, cert_filestr) == 0) {
        printf("%s, %d\n", __FUNCTION__, __LINE__);
        result = false;
    }
    else {
        fwpdate_cert = PEM_read_bio_X509(certbio, NULL, 0, NULL);
        if (fwpdate_cert == NULL) {
            BIO_printf(outbio, "Error loading cert into memory\n");
            printf("%s, %d\n", __FUNCTION__, __LINE__);
            result = false;
        }
        else {

            /* ---------------------------------------------------------- */
            /* Extract the certificate's public key data.                 */
            /* ---------------------------------------------------------- */
            fwpdate_pkey = X509_get_pubkey(fwpdate_cert);
            if (fwpdate_pkey == NULL) {
                BIO_printf(outbio, "Error getting public key from certificate");
                result = false;

            }
            /* ---------------------------------------------------------- */
            /* Print the public key information and the key in PEM format */
            /* ---------------------------------------------------------- */
            /* display the key type and size here */
            if (fwpdate_pkey != NULL) {
                switch (fwpdate_pkey->type) {
                case EVP_PKEY_RSA:
                    BIO_printf(outbio, "%d bit RSA Key\n\n", EVP_PKEY_bits(fwpdate_pkey));
                    break;
                case EVP_PKEY_DSA:
                    BIO_printf(outbio, "%d bit DSA Key\n\n", EVP_PKEY_bits(fwpdate_pkey));
                    break;
                default:
                    BIO_printf(outbio, "%d bit non-RSA/DSA Key\n\n", EVP_PKEY_bits(fwpdate_pkey));
                    break;
                }
            }
            else if(PEM_write_bio_PUBKEY(outbio, fwpdate_pkey) == 0){
                BIO_printf(outbio, "Error writing public key data in PEM format");
            }
            else {
                /* Do nothing */
            }
        }
    }

    /* EVP_PKEY_free(fwpdate_pkey);*/
    X509_free(fwpdate_cert);
    BIO_free_all(certbio);
    BIO_free_all(outbio);
    result = true;
    printf("%s, %d, result =%d \n", __FUNCTION__, __LINE__, result);
    return result;
}


/*============================================================================================
|*==              J                                                                         ==
|*==              Validating signature                                                      ==
|*==    openssl dgst -sha256 -verify secondary_public.pem -signature signature image.cwe*   ==
|*============================================================================================*/

/* polyspace< JUST-MISRA-16.7 : msg have decaared ad const No functional impact and no issue caused. : Justify > */
static int32_t FwUpdateRSAVerifySignature( uint8_t* msg_hash, size_t msg_hash_len, const char* msg, size_t msg_len, int32_t* authentic)
{
    printf("%s, %d\n", __FUNCTION__, __LINE__);
    int32_t result = -1;
    *authentic = 0;
    EVP_MD_CTX* m_RSAVerifyCtx = EVP_MD_CTX_create();

    if ((msg_hash == NULL) || (msg == NULL) || (m_RSAVerifyCtx == NULL) || (fwpdate_pkey == NULL)) {
        printf("%s, %d, msg_hash or msg is NULL\n", __FUNCTION__, __LINE__);
        result = -1;
    }
    else {

        if (EVP_DigestVerifyInit(m_RSAVerifyCtx, NULL, EVP_sha256(), NULL, fwpdate_pkey) <= 0) {
            printf("%s, %d\n", __FUNCTION__, __LINE__);
            result = -1;
        }
        else if (EVP_DigestVerifyUpdate(m_RSAVerifyCtx, msg, msg_len) <= 0) {
            printf("%s, %d\n", __FUNCTION__, __LINE__);
            result = -1;
        }
        else {

            *authentic = EVP_DigestVerifyFinal(m_RSAVerifyCtx, msg_hash, msg_hash_len);
            printf("%s, %d, authentic = %d\n", __FUNCTION__, __LINE__, *authentic);

            EVP_MD_CTX_cleanup(m_RSAVerifyCtx);

            if (*authentic >= 0){
                printf("%s, %d\n", __FUNCTION__, __LINE__);
                result =  1;
            }else {
                printf("%s, %d\n", __FUNCTION__, __LINE__);
                result = -1;
            }
        }
    }
    printf("%s, %d, result = %d\n", __FUNCTION__, __LINE__, result);
    return result;
}



long readFile(const char* srcFile, char* outStr)
{
    int err;
    int sig_len;
    FILE* fp = fopen(srcFile,"rb");
    if (fp == NULL) {
        printf("%s,%d\n", __func__, __LINE__);
    }
    //    fseek(fp, 0L, 512*8);
    long ret = fread(outStr, 1, 2048, fp);
    printf("%s,%d, ret = %ld\n",  __func__, __LINE__, ret);
    fclose(fp);
    return ret;
}

/*
format: gcc command-func.c -lssl -l crypto
*/
int main()
{
    printf("%s,%d\n", __func__, __LINE__);
    if (FwUpdateVerfySecCert() == false) {
        printf("%s,%d, verfy second certificate failed\n",__func__, __LINE__);
    }
    else {
        FwExtracSecondaryKeys();
        unsigned char sig_buf[4096] = {0};
        memset(sig_buf, 0, sizeof(sig_buf));
        long sign_len = readFile("signature", sig_buf);
        sig_buf[sign_len] = '\0';
        unsigned char data_image[4096] = {0};
        memset(data_image, 0, sizeof(data_image));
        long data_len = readFile("data.txt", data_image);
        data_image[data_len] = '\0';
        int32_t authentic;
        int32_t ret = FwUpdateRSAVerifySignature( (uint8_t*)sig_buf, (size_t)512, data_image, data_len, &authentic);
        printf("%s,%d, ret = %d, authentic = %d\n", __func__, __LINE__, ret, authentic);
        if ((ret == 1) && (authentic == 1)) {
            printf("%s, %d, Signature Verified Ok!\n", __func__, __LINE__);
        }
        else {
            printf("%s, %d, Signature Verified Failed!, ERR_get_error = %ld \n", __func__, __LINE__, ERR_get_error());
}
}
    return 0;
}

