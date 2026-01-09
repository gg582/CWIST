CC = gcc
CFLAGS = -I../../include -I../../lib -I../../lib/cjson -Wall -Wextra -g
LIBS =

# Path to library sources
SRC_DIR = ../../src
SRCS = $(SRC_DIR)/sstring/sstring.c \
       $(SRC_DIR)/process/err/error.c \
       $(SRC_DIR)/http/http.c \
       ../../lib/cjson/cJSON.c \
       main.c

TARGET = simple_server

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

clean:
	rm -f $(TARGET)
