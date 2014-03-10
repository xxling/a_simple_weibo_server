#ifndef USER_DB_H
#define USER_DB_H

#include "db.h"
#include <stdio.h>
#include <stdint.h>

int validate_login(MYSQL *conn, const char *name, const char *password);

#endif
