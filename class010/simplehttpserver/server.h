#ifndef __SERVER_H__
#define __SERVER_H__
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include<sys/epoll.h>
#include<fcntl.h>
#include<errno.h>   
#include<string.h>
#include<sys/stat.h>
#include<assert.h>
#include<sys/sendfile.h>
#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
#include<signal.h>

#define SOCKET int

// 初始化监听套接字
SOCKET initListenFd(unsigned short port);

//启动epoll
int epollRun(SOCKET lfd);

//接受客户端连接
int acceptClient(SOCKET lfd,int epfd);

// 接受http请求
int recvHttpRequest(SOCKET cfd, int epfd);

//解析请求行
int parseRequestLine(const char *line, int cfd);

//发送文件
int sendFile(const char *fileName, SOCKET cfd);

//发送响应头(状态行,响应头)
int sendHeadMsg(int cfd, int status, const char *descr, const char *type, int length);

// 根据文件名获取HTTP Content - type 
const char *getFileType(const char *fileName);

//发送目录
int sendDir(const char *dirName, SOCKET cfd);

//将字符转化为整形
int hextToDec(char c);

//解码
// to 存贮解码之后的数据,传出参数,from是被解码的数据,传入参数
void decodeMsg(char *to, char *from);

//判断是不是16进制
int isxgidit(char c);

// SIGPIPE 信号处理函数
void sigpipe_handler(int sig);

//对文件切片发送
int sendSliceFile(const char *fileName, SOCKET cfd);

#endif //__SERVER_H__