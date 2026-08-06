# Tutorial 02: Routing & Middleware Pipelines

In this tutorial, you will master dynamic route parameter extraction (`/user/:id`), route groups, global vs route-level middleware, CORS configuration, rate limiting, and custom status error handlers.

---

## 1. Parameterized Routes & Route Groups

CWIST provides a fast Radix-tree based router that supports wildcards and URL parameter extraction:

```c
#include <stdio.h>
#include <cwist/app.h>
#include <cwist/net/http/http.h>

/* Handler with route parameter extraction */
static void handle_get_user(cwist_http_request *req, cwist_http_response *res, void *user_ctx) {
    (void)user_ctx;
    /* Get URL path parameter ":id" */
    const char *user_id = cwist_http_request_get_param(req, "id");
    if (!user_id) user_id = "unknown";

    char jsonbuf[256];
    snprintf(jsonbuf, sizeof(jsonbuf),
             "{\"id\":\"%s\",\"name\":\"User %s\",\"status\":\"active\"}",
             user_id, user_id);

    cwist_http_response_set_status(res, 200);
    cwist_http_response_set_header(res, "Content-Type", "application/json");
    cwist_http_response_set_body(res, jsonbuf);
}
```

---

## 2. Middleware Pipelines & Security Headers

Middleware functions execute before route handlers. They can inspect requests, mutate response headers, verify credentials, or short-circuit execution.

```c
/* Custom Auth Middleware */
static bool mw_require_auth(cwist_http_request *req, cwist_http_response *res, void *user_ctx) {
    (void)user_ctx;
    const char *token = cwist_http_request_get_header(req, "Authorization");
    if (!token || strcmp(token, "Bearer secret-token-123") != 0) {
        cwist_http_response_set_status(res, 401);
        cwist_http_response_set_header(res, "Content-Type", "application/json");
        cwist_http_response_set_body(res, "{\"error\":\"Unauthorized\"}");
        return false; /* Halts execution chain */
    }
    return true; /* Continue to next middleware / route handler */
}

int main(void) {
    cwist_app_config_t config;
    cwist_app_config_init_default(&config);
    config.port = 8080;

    cwist_app_t *app = cwist_app_create(&config);

    /* 1. Global CORS Middleware */
    cwist_app_use_cors(app, "*", "GET, POST, OPTIONS, PUT, DELETE", "Content-Type, Authorization");

    /* 2. Global Rate Limiter: 100 requests per minute per IP */
    cwist_app_use_rate_limit(app, 100, 60);

    /* 3. Global Access Logger */
    cwist_app_use_logger(app);

    /* Public Routes */
    cwist_app_get(app, "/public/status", handle_public_status, NULL);

    /* Protected API Route Group with Auth Middleware */
    cwist_route_group_t *api = cwist_app_group(app, "/api/v1");
    cwist_group_use(api, mw_require_auth, NULL);
    cwist_group_get(api, "/users/:id", handle_get_user, NULL);

    /* Custom 404 Error Handler */
    cwist_app_register_error_handler(app, 404, handle_custom_404, NULL);

    cwist_app_start(app);
    cwist_app_wait(app);
    cwist_app_destroy(app);
    return 0;
}
```

Next Step: Learn JSON parsing, validation, and serialization in **[03-json-api-and-validation.md](file:///home/yjlee/cwist/tutorials/03-json-api-and-validation.md)**.
