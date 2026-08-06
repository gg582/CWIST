# Tutorial 08: Background Jobs & Scheduler Worker Pools

In this tutorial, you will use CWIST's thread-pool scheduler (`cwist_scheduler`) and lock-free job queue (`cwist_io_queue`) to run non-blocking immediate and delayed background tasks.

---

## 1. Creating a Scheduler Worker Pool

`cwist_scheduler` manages background thread execution so HTTP request handlers return immediately without blocking on heavy computations, email delivery, or database cleanup.

```c
#include <stdio.h>
#include <unistd.h>
#include <cwist/sys/job/scheduler.h>

/* Task payload definition */
typedef struct {
    int user_id;
    char email[128];
} send_email_task_t;

/* Background worker callback */
static void worker_send_email(void *arg) {
    send_email_task_t *task = (send_email_task_t *)arg;
    printf("[Worker Thread] Sending welcome email to %s (User ID: %d)...\n",
           task->email, task->user_id);
    sleep(1); /* Simulate network I/O */
    printf("[Worker Thread] Email sent successfully to %s\n", task->email);
    free(task);
}

int main(void) {
    /* Create scheduler with 4 worker threads */
    cwist_scheduler_t *sched = cwist_scheduler_create(4);

    /* Enqueue immediate background task */
    send_email_task_t *task1 = malloc(sizeof(send_email_task_t));
    task1->user_id = 101;
    snprintf(task1->email, sizeof(task1->email), "user101@example.com");
    cwist_scheduler_schedule(sched, worker_send_email, task1);

    /* Enqueue delayed background task (runs after 2 seconds) */
    send_email_task_t *task2 = malloc(sizeof(send_email_task_t));
    task2->user_id = 102;
    snprintf(task2->email, sizeof(task2->email), "user102@example.com");
    cwist_scheduler_schedule_delayed(sched, worker_send_email, task2, 2000);

    printf("[Main Thread] Tasks scheduled. Main thread continuing execution...\n");
    sleep(4);

    cwist_scheduler_destroy(sched);
    return 0;
}
```

---

## 2. Integrating Background Jobs into HTTP Handlers

```c
static void handle_user_signup(cwist_http_request *req, cwist_http_response *res, void *user_ctx) {
    cwist_scheduler_t *sched = (cwist_scheduler_t *)user_ctx;

    /* Process HTTP signup... */

    send_email_task_t *task = malloc(sizeof(send_email_task_t));
    task->user_id = 456;
    snprintf(task->email, sizeof(task->email), "newuser@example.com");

    /* Dispatch async email job without delaying HTTP response */
    cwist_scheduler_schedule(sched, worker_send_email, task);

    cwist_http_response_set_status(res, 201);
    cwist_http_response_set_body(res, "{\"message\":\"User created. Welcome email pending.\"}");
}
```

Next Step: Learn CLI scaffolding and developer workflow tooling in **[09-dev-workflow-and-hot-reload.md](file:///home/yjlee/cwist/tutorials/09-dev-workflow-and-hot-reload.md)**.
