#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include "protocol.h"
#include <pthread.h>
#include <stdio.h>

#define MAX_QUEUE_SIZE 50
#define NUMBER_THREADS 10

typedef struct node_t
{
    message_t *msg;
    unsigned uid;
    int client_fd;
    struct node_t *next;
}node_t;

typedef struct 
{
    int mq_max_queue_size;
    int mq_cur_queue_size;
    pthread_mutex_t mq_lock;
    pthread_cond_t mq_empty;
    pthread_cond_t mq_full;
    pthread_cond_t mq_not_full;
    pthread_cond_t mq_not_empty;
    node_t *mq_head;
    node_t *mq_tail;
    pthread_t *tids;
}mq_t;

node_t *create_node(void *m, int client_fd);
void free_node(void *n);
void init_message_queue(mq_t *m_queue, int number_threads, void *(func)(void *));
void produce_message(mq_t *m_queue, node_t *n);
node_t *consume_message(mq_t *m_queue);

extern mq_t message_out_queue;
extern mq_t login_queue;
#endif
