CC ?= gcc
CFLAGS ?= -Wall -Wextra -std=c99 -I../ds/include -g

SRC = ../ds/src/queue.c ../ds/src/sll.c ../ds/test/queue_test.c

TARGET = test_queue

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean
