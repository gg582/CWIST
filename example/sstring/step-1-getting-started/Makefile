CC = gcc
CFLAGS = -I../../../include -I../../../lib -I../../../lib/cjson -Wall -Wextra

# Paths to the object files compiled in the root project
SSTRING_OBJ = ../../../src/sstring/sstring.o
OBJS = $(SSTRING_OBJ)

TARGET = getting-started

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) main.c $(OBJS) -o $(TARGET)

clean:
	rm -f $(TARGET)
