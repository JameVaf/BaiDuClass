#include<stdio.h>
#include "server.h"

int main(int argc,char* argv[])
{
    // 注册 SIGPIPE 信号处理函数
    signal(SIGPIPE, sigpipe_handler);
    
    if(argc != 3)
    {
        printf("please input: ./a.out <port> <path>");
        return -1;
    }
    unsigned short port = atoi(argv[1]);
    //切换工作目录
    chdir(argv[2]);
    // 1.初始化监听套接字
    int lfd = initListenFd(port);

    //启动服务器程序
    epollRun(lfd);
    return 0;
}

