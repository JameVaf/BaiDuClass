#include<iostream>
#include<unistd.h>

#include "server.h"

Server::Server()
{
    std::cout << "构造成功" << std::endl;
}

Server::~Server()
{
    std::cout << "析构成功" << std::endl;
}

void Server::run()
{
    while(true)
    {
        std::cout << "run ..................." << std::endl;
        ::usleep(1000000);  //等待1秒钟
    }
};