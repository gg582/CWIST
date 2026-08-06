# Tutorial 04: gRPC Services & Protobuf Integration

In this tutorial, you will generate C data structures from `.proto` files using `cwist proto`, implement unary and streaming gRPC service handlers over HTTP/2, and enable health check & reflection services.

---

## 1. Defining a `.proto` Schema

Create `greeter.proto`:

```protobuf
syntax = "proto3";

package greeter;

message HelloRequest {
  string name = 1;
}

message HelloReply {
  string message = 1;
}

service Greeter {
  rpc SayHello (HelloRequest) returns (HelloReply);
}
```

---

## 2. Generating Code with `cwist proto`

Run the CWIST CLI code generator:

```bash
./tools/cli/cwist proto greeter.proto
```

This generates `greeter.pb.h` and `greeter.pb.c` containing C struct definitions, encoder/decoder helpers, and service path constants (`GREETER_SAYHELLO_PATH = "/greeter.Greeter/SayHello"`).

---

## 3. Implementing the gRPC Server

```c
#include <stdio.h>
#include <cwist/app.h>
#include <cwist/net/grpc/grpc.h>
#include <cwist/net/grpc/protobuf.h>
#include "greeter.pb.h"

/* Unary gRPC Handler */
static void handle_say_hello(cwist_grpc_context_t *ctx, void *user_ctx) {
    (void)user_ctx;
    
    /* Decode request payload */
    const uint8_t *req_bytes = cwist_grpc_context_get_request_bytes(ctx);
    size_t req_len = cwist_grpc_context_get_request_len(ctx);

    greeter_HelloRequest req = {0};
    greeter_HelloRequest_decode(&req, req_bytes, req_len);

    char greeting[256];
    snprintf(greeting, sizeof(greeting), "Hello, %s!", req.name ? req.name : "World");

    greeter_HelloReply reply = { .message = greeting };
    
    /* Encode response payload */
    uint8_t outbuf[512];
    size_t out_len = greeter_HelloReply_encode(&reply, outbuf, sizeof(outbuf));

    /* Return gRPC OK response */
    cwist_grpc_set_response(ctx, outbuf, out_len);
}

int main(void) {
    cwist_app_config_t config;
    cwist_app_config_init_default(&config);
    config.port = 50051;
    config.enable_http2 = true;

    cwist_app_t *app = cwist_app_create(&config);

    /* Register gRPC Unary RPC */
    cwist_app_grpc_unary(app, "greeter.Greeter", "SayHello", handle_say_hello, NULL);

    /* Register standard gRPC Health & Reflection endpoints */
    cwist_app_grpc_health(app);
    cwist_app_grpc_health_set_status(app, "greeter.Greeter", CWIST_GRPC_HEALTH_SERVING);
    cwist_app_grpc_reflection(app);

    printf("gRPC server listening on 127.0.0.1:50051\n");
    cwist_app_start(app);
    cwist_app_wait(app);
    cwist_app_destroy(app);
    return 0;
}
```

Next Step: Learn GraphQL queries and mutations in **[05-graphql-api.md](file:///home/yjlee/cwist/tutorials/05-graphql-api.md)**.
