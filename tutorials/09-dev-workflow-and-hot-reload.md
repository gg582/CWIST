# Tutorial 09: CLI Scaffolding, Testing & Dev Workflow

In this final tutorial, you will learn how to scaffold new CWIST projects using `cwist new project`, configure build manifests (`.cwpro`), write in-process unit and integration tests using `cwist_test_client`, and run automated benchmarks.

---

## 1. Project Scaffolding with CWIST CLI

CWIST provides a CLI tool (`tools/cli/cwist`) to generate standardized project structures:

```bash
/* Create new application scaffold */
./tools/cli/cwist new project my_api_service
cd my_api_service
```

This generates:
* `src/main.c`: Application entry point with health checks and logging.
* `Makefile`: Pre-configured Makefile pointing to `libcwist.a` and project include directories.
* `.cwpro`: Configuration manifest tracking project metadata and build flags.
* `config/.env`: Environment variables template.

Build and launch the project:

```bash
make
./bin/my_api_service
```

---

## 2. In-Process Testing with `cwist_test_client`

You can test route handlers directly in unit tests without spawning external socket servers or running `curl`:

```c
#include <assert.h>
#include <stdio.h>
#include <cwist/app.h>
#include <cwist/sys/app/test_client.h>

void test_health_endpoint(void) {
    cwist_app_config_t config;
    cwist_app_config_init_default(&config);
    cwist_app_t *app = cwist_app_create(&config);

    cwist_app_get(app, "/health", handle_health, NULL);

    /* Perform in-process HTTP GET */
    cwist_test_response_t *res = cwist_test_client_get(app, "/health");
    assert(res != NULL);
    assert(res->status_code == 200);
    assert(strstr(res->body, "\"status\":\"ok\"") != NULL);

    printf("PASS: /health endpoint test passed!\n");

    cwist_test_response_destroy(res);
    cwist_app_destroy(app);
}

int main(void) {
    test_health_endpoint();
    return 0;
}
```

---

## 3. Summary & Roadmap Checklist

Congratulations! You have completed the CWIST tutorial series.

* ✅ **P0 (Critical Architecture)**: Unified epoll/io_uring reactor, graceful shutdown, compression, CORS, rate limiting.
* ✅ **P1 (Production Readiness)**: Secure headers, connection pooling, SQLite migrations, access logging, Prometheus `/metrics`.
* ✅ **P2 (Developer Experience)**: Hot reload watcher, CLI project generator, `.env` loader, in-process test client.
* ✅ **P3 (Deep Protocols)**: HTTP/1.1, HTTP/2 Server Push, HTTP/3 (lsquic), WebSocket framed sequence transport.
* ✅ **P4 (Ecosystem Integrations)**: gRPC over HTTP/2, Protobuf C codegen, GraphQL query engine, scheduler worker pools.

For more example applications, explore the `example/` directory in the CWIST source repository.
