#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
struct message
{
    uint8_t type; //data type
    uint32_t length; //data length
    char * data; //data content
    uint8_t cs[16]; //md5 
};
typedef struct message message_t;
#define HEAD_SIZE  (sizeof(uint8_t) + sizeof(uint32_t))
#define CS_SIZE  (16 * sizeof(uint8_t))
void message_read(int socket_fd, void *message);
void message_write(int socket_fd, void *message);
void message_set(void *message, uint8_t type, uint32_t length, void *data);
void check_type(void *message);
uint32_t get_length(void *message);
#endif
