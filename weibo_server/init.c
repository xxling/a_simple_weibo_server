#include "init.h"

void init_queues(unsigned number_threads)
{
    init_message_queue(&login_queue, number_threads, process_login);
    init_message_queue(&message_out_queue, number_threads, process_message_out);
    init_user_queue(&user_queue);    
}
