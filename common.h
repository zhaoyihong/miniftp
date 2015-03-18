/*************************************************************************
	> File Name: common.h
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月25日 星期三 10时29分53秒
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H

#include  <stdio.h>
#include  <stdlib.h>
#include  <unistd.h>
#include  <sys/socket.h>
#include  <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include  <sys/types.h>
#include  <errno.h>
#include  <fcntl.h>
#include  <sys/epoll.h>
#include  <sys/select.h>
#include  <assert.h>
#include  <signal.h>
#include  <sys/wait.h>
#include  <pwd.h>

#define MAX_COMMAND_LINE  1024
#define MAX_CMD 32
#define MAX_ARG 1024


#endif
