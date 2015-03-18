/*************************************************************************
	> File Name: private_parent.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年03月18日 星期三 14时47分07秒
 ************************************************************************/

#include  <iostream>
#include  "session.h"
using namespace std;

//协助子进程,处理子进程(ftp服务进程)发送来的命令.
void handle_parent(session_t& sess)
{
    char cmd; //命令码
    while(1)
    {
        read(sess.parent_fd,&cmd,sizeof(1));


    }


}
