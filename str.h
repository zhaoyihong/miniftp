/*************************************************************************
	> File Name: str.h
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年03月18日 星期三 16时50分41秒
 ************************************************************************/
#ifndef _STR_H
#define _STR_H

//去除\r\n
void str_trim_crlf(char *str);
//字符串分割
void str_split(const char *str,char *left ,char *right,char c);
//判断是否全是空白
int str_all_space(const char *str);
//字符串转化为大写
void str_upper(char *str);
//字符串转化为longlong
long long str_to_longlong(const char *str);
//字符串按照八进制转化为无符号整型
unsigned int str_octal_to_unix(const char *str);

#endif
