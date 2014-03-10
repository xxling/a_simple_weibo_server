#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct message_head
{
    uint8_t type;
    uint32_t length;
    uint32_t uid;
}message_head_t;

struct message
{
    message_head_t head;  
    char * data; //data content
    uint8_t cs[16]; //md5 
};
typedef struct message message_t;
#define HEAD_SIZE  (sizeof(message_head_t))
#define CS_SIZE  (16 * sizeof(uint8_t))
message_t *message_read(int socket_fd);
void message_write(int socket_fd, void *message);
message_t *message_new(uint8_t type, uint32_t length, uint32_t uid, void *data);
void message_free(void *message);
uint8_t message_type(void *message);
uint32_t get_length(void *message);
uint32_t get_uid(void *message);
#endif
