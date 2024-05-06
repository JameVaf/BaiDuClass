#include "server.h"


//初始化监听套接字
SOCKET initListenFd(unsigned short port)
{
    // 1.创建套截字
    SOCKET lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd == -1)
    {
        perror("socket() failed");
        return -1;
    }

    // 2.设置端口复用
    int opt = 1;
    int ret = setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (-1 == ret)
    {
        perror("setsockopt() failed");
        return -1;
    }

    // 3.bind 地址
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    ret = bind(lfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (-1 == ret)
    {
        perror("bind() failed");
        return -1;
    }

    // 4.监听客户端
    ret = listen(lfd, 128);
    if (-1 == ret)
    {
        perror("listen() failed");
        return -1;
    }

    return lfd;
}

// 启动epoll
int epollRun(SOCKET lfd)
{
    //1.首先创建epoll实例
    int epfd = epoll_create(1);
    if(-1 == epfd)
    {
        perror("epoll_create() failed");
        return -1;
    }

    //2.将lfd 添加到epoll
    struct epoll_event ev;
    ev.data.fd = lfd;
    ev.events = EPOLLIN;
    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, lfd,&ev );
    if(-1 == ret)
    {
        perror("epoll_ctl() add fd: failed");
        return -1;
    }
    //3.检测 事件
    struct epoll_event evs[1024];
    while (true)
    {
        int num = epoll_wait(epfd, evs, 1024, -1);
        for (int i = 0; i < num;++i)
        {
            int fd = evs[i].data.fd;
            if(fd == lfd)//建立新连接
            {
                acceptClient(fd, epfd);
            }
            else // 进行通信
            {
                //接受客户端的数据
                recvHttpRequest(fd, epfd);
            }
        }
    }
}

// 接受客户端连接
int acceptClient(SOCKET lfd,int epfd)
{
    struct sockaddr_in clientAddr;
    memset(&clientAddr, 0, sizeof(clientAddr));
    SOCKET newClientFd = accept(lfd, NULL, NULL);
    if (-1 == newClientFd)
    {
        perror("accept() failed");
        return -1;
    }
    // 2.设置非阻塞
    int flag = fcntl(newClientFd, F_GETFL);
    flag |= O_NONBLOCK;
    fcntl(newClientFd, F_SETFL, flag);

    // 3.将文件描述符添加epoll
    struct epoll_event ev;
    ev.data.fd = newClientFd;
    ev.events = EPOLLIN | EPOLLET;
    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, newClientFd, &ev);
    if (-1 == ret)
    {
        perror("epoll_ctl() add  newfd in epoll failed");
        return -1;
    }
    return 0;
}

// 接受http请求
int recvHttpRequest(SOCKET cfd, int epfd)
{
    printf("开始接受连接\n");
    int len = 0;
    int totle = 0;
    char temp[1024] = {0};
    char buff[4096] = {0};
    while( (len = recv(cfd,temp,sizeof(temp),0))>0)
    {
        if(totle + len<sizeof buff)
        {
            memcpy(buff+totle, temp, len);
        }
        totle += len;
    }
    //判断数据是否接受完毕
    if(len == -1 && errno == EAGAIN)
    {
        //printf("%s", buff);
        // 解析请求行
        char *pt = strstr(buff, "\r\n");
        int reqLen = pt - buff;
        buff[reqLen] = '\0';
        parseRequestLine(buff, cfd);
    }
    else if(len == 0)
    {
        //客户端断开连接
        epoll_ctl(epfd, EPOLL_CTL_DEL, cfd, NULL);
        close(cfd);
        cfd = -1;
    }
    else{
        //程序发生错误
        perror("recv() failed");
    }
    return 0;
}

// 解析请求行
int parseRequestLine(const char *line, int cfd)
{
    //解析请求行
    char method[12] = {0};
    char path[1024] = {0};
    char temppath[1024] = {0};
    sscanf(line, "%[^ ] %[^ ]", method, temppath);
    if(strcasecmp(method,"get") != 0)
    {
        return -1;
    }
    decodeMsg(path, temppath);
    printf("method:%s path:%s\n", method, path);
    // 处理客户端请求的静态资源
    char *file = NULL;
    if(strcmp(path,"/") == 0)
    {
        file = "./";
    }
    else{
        file = path + 1;
    }
////////    
    printf("fileName:%s\n", file);
    // 获得文件属性
    struct stat st;
    int ret = stat(file, &st);
    if(-1 == ret)
    {
        //文件不存在 --回复一个404页面
        sendHeadMsg(cfd, 404, "Not Found", getFileType(".html"), -1);
        sendFile("404.html", cfd);
        return 0;
    }
    //printf("method: %s,path:%s,file:%s", method, path,file);

    // 判断文件类型
    // 判断是不是文件夹
    if(S_ISDIR(st.st_mode))
    {
        //把本地目录的内容发送给客户端
        sendHeadMsg(cfd, 200, "OK", getFileType(".html"), -1);
        sendDir(file, cfd);
       // char buf[4096] = {0};
       // sprintf(buf, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><head><title>Hello</title></head><body><h1>Hello, World!</h1></body></html>");
       // send(cfd, buf, strlen(buf), 0);
    }
    else
    {
        //把文件内容发送给客户端
        sendHeadMsg(cfd, 200, "OK", getFileType(file), st.st_size);
        sendFile(file, cfd);
    }

    return 0;
}

// 发送文件
int sendFile(const char *fileName, SOCKET cfd)
{

    int fd = open(fileName, O_RDONLY);
    assert(fd > 0);
#if 0
    while(true)
    {
        char buff[1024] = {0};
        int len = read(fd, buff, sizeof(buff));
        if(len > 0)
        {
            send(cfd, buff, sizeof(buff));
            usleep(10); //让程序休眠10微秒
        }
        else if( len == 0)
        {
            break;
        }
        else{
            perror("read() failed");
        }
    }
#endif
    off_t offset = 0;
    int size = lseek(fd, 0, SEEK_END);
    printf("neng send file size:%d\n", size);
    lseek(fd, 0, SEEK_SET);
    while(offset < size)
    {
        int ret = sendfile(cfd, fd, &offset, size-offset);
        if(ret == -1 && errno == EAGAIN)
        {
           // printf("没数据..\n");
        }
        if (ret == -1 )
        {
           // perror("sendfile() failed");
           if (errno == EPIPE)
           {
               // 连接已经关闭，处理 "broken pipe" 错误
               printf("Connection closed by peer\n");
           }
        }
        else
        {
            printf("sucess send %d bytes\n", ret);
        }
       sleep(1);
    }
///////
    printf("sendfile over\n");

    close(fd);
    fd = -1;
    return 0;
}

// 发送响应头(状态行,响应头)
int sendHeadMsg(int cfd, int status, const char *descr, const char *type, int length)
{
    
    // 1.状态行
    char buf[4096] = {0};
    sprintf(buf, "HTTP/1.1 %d %s\r\n", status, descr);
    //响应头
    sprintf(buf+strlen(buf),"Content-Type: %s\r\n",type);
    //sprintf(buf + strlen(buf), "content-length: %d\r\n", length);
    sprintf(buf + strlen(buf), "\r\n");

    send(cfd, buf, strlen(buf), 0);
    printf("head message:%s\n\n", buf);

    return 0;
}

// 根据文件名获取HTTP Content - type
const char *getFileType(const char *fileName)
{
    const char *dot = strrchr(fileName, '.');

    // 常见文本类型
    if(strcmp(dot,".txt") == 0)
    {
        return "text/plain";
    }
    if (strcmp(dot, ".html") == 0)
    {
        return "text/html; charset=utf-8";
    }
    if (strcmp(dot, ".css") == 0)
    {
        return "text/css";
    }
    if (strcmp(dot, ".js") == 0)
    {
        return "text/javascript";
    }
    if (strcmp(dot, ".csv") == 0)
    {
        return "text/csv";
    }
    if (strcmp(dot, ".xml") == 0)
    {
        return "application/xml";
    }
    if (strcmp(dot, ".json") == 0)
    {
        return "application/json";
    }
    if (strcmp(dot, ".md") == 0)
    {
        return "text/markdown";
    }

    //常见图像类型
    if (strcmp(dot, ".jpg") == 0 || strcmp(dot,".jpeg")==0)
    {
        return "iamge/jpg";
    }
    if (strcmp(dot, ".png") == 0)
    {
        return "image/png";
    }
    if (strcmp(dot, ".gif") == 0)
    {
        return "image/gif";
    }
    if (strcmp(dot, ".bmp") == 0)
    {
        return "image/bmp";
    }
    if (strcmp(dot, ".svg") == 0)
    {
        return "image/svg+xml";
    }

    //音频文件类型
    if (strcmp(dot, ".mp3") == 0)
    {
        return "audio/mp3";
    }
    if (strcmp(dot, ".ogg") == 0)
    {
        return "audio/ogg";
    }
    if (strcmp(dot, ".wav") == 0)
    {
        return "audio/wav";
    }
    if (strcmp(dot, ".flac") == 0)
    {
        return "audio/flac";
    }

    //视频文件类型
    if (strcmp(dot, ".mp4") == 0)
    {
        return "audio/mp4";
    }
    if (strcmp(dot, ".ogv") == 0)
    {
        return "audio/ogg";
    }
    if (strcmp(dot, ".avi") == 0)
    {
        return "audio/x-msvideo";
    }
    if (strcmp(dot, ".mov") == 0)
    {
        return "audio/quicktime";
    }
    if (strcmp(dot, ".mkv") == 0)
    {
        return "audio/x-matroska";
    }

    //压缩文件类型
    if (strcmp(dot, ".zip") == 0)
    {
        return "application/zip";
    }
    if (strcmp(dot, ".tar") == 0)
    {
        return "application/x-tar";
    }
    if (strcmp(dot, ".gz") == 0)
    {
        return "application/gzip";
    }
    if (strcmp(dot, ".bz2") == 0)
    {
        return "application/x-bzip2";
    }
    if (strcmp(dot, ".xz") == 0)
    {
        return "application/x-xz";
    }

    //应用程序类型
    if (strcmp(dot, ".exe") == 0)
    {
        return "application/octet-stream";
    }
    if (strcmp(dot, ".apk") == 0)
    {
        return "application/vnd.android.packge-archive";
    }
    if (strcmp(dot, ".deb") == 0)
    {
        return "application/x-debian-package";
    }
    if (strcmp(dot, ".rpm") == 0)
    {
        return "application/x-rpm";
    }

    return "text/plain; charset=utf-8";
}

// 发送目录
int sendDir(const char *dirName, SOCKET cfd)
{
 
    char buf[4096] = {0};
    sprintf(buf, "<html><head><title>%s</title></head><body><table>", dirName);
    struct dirent **namelist;
    int num = scandir(dirName, &namelist,NULL,alphasort);
    
    for (int i = 0; i < num; ++i)
    {
        //取出文件名
        char *name = (namelist[i])->d_name;
        
        struct stat st;
        char subPath[4096] = {0};
        sprintf(subPath, "%s/%s", dirName, name);
        stat(subPath, &st);
        if(S_ISDIR(st.st_mode))
        {
            sprintf(buf + strlen(buf), "<tr><td><a href=\"%s/\">%s</a></td><td>%ld</td></tr>", 
            name,name, st.st_size);
        }
        else
        {
            sprintf(buf + strlen(buf), 
            "<tr><td><a href=\"%s\">%s</a></td><td>%ld</td></tr>",
                    name, name, st.st_size);
        }
        int size = strlen(buf);
        int sendlen = send(cfd, buf, size, 0);
      
        memset(buf, 0, sizeof(buf));
        free(namelist[i]);
    }
    printf("Dir file number:%d", num);
    sprintf(buf, "</table></body></html>");
  
    int sendlen = send(cfd, buf, strlen(buf), 0);

    free(namelist);

    return 0;
}

// 将字符转化为整形
int hextToDec(char c)
{
    if(c >= '0' && c<='9')
    {
        return c - '0';
    }
    if(c >= 'a' && c <= 'z')
    {
        return c - 'a'+10;
    }
    if(c>='A' && c<='Z')
    {
        return c - 'A'+10;
    }
    return 0;
}

// 解码
//  to 存贮解码之后的数据,传出参数,from是被解码的数据,传入参数
void decodeMsg(char *to, char *from)
{
    for (; *from != '\0';++to,++from)
    {
        //isxgidit -> 判断字符是不是16进制格式,取值 0-f
        //
        if (from[0] == '%' && isxgidit(from[1]) && isxgidit(from[2]))
        {
            *to = hextToDec(from[1]) * 16 + hextToDec(from[2]);
            from += 2;
        }
        else
        {
            *to = *from;
        }
    }
}

// 判断是不是16进制
int isxgidit(char c)
{
    return c >= '0' && c <= 'f' ? 1 : 0;
}

// SIGPIPE 信号处理函数
void sigpipe_handler(int sig)
{
    printf("Received SIGPIPE signal\n");
    // 可以在这里进行一些处理，比如重新建立连接等
}

// 对文件切片发送
int sendSliceFile(const char *fileName, SOCKET cfd)
{
    FILE* file = open(fileName,O_RDONLY);
    if(NULL == file)
    {
        printf("open %s failed\n", fileName);
        return -1;
    }
}