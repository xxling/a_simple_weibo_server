#ifndef USER_QUEUE_H
#define USER_QUEUE_H
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

typedef struct user_t
{
    uint32_t uid;
    uint32_t timestamp;
    struct user_t *next;
}user_t;

typedef struct u_queue_t
{
    pthread_rwlock_t lock;
    user_t *head;
    user_t *tail;
}u_queue_t;

#define NOW() (get_timestamp())

void init_user_queue(u_queue_t *u);
void add_user(u_queue_t *u, user_t *user);
void delete_user(u_queue_t *u, uint32_t uid);
user_t *find_user(u_queue_t *u, uint32_t uid);
void update_user_timestamp(u_queue_t *u, uint32_t uid, uint32_t now);
uint32_t get_timestamp(void);
extern u_queue_t user_queue;

#endif
