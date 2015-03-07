/*************************************************************************
	> File Name: network_service.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年03月04日 星期三 15时39分18秒
 ************************************************************************/

#include  <iostream>
#include  "sysutils.h"
#include  "common.h"

using namespace std;


void server_service_readn(int listenfd)
{
    while(1)
    {
        struct sockaddr_in peeraddr;
        socklen_t peeraddr_len = sizeof(peeraddr);
        
        int conn;
        if( (conn=accept(listenfd,(sockaddr *)&peeraddr,&peeraddr_len)) == -1)
        {
            err_exit("accpet");
        }
        
        puts("client conneted");

        pid_t pid = fork();
        if(pid == -1)
        {
            err_exit("fork");
        }
        else if(pid == 0)
        {
            //子进程反射客户端发来的消息
            close(listenfd);

            char recvbuf[1024];
            while(1)
            {
                memset(recvbuf,0,sizeof(recvbuf));
                int ret = readn(conn,recvbuf,sizeof(recvbuf));
                if(ret == -1)
                {
                    err_exit("readn");
                }
                else if(ret == 0)
                {
                    puts("client closed");
                    break;
                }
                printf("%s",recvbuf);
                if(-1 == writen(conn,recvbuf,sizeof(recvbuf)))
                {
                    err_exit("writen");
                }
            }
            
            exit(EXIT_SUCCESS);
        }
        
        //父进程
        close(conn);
    }
    
}


void client_service_readn(int sockfd)
{
    int epfd = epoll_create1(EPOLL_CLOEXEC);
    if(-1 == epfd)
    {
        err_exit("epoll_create1");
    }

    epoll_event event;
    event.data.fd = fileno(stdin);
    event.events = EPOLLIN | EPOLLET;
    
    if(epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event) < 0)
    {
        err_exit("epoll_ctl");
    }

    
    event.data.fd = sockfd;
    if(epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&event) < 0)
    {
        err_exit("epoll_ctl");
    }

    int nready;
    const int MAX_EVENT_NUM=10;
    epoll_event events[MAX_EVENT_NUM];
    bool stdin_closed = false;
    while(1)
    {
        nready = epoll_wait(epfd,events,MAX_EVENT_NUM,-1);
        
        if(nready == -1)
        {
            if(errno == EINTR)
            {
                continue;
            }

            err_exit("epoll_wait");
        }
        
        if(nready == 0)
        {
            continue;
        }

        for(int i=0;i<nready;++i)
        {
            if(events[i].data.fd == fileno(stdin)  && (events[i].events & EPOLLIN))
            {
                //写入到服务器
                char sendbuf[1024] = {
                    0
                };

                if(fgets(sendbuf,1024,stdin)  != NULL)
                {
                   if(-1 == writen(sockfd,sendbuf,1024))
                    {
                        err_exit("writen");
                    }
                }
                else
                {
                    stdin_closed = true;
                    puts("stdin closed");
                    shutdown(sockfd,SHUT_WR);
                    event.data.fd = fileno(stdin);
                    if(-1 == epoll_ctl(epfd,EPOLL_CTL_DEL,fileno(stdin),&event))
                    {
                        err_exit("epoll_ctl");
                    }
                }

            }
            else if(events[i].data.fd == sockfd && (events[i].events&EPOLLIN)) 
            {
                char recvbuf[1024] = {
                    0
                };

                int nread = readn(sockfd,recvbuf,1024);
                if(nread == -1)
                {
                    err_exit("readn");
                }

                if(nread == 0)
                {
                    if(stdin_closed)
                    {
                        puts("client closed");
                        return;
                    }
                    else
                    {
                        shutdown(sockfd,SHUT_RDWR);
                        puts("server closed");
                        return;
                    }
                }

                printf("%s",recvbuf);
            }
        }
    }

} 





void server_service_readline(int listenfd)
{
    while(1)
    {
        struct sockaddr_in peeraddr;
        socklen_t peeraddr_len = sizeof(peeraddr);
        
        int conn;
        if( (conn=accept(listenfd,(sockaddr *)&peeraddr,&peeraddr_len)) == -1)
        {
            err_exit("accpet");
        }
        
        puts("client conneted");

        pid_t pid = fork();
        if(pid == -1)
        {
            err_exit("fork");
        }
        else if(pid == 0)
        {
            //子进程反射客户端发来的消息
            close(listenfd);

            char recvbuf[1024];
            while(1)
            {
                memset(recvbuf,0,sizeof(recvbuf));
                int ret = readline(conn,recvbuf,sizeof(recvbuf));
                if(ret == -1)
                {
                    err_exit("readn");
                }
                else if(ret == 0)
                {
                    puts("client closed");
                    break;
                }

                printf("%s",recvbuf);

                if(-1 == writen(conn,recvbuf,strlen(recvbuf)))
                {
                    err_exit("writen");
                }
            }
            
            exit(EXIT_SUCCESS);
        }
        
        //父进程
        close(conn);
    }
    
}


void client_service_readline(int sockfd)
{
    int epfd = epoll_create1(EPOLL_CLOEXEC);
    if(-1 == epfd)
    {
        err_exit("epoll_create1");
    }

    epoll_event event;
    event.data.fd = fileno(stdin);
    event.events = EPOLLIN | EPOLLET;
    
    if(epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event) < 0)
    {
        err_exit("epoll_ctl");
    }

    
    event.data.fd = sockfd;
    if(epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&event) < 0)
    {
        err_exit("epoll_ctl");
    }

    int nready;
    const int MAX_EVENT_NUM=10;
    epoll_event events[MAX_EVENT_NUM];
    bool stdin_closed = false;
    while(1)
    {
        nready = epoll_wait(epfd,events,MAX_EVENT_NUM,-1);
        
        if(nready == -1)
        {
            if(errno == EINTR)
            {
                continue;
            }

            err_exit("epoll_wait");
        }
        
        if(nready == 0)
        {
            continue;
        }

        for(int i=0;i<nready;++i)
        {
            if(events[i].data.fd == fileno(stdin)  && (events[i].events & EPOLLIN))
            {
                //写入到服务器
                char sendbuf[1024] = {
                    0
                };

                if(fgets(sendbuf,1024,stdin)  != NULL)
                {
                   if(-1 == writen(sockfd,sendbuf,strlen(sendbuf)))
                    {
                        err_exit("writen");
                    }
                }
                else
                {
                    stdin_closed = true;
                    puts("stdin closed");
                    shutdown(sockfd,SHUT_WR);
                    event.data.fd = fileno(stdin);
                    if(-1 == epoll_ctl(epfd,EPOLL_CTL_DEL,fileno(stdin),&event))
                    {
                        err_exit("epoll_ctl");
                    }
                }

            }
            else if(events[i].data.fd == sockfd && (events[i].events&EPOLLIN)) 
            {
                char recvbuf[1024] = {
                    0
                };

                int nread = readline(sockfd,recvbuf,1024);
                if(nread == -1)
                {
                    err_exit("readn");
                }

                if(nread == 0)
                {
                    if(stdin_closed)
                    {
                        puts("client closed");
                        return;
                    }
                    else
                    {
                        puts("server closed");
                        shutdown(sockfd,SHUT_RDWR);
                        return;
                    }
                }

                printf("%s",recvbuf);
            }
        }
    }
}




