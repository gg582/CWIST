CC = gcc
CFLAGS = -I./include -I./lib -I./lib/cjson -Wall -Wextra -pthread
LIBS = -pthread

SRCS = src/sstring/sstring.c src/process/err/error.c src/http/http.c src/session/session_manager.c lib/cjson/cJSON.c
OBJS = $(SRCS:.c=.o)

all: $(OBJS)

test: $(OBJS) tests/test_sstring.c
	$(CC) $(CFLAGS) -o test_sstring tests/test_sstring.c $(OBJS) $(LIBS)
	./test_sstring

test_http: $(OBJS) tests/test_http.c
	$(CC) $(CFLAGS) -o test_http tests/test_http.c $(OBJS) $(LIBS)
	./test_http

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) test_sstring test_http
