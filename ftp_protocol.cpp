/*************************************************************************
	> File Name: ftp_protocol.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年03月18日 星期三 14时45分05秒
 ************************************************************************/

#include  <iostream>
#include    "session.h"
#include    "sysutils.h"
#include    "str.h"
using namespace std;


//与客户端进行交互,解析ftp命令与参数,处理命令.
//可能需要父进程的协助
void handle_child(session_t& sess)
{
    //发送登录成功的欢迎信息.
    //注意命令格式 命令码 信息\r\n
    const char *welcome = "220 miniftpd service\r\n";
   
    writen(sess.ctrl_fd,(void *)(welcome),strlen(welcome));

    //登录成功后,将ftp进程的用户改为当前登录的用户
    //ftp进程的权限相对降低了,所以需要一个nobody进程进行协助

    int ret;
    while(1)
    {
        bzero(sess.cmdline,sizeof(sess.cmdline));
        bzero(sess.arg,sizeof(sess.arg));
        bzero(sess.cmd,sizeof(sess.cmd));

        //ctrl_fd是于客户端连接的sock号
        ret = readline(sess.ctrl_fd,sess.cmdline,MAX_COMMAND_LINE);
        if(-1 == ret)
        {
            //todo: 关闭前关闭nobody进程.

            err_exit("readline");
        }
        else if(0 == ret)
        {
           //todo: 关闭前关闭nobody进程. 
            exit(EXIT_SUCCESS);
        }
          
        //解析命令与参数
        #ifdef DEBUG
        printf("[%s]\n",sess.cmdline);
        #endif
        //1 去除\r\n
        //2 将字符串分割成两段 
        
        str_trim_crlf(sess.cmdline);
        #ifdef DEBUG
        printf("[%s]\n",sess.cmdline);
        #endif
        
        str_split(sess.cmdline,sess.cmd,sess.arg,' ');
        #ifdef DEBUG
        printf("cmd:[%s],arg:[%s]\n",sess.cmd,sess.arg);
        #endif 



    }


}





