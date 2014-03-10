#include "login.h"

void *process_login(void *args)
{
    uint32_t uid;
    MYSQL mysql;
    MYSQL *conn;
    message_t *m;
    node_t *status;
    node_t *n = NULL;
    client_login_message_t *client;

    while(1)
    {   
        n = consume_message(&login_queue);
        m = n->msg;
        uid = get_uid((void *)m);
        user_t *u;

        server_login_message_t *data = 
            (server_login_message_t *)malloc(sizeof(server_login_message_t));
        
        client = (client_login_message_t *)(m->data);
        conn = connect_db_use_config(&mysql);
        uid = validate_login(conn, client->username, client->password);

        if(uid)
        {
            user_t *p;
            p = find_user(&user_queue, uid);
            if(p == NULL)
            {
                memcpy(data, LOGIN_SUCCESS_MESSAGE, sizeof(server_login_message_t));
                m = message_new(MESSAGE_LOGIN, MAX_MESSAGE_SIZE, uid, data);
                status = create_node((void *)m, n->client_fd);
                u = (user_t *)malloc(sizeof(user_t));
                u->uid = uid;
                add_user(&user_queue, u);
                produce_message(&message_out_queue, status); 
                free(n);
            }
            else
            {
                memcpy(data, LOGIN_REPEAT_MESSAGE, sizeof(server_login_message_t));
                m = message_new(MESSAGE_LOGIN, MAX_MESSAGE_SIZE, uid, data);
                status = create_node((void *)m, n->client_fd);
                uint32_t now = NOW();
                update_user_timestamp(&user_queue, uid, now);
                produce_message(&message_out_queue, status); 
                free(n);
            }
        }   
        else
        {
            memcpy(data, LOGIN_FAILURE_MESSAGE, sizeof(server_login_message_t));
            m = message_new(MESSAGE_LOGIN, MAX_MESSAGE_SIZE, uid, data);
            status = create_node((void *)m, n->client_fd);
            produce_message(&message_out_queue, status);
            free(n);
        }
    }
}
