/*************************************************************************
	> File Name: libcur.c
	> Author: 
	> Mail: 
	> Created Time: Wed 12 Jul 2017 10:46:10 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include <curl/curl.h>
#include <stdlib.h>
#include<string.h>

static const char *USER_AGENT="Ficosa TCU";
CURL *curl;

void HttpClientInit(char *URL)
{
    printf("%s,%d\n",__func__,__LINE__);
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, URL);
    /* Set default options now */

    /* Set proxy */
    //curl_easy_setopt(curl, CURLOPT_PROXY, "172.26.12.53:8080");

    /* Enable strict peer verification */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);

    /* Set User Agent String according to configuration */
    curl_easy_setopt(curl, CURLOPT_USERAGENT, USER_AGENT);

    /* don't followxx redirection */
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 0L);
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 0L);

    /* Allow only http and https (libcurl supports many more, but
    * we want to avoid untested behaviour)*/
    curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS );

    /* A response code >400 from the server is an error, treat it as such*/
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);

    //CurlCleanup();
    printf("%s,%d,[httpClient] Http Client ready\n", __func__,__LINE__);
}

void HttpClientsetCaCertFile()
{
    printf("%s,%d\n",__func__,__LINE__);
    CURLcode res = -1;
    res = curl_easy_setopt(curl, CURLOPT_CAINFO, "cacert.pem"); 

    curl_easy_setopt(curl, CURLOPT_SSLCERTTYPE, "PEM");
    res = curl_easy_setopt(curl, CURLOPT_SSLCERT, "client.crt");

    curl_easy_setopt(curl, CURLOPT_SSLKEYTYPE, "PEM");
    res = curl_easy_setopt(curl, CURLOPT_SSLKEY, "client.key");   
}

int main(int argc, char *argv[])
{
    printf("%s,%d\n",__func__,__LINE__);
    CURLcode res;
    int responseCode = -1;
    if(argc!=2) {
        printf("Usage : file <url>;\n");
    }
    else {
        HttpClientInit(argv[1]);
        if(curl!=NULL) {
            printf("%s,%d, curl is not NULL\n",__func__,__LINE__);
            HttpClientsetCaCertFile(); 
            /* Set proxy */
            curl_easy_setopt(curl, CURLOPT_PROXY, "172.26.12.53:8080");
            /* set proxy user and password */
            curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, "xxx:111111");     
            res = curl_easy_perform(curl);
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
           
            printf("%s,%d,curl_easy_perform=[%d]\n",__func__,__LINE__, res);
            if(res != CURLE_OK){
                printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            }
            printf("%s,%d,responseCode=[%d]\n",__func__,__LINE__, responseCode);
            curl_easy_cleanup(curl);
        }
        else {
            printf("%s,%d, curl == NULL\n",__func__,__LINE__); 
        }
    }
    return 0;
}
