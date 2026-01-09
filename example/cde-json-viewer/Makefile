CC = gcc
# Include root include dir
# We use -I../../lib to ensure we can find headers if they aren't in system path, 
# but we link against the installed library.
CFLAGS = -I../../include -I../../lib -I../../lib/cjson -Wall -Wextra

# Sources from the main project needed here
SRCS = main.c ../../src/sstring/sstring.c ../../src/process/err/error.c ../../src/http/http.c ../../lib/cjson/cJSON.c
OBJS = $(SRCS:.c=.o)
TARGET = cde-viewer
LIBS =

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
