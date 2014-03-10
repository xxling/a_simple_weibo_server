#include "weibo.h"

void *listen_message_in(void *socket_fd)
{
    int *server_fd = (int *)socket_fd;
    int client_fd;
    struct sockaddr_in client;
    int len = sizeof(struct sockaddr_in);
    message_t *message;

    while(1)
    {
        client_fd = accept(*server_fd, (struct sockaddr *)&client, &len);
        if(client_fd == -1)
        {
            continue;
        }
        
        message = message_read(client_fd);
        process_message_in((void *)message, client_fd);       
    }
}

void process_message_in(void *message, int client_fd)
{
    node_t *n;
    message_t *m = (message_t *)message;
    uint8_t type;

    n = create_node((void *)m, client_fd);
    type = message_type(message);
    switch(type)
    {
        case MESSAGE_LOGIN:
            produce_message(&login_queue, n);
            break;
        default:
            break;
    }
}
