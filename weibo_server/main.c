#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>


#include "protocol.h"

#define PORT 5900
#define BACKLOG 5

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
    char buf[255] = "send to client";

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

    while(1)
    {

        client_fd = accept(socket_fd, (struct sockaddr *)&client, &len);
        if(client_fd < 0)
        {
            printf("accept failed\n");
            close(socket_fd);
            return -1;
        }

        message_read(client_fd, (void *)&message);
        message_set(&out, 1, strlen(buf) + 1, buf);
        message_write(client_fd, &out);
    }
}
