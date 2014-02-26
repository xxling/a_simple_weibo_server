#include "protocol.h"

void message_read(int socket_fd, void *message)
{
    int recv_len = 0;
    int data_length = 0;
    int len;
    message_t *m = (message_t *)message;

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
    data_length = m->length;
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

void message_set(void *message, uint8_t type, uint32_t length, void *data)
{
    message_t *m = (message_t *)message;
    m->type = type;
    m->length = length;

    m->data = (char *)malloc(sizeof(length) * sizeof(char));
    memcpy(m->data, data, length);
}

void check_type(void *message)
{
    message_t *m = (message_t *)message;
    
}

uint32_t get_length(void *message)
{
    message_t *m = (message_t *)message;

    return (uint32_t)m->length;
}
