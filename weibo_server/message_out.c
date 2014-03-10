#include "message_out.h"
#include "message_queue.h"


void *process_message_out(void *args)
{
    node_t *n;
    
    while(1)
    {
        n = consume_message(&message_out_queue);
        message_write(n->client_fd, (void *)n->msg); 
        free_node(n);
    }
}
