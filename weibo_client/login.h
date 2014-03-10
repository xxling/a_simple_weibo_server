#ifndef LOGIN_H
#define LOGIN_H

#include "protocol.h"
#include "weibo.h"
#include <stdio.h>

#define MAX_USERNAME_SIZE 255
#define MAX_PASSWORD_SIZE 255

#define MAX_MESSAGE_SIZE 255

typedef struct client_login_message_t
{
    char username[MAX_USERNAME_SIZE];
    char password[MAX_PASSWORD_SIZE];
}client_login_message_t;

typedef struct server_login_message_t
{
    char message[MAX_MESSAGE_SIZE]; //remind the client whether success login or not
}server_login_message_t;


void process_login(int socket_fd, const char *username, const char *password);
#endif
