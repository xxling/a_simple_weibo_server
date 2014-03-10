#ifndef WEIBO_H
#define WEIBO_H

#include "protocol.h"
#include "message_queue.h"
#include <netinet/in.h>

#define PORT 5900
#define BACKLOG 5

#define MESSAGE_LOGIN 1
#define MESSAGE_GET 2
#define MESSAGE_POST 3

#define THREAD_NUMS 10

void* listen_message_in(void *socket_fd);
void process_message_in(void *message, int client_fd);

#endif
