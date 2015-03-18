/*************************************************************************
	> File Name: ftp_protocol.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年03月18日 星期三 14时45分05秒
 ************************************************************************/

#include  <iostream>
#include    "session.h"
#include    "sysutils.h"
using namespace std;


//与客户端进行交互,解析ftp命令与参数,处理命令.
//可能需要父进程的协助
void handle_child(session_t& sess)
{
    //发送登录成功的欢迎信息
    const char *welcome = "220 miniftpd service\r\n";
    writen(sess.ctrl_fd,(void *)(welcome),strlen(welcome));

    //登录成功后,将ftp进程的用户改为当前登录的用户
    //ftp进程的权限相对降低了,所以需要一个nobody进程进行协助

    while(1)
    {
        bzero(sess.cmdline,sizeof(sess.cmdline));
        bzero(sess.arg,sizeof(sess.arg));
        bzero(sess.cmd,sizeof(sess.cmd));

        //ctrl_fd是于客户端连接的sock号
        readline(sess.ctrl_fd,sess.cmd,MAX_COMMAND_LINE);
        //解析命令与参数




    }


}





