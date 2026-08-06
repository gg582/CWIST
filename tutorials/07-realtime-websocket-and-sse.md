# Tutorial 07: Realtime WebSocket & Server-Sent Events (SSE)

In this tutorial, you will build live real-time web applications using WebSockets and Server-Sent Events (SSE).

---

## 1. Live Server-Sent Events (SSE) Streaming

SSE provides low-overhead single-directional streaming from server to client over standard HTTP:

```c
#include <stdio.h>
#include <cwist/app.h>
#include <cwist/net/http/sse.h>

static void handle_sse_stream(cwist_http_request *req, cwist_http_response *res, void *user_ctx) {
    (void)req;
    (void)user_ctx;

    /* Initialize SSE response headers (text/event-stream, Cache-Control: no-cache) */
    cwist_sse_init_response(res);

    /* Send initial event */
    cwist_sse_event_t evt = {
        .event = "connected",
        .data = "{\"message\":\"Welcome to live SSE stream\"}",
        .id = "1"
    };
    cwist_sse_send_event(res, &evt);

    /* Stream ticker loop */
    for (int i = 2; i <= 5; i++) {
        char databuf[128];
        snprintf(databuf, sizeof(databuf), "{\"tick\":%d,\"timestamp\":%ld}", i, time(NULL));
        
        cwist_sse_event_t tick_evt = {
            .event = "ticker",
            .data = databuf
        };
        cwist_sse_send_event(res, &tick_evt);
    }
}
```

---

## 2. WebSocket Bidirectional Echo & Chat Server

```c
#include <cwist/net/websocket/websocket.h>

static void handle_ws_upgrade(cwist_http_request *req, cwist_http_response *res, void *user_ctx) {
    (void)res;
    (void)user_ctx;

    /* Upgrade HTTP connection to WebSocket */
    cwist_websocket *ws = cwist_websocket_upgrade(req, req->client_fd);
    if (!ws) return;

    printf("WebSocket client connected on fd %d\n", ws->fd);

    /* Read frame loop */
    while (!ws->is_closed) {
        cwist_ws_frame *frame = cwist_websocket_receive(ws);
        if (!frame) break;

        if (frame->opcode == WS_OPCODE_TEXT) {
            printf("Received text: %s\n", frame->payload);
            /* Echo frame back to client */
            cwist_websocket_send_text(ws, (const char *)frame->payload);
        } else if (frame->opcode == WS_OPCODE_CLOSE) {
            cwist_websocket_close(ws, 1000, "Normal closure");
            cwist_ws_frame_destroy(frame);
            break;
        }
        cwist_ws_frame_destroy(frame);
    }

    cwist_websocket_destroy(ws);
}
```

Next Step: Learn background task scheduling and lock-free job queues in **[08-background-jobs-and-scheduler.md](file:///home/yjlee/cwist/tutorials/08-background-jobs-and-scheduler.md)**.
