#include "common.h"
#include  "session.h"
#include  "sysutils.h"
#include    "ftp_protocol.h"
#include    "private_parent.h"

void begin_session(session_t &sess)
{
    //将父进程改为nobody进程,(本来是root用户)
    struct passwd *pw = getpwnam("nobody");
    if(NULL == pw)
    {
        err_exit("getpwnam");
    }
    //注意更改顺序,先改组id再改用户id;因为可能改了用户id后没有权限改主id
    if( setgid(pw->pw_gid) < 0 )
    {
        err_exit("setgid");
    }
    if(setuid(pw->pw_uid) < 0)
    {
        err_exit("setuid");
    }

    //使用socketpair进行父子进程间通信
    int sockfds[2];
    if(socketpair(AF_UNIX,SOCK_STREAM,0,sockfds) < 0)
    {
        err_exit("socketpair");
    }

    //为每个连接创建两个进程
    pid_t pid;
    pid = fork();
    if(pid < 0)
    {
        err_exit("fork");
    }

    if(0 == pid)
    {
        //子进程是服务进程
        
        close(sockfds[0]);
        sess.child_fd = sockfds[1];
        handle_child(sess);
    }
    else
    {
        




        close(sockfds[1]);
        sess.parent_fd = sockfds[0];
        handle_parent(sess);
    }


}
