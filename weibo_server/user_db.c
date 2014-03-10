#include "user_db.h"

int validate_login(MYSQL *conn, const char *name, const char *password)
{
    char *cmd = "select * from `users` where name = \'%s\' and password = \'%s\'";
    char cmd_buf[200];
    MYSQL_RES *res;
    MYSQL_ROW row;
    uint32_t uid;
    snprintf(cmd_buf, sizeof(cmd_buf), cmd, name, password);
    printf("%s\n", cmd_buf);
    res = fetch_result(conn, cmd_buf);

    if(res == NULL)
    {
        return 0;
    }
    else
    {
        row = fetch_row(res);
        uid = atoi(row[0]);
        free_result(res);
        close_connection(conn);
        return row == NULL ? 0:uid;
    }
}
