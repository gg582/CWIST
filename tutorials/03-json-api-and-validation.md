# Tutorial 03: JSON API & Input Validation

In this tutorial, you will build robust RESTful JSON endpoints using CWIST's fast `json_builder`, parse requests safely using `bind.c` schema validation, and handle errors cleanly.

---

## 1. Fast JSON Serialization with `json_builder`

CWIST includes a zero-allocation streaming `json_builder` to build structured JSON payloads quickly:

```c
#include <stdio.h>
#include <cwist/app.h>
#include <cwist/core/utils/json_builder.h>

static void handle_user_profile(cwist_http_request *req, cwist_http_response *res, void *user_ctx) {
    (void)req;
    (void)user_ctx;

    cwist_json_builder_t *jb = cwist_json_builder_create();
    cwist_json_builder_object_begin(jb);
    
    cwist_json_builder_key_string(jb, "status", "success");
    cwist_json_builder_key_int(jb, "user_id", 42);
    cwist_json_builder_key_string(jb, "username", "alice");
    cwist_json_builder_key_bool(jb, "is_admin", true);

    cwist_json_builder_key_array_begin(jb, "roles");
    cwist_json_builder_string(jb, "developer");
    cwist_json_builder_string(jb, "maintainer");
    cwist_json_builder_array_end(jb);

    cwist_json_builder_object_end(jb);

    const char *json_out = cwist_json_builder_to_string(jb);

    cwist_http_response_set_status(res, 200);
    cwist_http_response_set_header(res, "Content-Type", "application/json");
    cwist_http_response_set_body(res, json_out);

    cwist_json_builder_destroy(jb);
}
```

---

## 2. Request Body Validation with `bind.c`

Validate inbound JSON payloads against strict type constraints before processing:

```c
#include <cwist/core/validation/bind.h>

static void handle_create_user(cwist_http_request *req, cwist_http_response *res, void *user_ctx) {
    (void)user_ctx;

    /* Define expected schema fields */
    cwist_bind_rule_t rules[] = {
        { "username", CWIST_BIND_STRING, .required = true, .min_len = 3, .max_len = 30 },
        { "email",    CWIST_BIND_STRING, .required = true, .is_email = true },
        { "age",      CWIST_BIND_INT,    .required = false, .min_val = 18, .max_val = 120 }
    };
    cwist_schema_t schema = { rules, 3 };

    cwist_bind_result_t result;
    if (!cwist_bind_validate_json(req->body, &schema, &result)) {
        cwist_http_response_set_status(res, 400);
        cwist_http_response_set_header(res, "Content-Type", "application/json");
        cwist_http_response_set_body(res, result.error_json);
        cwist_bind_result_cleanup(&result);
        return;
    }

    cwist_http_response_set_status(res, 201);
    cwist_http_response_set_body(res, "{\"status\":\"created\"}");
    cwist_bind_result_cleanup(&result);
}
```

Next Step: Learn gRPC over HTTP/2 and Protobuf C generation in **[04-grpc-and-protobuf.md](file:///home/yjlee/cwist/tutorials/04-grpc-and-protobuf.md)**.
