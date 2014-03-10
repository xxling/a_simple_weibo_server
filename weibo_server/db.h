#ifndef DB_H
#define DB_H
#include <mysql/mysql.h>
#include <stdio.h>

MYSQL *connect_db(MYSQL *mysql, const char *host, 
        const char *user, const char *password, const char *db_name);

MYSQL *connect_db_use_config(MYSQL *mysql);

MYSQL_RES *fetch_result(MYSQL *conn, const char *cmd);

MYSQL_ROW fetch_row(MYSQL_RES *res);

void free_result(MYSQL_RES *res);

void close_connection(MYSQL *conn);

#endif
