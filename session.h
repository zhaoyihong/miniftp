#ifndef _SESSION_H
#define _SESSION_H
#include "common.h"


struct session_t
{
    session_t()
    {
        ctrl_fd = parent_fd = child_fd = -1;
        memset(cmdline,0,sizeof(cmdline));
        memset(cmd,0,sizeof(cmd));
        memset(arg,0,sizeof(arg));
    }


    //控制连接
    int ctrl_fd;
    char cmdline[MAX_COMMAND_LINE];
    char cmd[MAX_CMD];
    char arg[MAX_ARG];
    //父子进程间通道
    int parent_fd,child_fd;

};

void begin_session(session_t& sess);





#endif
