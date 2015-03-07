/*************************************************************************
	> File Name: main.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月25日 星期三 11时05分20秒
 ************************************************************************/

#include  <iostream>
#include  "sysutils.h"
#include    "network_service.h"


using namespace std;

int main(void)
{

    //需要root用户启动
    /*
    if(0 != getuid())
    {
        cerr << "miniftp must be started as root" << endl;
        exit(EXIT_FAILURE);
    }
    */


    //忽略子进程结束
    signal(SIGCHLD,SIG_IGN);

    //暂时写为5188
    int listenfd = tcp_server(NULL,5188);
   
    server_service_readline(listenfd);


    return 0;
}


