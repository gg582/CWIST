# CWIST Step-by-Step Tutorials

Welcome to the **CWIST** step-by-step tutorial series. CWIST is a high-performance C web framework supporting HTTP/1.1, HTTP/2, HTTP/3 (QUIC), WebSocket, gRPC, and GraphQL.

Below is the complete roadmap of structured, step-by-step tutorials to guide you from basic setup to enterprise production deployment.

---

## 📚 Tutorial Index

### 1. Getting Started & Core Fundamentals
* **[01-getting-started.md](file:///home/yjlee/cwist/tutorials/01-getting-started.md)**: Workspace setup, building `libcwist.a`, building your first HTTP/1.1 web server, basic routing, and running under `cwist watcher` hot reload.
* **[02-routing-and-middleware.md](file:///home/yjlee/cwist/tutorials/02-routing-and-middleware.md)**: Parameterized dynamic routes (`/users/:id`), route groups, global middleware pipelines (CORS, Rate Limiting, Logging), and custom status error handlers.

### 2. High-Performance API & Protocol Layer
* **[03-json-api-and-validation.md](file:///home/yjlee/cwist/tutorials/03-json-api-and-validation.md)**: Building RESTful JSON APIs using `json_builder`, input validation with `bind.c`, and error sanitization.
* **[04-grpc-and-protobuf.md](file:///home/yjlee/cwist/tutorials/04-grpc-and-protobuf.md)**: Writing `.proto` schemas, compiling C models with `cwist proto`, registering HTTP/2 gRPC unary and streaming RPCs, and built-in reflection/health services.
* **[05-graphql-api.md](file:///home/yjlee/cwist/tutorials/05-graphql-api.md)**: Defining GraphQL schemas, mounting query & mutation resolvers, variable binding, field aliases, and HTTP POST endpoints.

### 3. Data & State Management
* **[06-database-and-orm.md](file:///home/yjlee/cwist/tutorials/06-database-and-orm.md)**: Embedded SQLite integration, connection pooling, schema migrations, and socket-backed `_Generic` ORM query building.
* **[07-realtime-websocket-and-sse.md](file:///home/yjlee/cwist/tutorials/07-realtime-websocket-and-sse.md)**: Live bidirectional WebSocket chat servers, framed sequence chunks, Server-Sent Events (SSE) live streaming, and client auto-reconnect logic.

### 4. Enterprise Hardening & Operations
* **[08-background-jobs-and-scheduler.md](file:///home/yjlee/cwist/tutorials/08-background-jobs-and-scheduler.md)**: Worker thread pools, lock-free job queue (`cwist_io_queue`), immediate and delayed cron-like background jobs.
* **[09-dev-workflow-and-hot-reload.md](file:///home/yjlee/cwist/tutorials/09-dev-workflow-and-hot-reload.md)**: Project scaffolding with `cwist new project`, `.cwpro` configuration manifests, inotify/kqueue watcher hot reload, and test client automation with `cwist_test_client`.

---

## 🚀 Quick Verification

To verify your CWIST build and run all examples:

```bash
make libcwist.a
make examples
make test
```
