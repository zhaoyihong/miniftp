/*************************************************************************
	> File Name: client.cpp
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

    //连接到tcp服务器
    int sockfd = tcp_client(NULL,5188); 
    
    
    char ip[100] = {
        0
    };
    int port = 0;

    
    getlocalport(sockfd,&port,ip);
    cout << ip << ":" << port <<  endl;
   
    getlocalip(ip);
    cout << ip << endl;


    client_service_readline(sockfd);    
    


    return 0;
}


