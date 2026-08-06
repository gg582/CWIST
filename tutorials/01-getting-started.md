# Tutorial 01: Getting Started & Hello World Server

In this tutorial, you will set up your CWIST development environment, build `libcwist.a`, create a basic HTTP web server from scratch, and use the `cwist` CLI watcher for hot reloading.

---

## 1. Prerequisites & Build

Ensure you have standard C build tools installed (`gcc`, `make`, `pkg-config`, `zlib`, `curl`, `nghttp2`).

To build the static CWIST framework library:

```bash
cd /path/to/cwist
make libcwist.a
```

This compiles all transport layers (HTTP/1.1, HTTP/2, HTTP/3), security engines, and utilities into `libcwist.a`.

---

## 2. Writing Your First HTTP Server

Create a file named `main.c`:

```c
#include <stdio.h>
#include <cwist/app.h>
#include <cwist/net/http/http.h>

/* Handler for GET / */
static void handle_home(cwist_http_request *req, cwist_http_response *res, void *user_ctx) {
    (void)req;
    (void)user_ctx;
    cwist_http_response_set_status(res, 200);
    cwist_http_response_set_header(res, "Content-Type", "text/plain; charset=utf-8");
    cwist_http_response_set_body(res, "Hello, CWIST Web Framework!");
}

/* Handler for GET /health */
static void handle_health(cwist_http_request *req, cwist_http_response *res, void *user_ctx) {
    (void)req;
    (void)user_ctx;
    cwist_http_response_set_status(res, 200);
    cwist_http_response_set_header(res, "Content-Type", "application/json");
    cwist_http_response_set_body(res, "{\"status\":\"ok\",\"uptime_seconds\":120}");
}

int main(void) {
    /* Initialize application configuration */
    cwist_app_config_t config;
    cwist_app_config_init_default(&config);
    config.port = 8080;
    config.workers = 4;

    /* Create CWIST app instance */
    cwist_app_t *app = cwist_app_create(&config);
    if (!app) {
        fprintf(stderr, "Failed to create CWIST app\n");
        return 1;
    }

    /* Register route handlers */
    cwist_app_get(app, "/", handle_home, NULL);
    cwist_app_get(app, "/health", handle_health, NULL);

    printf("Starting CWIST HTTP server on http://127.0.0.1:8080\n");

    /* Start non-blocking server event loop */
    if (!cwist_app_start(app)) {
        fprintf(stderr, "Failed to start CWIST app\n");
        cwist_app_destroy(app);
        return 1;
    }

    /* Keep process active */
    cwist_app_wait(app);
    cwist_app_destroy(app);
    return 0;
}
```

---

## 3. Compiling and Running

Compile `main.c` against `libcwist.a` and its headers:

```bash
gcc -I./include -I./lib \
    -std=c2x -Wall -pthread -fPIC -D_GNU_SOURCE \
    -o server main.c libcwist.a \
    -pthread -ldl -lm -lstdc++ -lz -lzstd -lcurl -lnghttp2 -lbrotlienc -lbrotlicommon -lbrotlidec
```

Run the server:

```bash
./server
```

Test endpoints in another terminal using `curl`:

```bash
curl -i http://127.0.0.1:8080/
# Output: HTTP/1.1 200 OK
# Content-Type: text/plain; charset=utf-8
# Hello, CWIST Web Framework!

curl -i http://127.0.0.1:8080/health
# Output: HTTP/1.1 200 OK
# Content-Type: application/json
# {"status":"ok","uptime_seconds":120}
```

---

## 4. Hot Reloading with CWIST Watcher

During development, you don't need to manually recompile and restart the server on every code edit. Use the built-in hot reload watcher:

```bash
./tools/cli/cwist watcher
```

The watcher detects file changes (`.c`, `.h`), runs `make`, verifies compilation success, and gracefully restarts your application binary without dropping active connections.

Next Step: Learn dynamic route parameters and middleware pipelines in **[02-routing-and-middleware.md](file:///home/yjlee/cwist/tutorials/02-routing-and-middleware.md)**.
