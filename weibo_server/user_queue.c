#include "user_queue.h"

u_queue_t user_queue;

void init_user_queue(u_queue_t *u)
{
    pthread_rwlock_init(&(u->lock), NULL);
    u->head = NULL;
    u->tail = NULL;
}

void add_user(u_queue_t *u, user_t *user)
{
    pthread_rwlock_wrlock(&(u->lock));
    if(u->head == NULL)
    {
        u->head = user;
        u->tail = user;
        user->next = NULL;
    }
    else
    {
        u->tail->next = user;
        u->tail = user;
        user->next = NULL;
    }
    pthread_rwlock_unlock(&(u->lock));
}

void delete_user(u_queue_t *u, uint32_t uid)
{
    user_t *p = u->head;
    user_t *tmp;
    
    pthread_rwlock_wrlock(&(u->lock));
    if(p == NULL)
    {
        fprintf(stderr, "Error: empty user queue\n");
        pthread_rwlock_unlock(&(u->lock));
        return;
    }
    else
    {
        if(p->uid == uid)
        {
            u->head = p->next;
            u->tail = p->next;
        }
        free(p);
    }

    while(p->next != NULL)
    {
        if(p->next->uid == uid)
        {
            break;
        }
        else
        {
            p = p->next;
        }
    }

    tmp = p->next;
    p->next = tmp->next;
    if(tmp == u->tail)
    {
        u->tail = p;
    }
    free(tmp);
    pthread_rwlock_unlock(&(u->lock));
}

user_t *find_user(u_queue_t *u, uint32_t uid)
{
    user_t *p;
    printf("find_user1\n");
    pthread_rwlock_rdlock(&(u->lock));
    printf("find_user2\n");
    p = u->head;
    if(p == NULL)
    {
        pthread_rwlock_unlock(&(u->lock));
        return NULL;
    }

    while(p != NULL)
    {
        if(p->uid == uid)
        {
            break;
        }
    }
    pthread_rwlock_unlock(&(u->lock));
    return p;
}

uint32_t get_timestamp(void)
{
    return (uint32_t)time(NULL);
}

void update_user_timestamp(u_queue_t *u, uint32_t uid, uint32_t now)
{
    user_t *p = find_user(u, uid);
    if(p == NULL)
    {
        fprintf(stderr, "update_user_timestamp error: invalid user id\n");
        return;
    }

    p->timestamp = now;
}
