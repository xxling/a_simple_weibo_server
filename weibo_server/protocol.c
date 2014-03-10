#include "protocol.h"

message_t  *message_read(int socket_fd)
{
    int recv_len = 0;
    int data_length = 0;
    int len;
    message_t *m = (message_t *)malloc(sizeof(message_t));

    while(recv_len < HEAD_SIZE)
    {
        len = recv(socket_fd, m, HEAD_SIZE - recv_len, 0);
        if(len > 0)
        {
            recv_len += len;
        }
    }

    recv_len = 0;
    data_length = get_length(m);
    m->data  = (char *)malloc(data_length * sizeof(char));
    while(recv_len < data_length)
    {
        len = recv(socket_fd, m->data, data_length - recv_len, 0);
        if(len > 0)
        {
            recv_len += len;
        }
    }

    recv_len = 0;
    while(recv_len < CS_SIZE)
    {
        len = recv(socket_fd, m->cs, CS_SIZE - recv_len, 0);
        if(len > 0)
        {
            recv_len += len;
        }
    }

    return m;

}

void message_write(int socket_fd, void *message)
{
    int send_len = 0;
    int len = 0;
    int data_length = 0;
    message_t *m = (message_t *)message;
        
    while(send_len < HEAD_SIZE)
    {
        len = send(socket_fd, m, HEAD_SIZE - send_len, 0);
        if(len > 0)
        {
            send_len += len;
        }
    }

    send_len = 0;
    data_length = get_length(m);
    while(send_len < data_length)
    {
        len = send(socket_fd, m->data, data_length - send_len, 0);
        if(len > 0)
        {
            send_len += len;
        }
    }

    send_len = 0;
    while(send_len < CS_SIZE)
    {
        len = send(socket_fd, m->cs, CS_SIZE - send_len, 0);
        if(len > 0)
        {
            send_len += len;
        }
    }
    
}

message_t *message_new(uint8_t type, uint32_t length, uint32_t uid, void *data)
{
    message_t *m = (message_t *)malloc(sizeof(message_t));
    memset(m, 0, sizeof(message_t));
    (m->head).type = type;
    (m->head).length = length;
    (m->head).uid = uid;

    m->data = (char *)malloc(length * sizeof(char));
    memset(m->data, 0, length * sizeof(char));
    memcpy(m->data, data, length);
    return m;
}

void message_free(void *message)
{
    message_t *m = (message_t *)message;
    free(m->data);
    free(m);
}

uint8_t message_type(void *message)
{
    message_t *m = (message_t *)message;
    return (m->head).type;
}

uint32_t get_length(void *message)
{
    message_t *m = (message_t *)message;

    return (m->head).length;
}

uint32_t get_uid(void *message)
{
    message_t *m = (message_t *)message;
    
    return (m->head).uid;
}
