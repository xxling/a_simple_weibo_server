#include "protocol.h"
#include "login.h"
#include "weibo.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

extern int errno;

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5900
#define THREADS 10


int main(int argc, char *argv[])
{
    int socket_fd;
    int ret;
    struct sockaddr_in server;
    char buf[255] = "send to server";
    message_t out;
    message_t in;
    pthread_t tids[THREADS];
    int i;

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd < 0)
    {
        printf("create socket error\n");
        return -1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);

    ret = connect(socket_fd, (struct sockaddr *)&server, sizeof(struct sockaddr));
    if(ret < 0)
    {
        printf("connect error: %d\n", errno);
        return;
    }

    /*for(i = 0; i < THREADS; i++)
    {
        pthread_create(&tids[i], NULL, (void *)chat_with_server, (void *)&server);
    }

    for(i = 0; i < THREADS; i++)
    {
        pthread_join(tids[i], NULL);
    }*/

    process_login(socket_fd, "Charles1", "123456");

    return 0;
    
}

void chat_with_server(void *server)
{
    message_t out;
    message_t in;
    int socket_fd;
    int ret;
    char buf[255] = "send to server";

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    ret = connect(socket_fd, (struct sockaddr *)server, sizeof(struct sockaddr));
    if(ret < 0)
    {
        printf("connect error: %d\n", errno);
        return;
    }

    printf("get message from server: %s\n", in.data);
    pthread_exit((void *)0);
}
