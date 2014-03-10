#include "db.h"

MYSQL *connect_db(MYSQL *mysql, const char *host, 
        const char *user, const char *password, const char *db_name)
{
    MYSQL *conn;

    conn = mysql_init(mysql);
    if(conn == NULL)
    {
        fprintf(stderr, "mysql_init error:%s\n", mysql_error(mysql));
        return NULL;
    }

    conn = mysql_real_connect(mysql, host, user, password, db_name, 0, NULL, 0);
    if(conn == NULL)
    {
        fprintf(stderr, "mysql_real_connect error:%s\n", mysql_error(mysql));
        return NULL;
    }

    return conn;
}

MYSQL *connect_db_use_config(MYSQL *mysql)
{
    const char *host = "localhost";
    const char *user = "root";
    const char *password = "test";
    const char *db_name = "weibo";

    return connect_db(mysql, host, user, password, db_name);
}

MYSQL_RES *fetch_result(MYSQL *conn, const char *cmd)
{
    int ret;
    MYSQL_RES *res;

    ret = mysql_query(conn, cmd);
    if(ret != 0)
    {
        fprintf(stderr, "mysql_query_error:%s\n", mysql_error(conn));
        return NULL;
    }

    res = mysql_use_result(conn);
    return res;
}

MYSQL_ROW fetch_row(MYSQL_RES *res)
{
    return mysql_fetch_row(res);
}

void free_result(MYSQL_RES *res)
{
    mysql_free_result(res);
}

void close_connection(MYSQL *conn)
{
    mysql_close(conn);
}
