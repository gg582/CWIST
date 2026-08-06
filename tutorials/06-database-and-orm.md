# Tutorial 06: Embedded Database & `_Generic` ORM Query Builder

In this tutorial, you will use CWIST's embedded SQLite backend, setup schema migrations, configure a connection pool, and build type-safe SQL queries using macro-dispatched `_Generic` ORM helpers.

---

## 1. Database Migrations & Connection Pool

Create database migrations to build your schema:

```c
#include <stdio.h>
#include <cwist/app.h>
#include <cwist/core/db/db.h>
#include <cwist/core/db/pool.h>
#include <cwist/core/db/migrate.h>

static void setup_database(void) {
    cwist_migrate_t *m = cwist_migrate_create(":memory:");

    cwist_migrate_add(m, 1,
        "CREATE TABLE users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, email TEXT);"
        "CREATE TABLE posts (id INTEGER PRIMARY KEY AUTOINCREMENT, user_id INTEGER, title TEXT);",
        "DROP TABLE posts; DROP TABLE users;"
    );

    cwist_migrate_up(m);
    printf("Migrated database to version: %d\n", cwist_migrate_get_version(m));
    cwist_migrate_destroy(m);
}
```

---

## 2. Type-Dispatched `_Generic` ORM Queries

CWIST provides C23 `_Generic` macro dispatch for scalar selects, returning values without raw void pointer casts:

```c
#include <cwist/core/orm/orm.h>
#include <cwist/core/orm/orm_socket.h>

void execute_orm_operations(cwist_orm_t *orm) {
    /* 1. Execute DDL / DML */
    cwist_orm_exec(orm, "INSERT INTO users (name, email) VALUES ('Alice', 'alice@example.com');");
    cwist_orm_exec(orm, "INSERT INTO users (name, email) VALUES ('Bob', 'bob@example.com');");

    /* 2. Dispatched Type-Safe Scalar Selection */
    int64_t user_count = 0;
    cwist_orm_select_one_int(orm, "users", "COUNT(*)", "1=1", &user_count);
    printf("Total users: %ld\n", user_count);

    char *email = NULL;
    cwist_orm_select_one_string(orm, "users", "email", "name = 'Alice'", &email);
    if (email) {
        printf("Alice's email: %s\n", email);
        free(email);
    }
}
```

Next Step: Learn real-time WebSocket communication and Server-Sent Events (SSE) in **[07-realtime-websocket-and-sse.md](file:///home/yjlee/cwist/tutorials/07-realtime-websocket-and-sse.md)**.
