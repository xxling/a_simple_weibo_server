#include "login.h"

void process_login(int socket_fd, const char *username, const char *password)
{
    message_t *m;
    message_t *n;
    client_login_message_t c;

    strcpy(c.username, username);
    strcpy(c.password, password);
  
    m = message_new(MESSAGE_LOGIN, MAX_USERNAME_SIZE + MAX_PASSWORD_SIZE, 0, (void *)&c);
    message_write(socket_fd, (void *)m);

    n = message_read(socket_fd);
    printf("%s\n", (char *)n->data);
}
