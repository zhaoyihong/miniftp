/*************************************************************************
	> File Name: main.cpp
	> Author:zhaoyihong 
> Mail:zhaoyihong_at_126_dot_com 
> Created Time: 2015年02月25日 星期三 11时05分20秒
************************************************************************/

#include  <iostream>
#include  "sysutils.h"
#include "session.h"

using namespace std;

int main(void)
{

    //需要root用户启动
    if(0 != getuid())
    {
        cerr << "miniftp must be started as root" << endl;
        exit(EXIT_FAILURE);
    }

    //忽略子进程结束
    signal(SIGCHLD,SIG_IGN);

    //会话对象
    session_t sess;

    //int listenfd = tcp_server("192.168.200.100",5188);
    //int listenfd = tcp_server("ubuntu",5188);

    #ifdef DEBUG
    int listenfd = tcp_server(NULL,5188);
    #else 
    int listenfd = tcp_server(NULL,21);
    #endif 

    //测试绑定的ip地址和端口
    #ifdef DEBUG
    sockaddr_in seraddr;
    memset(&seraddr,0,sizeof(seraddr));
    socklen_t serlen = sizeof(seraddr);
    if(-1 == getsockname(listenfd,(sockaddr*)&seraddr,&serlen))
    {
        err_exit("getsockname");
    }
    printf("seraddr:%s:%d\n",inet_ntoa(seraddr.sin_addr),ntohs(seraddr.sin_port));
    #endif

    int conn; //已连接套接字
    while(1)
    {
        conn = accept_timeout(listenfd,NULL,0);
        if(-1 == conn)
        {
            err_exit("accept");
        }

        pid_t pid = fork();
        if(-1 == pid)
        {
            err_exit("fork");
        }

        if(0 == pid)
        {
            //子进程
            close(listenfd);
            //处理连接会话
            sess.ctrl_fd = conn;
            begin_session(sess);
        }
        else 
        {
            //父进程
            close(conn);
        }
    }
    return 0;
}


