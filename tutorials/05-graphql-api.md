# Tutorial 05: GraphQL Schema & Query Engine

In this tutorial, you will define a GraphQL schema, register query and mutation field resolvers, and mount a bounded GraphQL executor endpoint over HTTP.

---

## 1. Defining GraphQL Schema & Resolvers

CWIST includes an in-tree bounded GraphQL query engine:

```c
#include <stdio.h>
#include <cwist/app.h>
#include <cwist/net/graphql/graphql.h>

/* Resolver for field "hello" */
static cwist_gql_value_t resolve_hello(cwist_gql_args_t *args, void *user_ctx) {
    (void)args;
    (void)user_ctx;
    return cwist_gql_string("Hello from CWIST GraphQL!");
}

/* Resolver for field "user(id: Int!)" */
static cwist_gql_value_t resolve_user(cwist_gql_args_t *args, void *user_ctx) {
    (void)user_ctx;
    int id = cwist_gql_args_get_int(args, "id", 0);

    cwist_gql_object_t *obj = cwist_gql_object_create();
    cwist_gql_object_set_int(obj, "id", id);
    cwist_gql_object_set_string(obj, "name", "Alice Developer");
    cwist_gql_object_set_string(obj, "role", "Lead Engineer");
    return cwist_gql_object_value(obj);
}
```

---

## 2. Mounting GraphQL Endpoint

```c
int main(void) {
    cwist_app_config_t config;
    cwist_app_config_init_default(&config);
    config.port = 8080;

    cwist_app_t *app = cwist_app_create(&config);

    /* Create GraphQL Schema */
    cwist_gql_schema_t *schema = cwist_gql_schema_create();

    /* Register Query Fields */
    cwist_gql_register_query(schema, "hello", resolve_hello, NULL);
    cwist_gql_register_query(schema, "user", resolve_user, NULL);

    /* Mount /graphql POST endpoint */
    cwist_app_graphql(app, "/graphql", schema);

    printf("GraphQL endpoint listening on http://127.0.0.1:8080/graphql\n");
    cwist_app_start(app);
    cwist_app_wait(app);

    cwist_gql_schema_destroy(schema);
    cwist_app_destroy(app);
    return 0;
}
```

---

## 3. Testing with `curl`

Send a GraphQL POST request:

```bash
curl -X POST http://127.0.0.1:8080/graphql \
  -H "Content-Type: application/json" \
  -d '{"query": "{ user(id: 42) { id name role } }"}'
```

Expected Response:

```json
{
  "data": {
    "user": {
      "id": 42,
      "name": "Alice Developer",
      "role": "Lead Engineer"
    }
  }
}
```

Next Step: Learn embedded SQLite, connection pooling, and ORM in **[06-database-and-orm.md](file:///home/yjlee/cwist/tutorials/06-database-and-orm.md)**.
