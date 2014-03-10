#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include "weibo.h"
#include "init.h"

int main(int argc, char *argv[])
{
    int socket_fd;
    int client_fd;
    struct sockaddr_in server;
    struct sockaddr_in client;
    message_t message;
    message_t out;
    int len;
    int ret;
    pthread_t tids[THREAD_NUMS];
    pthread_attr_t attr;
    int i;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd < 0)
    {
        printf("create socket error\n");
        return -1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(5900);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    ret = bind(socket_fd, (struct sockaddr *)&server, sizeof(struct sockaddr));
    if(ret < 0)
    {
        printf("bind error\n");
        close(socket_fd);
        return -1;
    }

    ret = listen(socket_fd, BACKLOG);
    if(ret < 0)
    {
        printf("listen error");
        close(socket_fd);
        return -1;
    }

    init_queues(THREAD_NUMS);
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    for(i = 0; i < THREAD_NUMS; i++)
    {
        pthread_create(&tids[i], &attr, (void *)listen_message_in, (void *)&socket_fd);
    }
    pthread_attr_destroy(&attr);
    
    listen_message_in((void *)&socket_fd);
}
