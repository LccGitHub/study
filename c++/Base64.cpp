#include"Base64.h"

const unsigned char Base64::s_enBaseTable64[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const unsigned char Base64::s_deBaseTable64[256] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,62,0,0,0,63,52,53,54,55,56,57,58,59,60,61,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,0,0,0,0,0,0,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51};
Base64::Base64()
{
    printf("Base64::%s \n", __func__);
}
Base64::~Base64()
{
    printf("Base64::%s \n", __func__);
}
/*----------------------------------------------------------
 * Base64是将每3个字符转化为4个字符，即（3*8bit=4*6bit），如果文本结尾不足3个字符，对转化为6为字符后，
 * 后面剩余的二进制位可能是2位或者4位（因为是N%6），余数为0时代表整除了，在剩余二进制位后面补0至6个二进制位，
 * 再在结尾加=号，使编码后的字符满足（N*8+等号个数）/6=base64的字符个数，说白了，如果N*8%6后余2个二进制位，
 * 就补2个=，余4个二进制位就补一个=，整除不补=。
 ---------------------------------------------------*/
int Base64::encodeBase64(const unsigned char* inStr, unsigned char* outStr, int outStrSize)
{
    int result = 0;
    if ((inStr == NULL) || (outStr == NULL)) {
        result = 1;
    }
    else {
        long inStrLen = 0, len = 0;
        inStrLen = strlen((const char*)inStr);
        if (0 == (inStrLen % 3)) {
            len = (inStrLen / 3) * 4;
        }
        else {
            len = (inStrLen / 3 + 1) * 4;
        }
        if (outStrSize < (len + 1)) {
            result = 2;
        }
        else {
            int i = 0, j = 0;
            for (i = 0, j = 0; i < len -2;j += 3, i += 4) {
                /*取出第一个字符的前6位并找出对应的结果字符*/
                outStr[i] = s_enBaseTable64[inStr[j] >> 2];
                /*将第一个字符的后位与第二个字符的前4位进行组合并找到对应的结果字符*/
                outStr[i + 1] = s_enBaseTable64[((inStr[j] & 0x3) << 4) | (inStr[j + 1] >> 4)];
                /*将第二个字符的后4位与第三个字符的前2位组合并找出对应的结果字符*/
                outStr[i + 2] = s_enBaseTable64[((inStr[j + 1] & 0xf) << 2) | (inStr[j + 2] >> 6)];
                /*取出第三个字符的后6位并找出结果字符*/
                outStr[i + 3] = s_enBaseTable64[(inStr[j + 2] & 0x3f)];
            }

            switch(inStrLen % 3) {
            case 1:
                outStr[i -2] = '=';
                outStr[i -1] = '=';
                break;
            case 2:
                outStr[i -1] = '=';
                break;
            default:
                /* do nothing */
                break;
            }
            outStr[strlen((const char*)outStr) + 1] = 0;
        }

    }
    return result;
}

int Base64::decodeBase64(const unsigned char* inStr, unsigned char* outStr, int outStrSize)
{
    int result = 0;
    if ((inStr == NULL) || (outStr == NULL)) {
        result = 1;
    }
    else {
        long inStrLen = 0, len = 0;
        /* get outStr len */
        inStrLen = strlen((const char*)inStr);
        if (strstr((const char*)inStr, "==")) {
            len = (inStrLen / 4) * 3 - 2;
        }
        else if (strstr((const char*)inStr, "=")) {
            len = (inStrLen / 4) * 3 - 1;
        }
        else {
            len = (inStrLen / 4) * 3;
        }


        /* outStrLen is not satify compute len */
        if (outStrSize < (len + 1)) {
            result = 2;
        }
        else {
            int i = 0, j = 0;
            memset(outStr, 0, outStrSize);
            for (i = 0, j = 0; i < inStrLen -2;j += 3, i += 4) {
                /*取出第一个字符对应base64表的十进制数的前6位与第二个字符对应base64表的十进制数的后2位进行组合*/
                outStr[j] = ((s_deBaseTable64[inStr[i]] <<2) & 0xFC) | ((s_deBaseTable64[inStr[i + 1]] >> 4) & 0x03) ;
                /*取出第二个字符对应base64表的十进制数的后4位与第三个字符对应bas464表的十进制数的后4位进行组合*/
                outStr[j + 1] = ((s_deBaseTable64[inStr[i + 1]] << 4 ) & 0xF0) | ((s_deBaseTable64[inStr[i + 2]] >> 2) & 0x0F) ;
                /*取出第三个字符对应base64表的十进制数的后2位与第4个字符进行组合*/
                outStr[j + 2] = ((s_deBaseTable64[inStr[i + 2]] << 6) & 0xCF) | (s_deBaseTable64[inStr[i + 3]] & 0x3F);
            }
            outStr[strlen((const char*)outStr) + 1] = 0;
        }

    }
    return result;
}


int main()
{
    Base64 base64;
    unsigned char enResult[512] = {0};
    base64.encodeBase64((const unsigned char*)"hello world", enResult, sizeof(enResult));
    printf("encode result =[%s] \n", enResult);


    unsigned char deResult[512] = {0};
    base64.decodeBase64((const unsigned char*)enResult, deResult, sizeof(deResult));
    printf("decode result =[%s] \n", deResult);
    return 0;
}

