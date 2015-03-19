/*************************************************************************
	> File Name: str.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年03月18日 星期三 16时54分34秒
 ************************************************************************/

#include  <iostream>
#include    "common.h"
using namespace std;


/**
 * str_trim_crlf - 去除\r\n
 * str:传入的字符串,去除\r\n后返回
 */
void str_trim_crlf(char *str)
{
    char *p = str+strlen(str)-1;
    while(*p == '\r' || *p == '\n')
    {
        *p = '\0';
        --p;
    }

}

/**
 * str_split - 字符串分割
 * str : 待分割的字符串
 * left : 命令存放位置
 * right : 参数存放位置
 * c : 分隔符
 */
void str_split(const char *str,char *left ,char *right,char c)
{
    char *p = strchr((char *)str,c);
    if(NULL == p)
    {
        strcpy(left,str);
    }
    else
    {
        strncpy(left,str,p-str);
        strcpy(right,p+1);
    }
    
}
 
/**
 * str_all_space - 判断是否全是空白
 * str : 待判断的字符串
 * 如果全是空白字符返回0,否则返回1
 */
int str_all_space(const char *str)
{
    char *p = (char *)str;
    while(*p)
    {
        if(!isspace(*p))
        {
            return 0;
        }
        ++p;
    }

    return 1;
}


////字符串转化为大写
void str_upper(char *str)
{
    char *p = str;
    while(*p)
    {
        *p = toupper(*p);
        ++p;
    }
}


/**
 * str_to_longlong - 字符串转化为longlong
 * str : 待转化的字符串
 * 成功返回longlong
 */
long long str_to_longlong(const char *str)
{
    //return atoll(str);//系统函数

    long long result = 0;
    long long mult = 1;

    int len = strlen(str);
    if(len > 20) 
    {
        return 0;
    }

    int i;
    for(i = len-1; i >= 0; -- i)
    {
        char ch = str[i];
        if(ch < '0' ||  ch > '9')
        {
            return 0;
        }

        result += (ch - '0')*mult; 
        mult *= 10;
    }

    return result;
}

/**
 * str_octal_to_unix - 字符串按照八进制转化为无符号整型
 * str : 八进制的字符串
 * 返回十进制的值
 */
unsigned int str_octal_to_unix(const char *str)
{
    unsigned result = 0;
    unsigned int mult = 1;

    int len = strlen(str);
    if(len > 10) 
    {
        return 0;
    }

    int i;
    for(i = len-1; i >= 0; -- i)
    {
        char ch = str[i];
        if(ch < '0' ||  ch > '7')
        {
            return 0;
        }

        result += (ch - '0')*mult; 
        mult = mult << 3;
    }

    return result;
}
