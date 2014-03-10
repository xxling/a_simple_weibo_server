#ifndef LOGIN_H
#define LOGIN_H

#include "message_queue.h"
#include "user_db.h"
#include "protocol.h"
#include "message_queue.h"
#include "user_queue.h"
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

#define LOGIN_SUCCESS_MESSAGE "Welcome to weibo server 1.0 by Charles\0"
#define LOGIN_FAILURE_MESSAGE "Username or Password is wrong, please check!\0"
#define LOGIN_REPEAT_MESSAGE "You have logined before\0"

typedef struct server_login_message_t
{
    char message[MAX_MESSAGE_SIZE]; //remind the client whether success login or not
}server_login_message_t;


void* process_login(void *args);
#endif
