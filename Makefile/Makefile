CC ?= gcc
CFLAGS ?= -ansi -std=c99 -pedantic-errors -Wall -Wextra
TARGET = fooer.out
OBJS = foo.o main.o 

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^


######## creat files .o ########
%.o: %.c foo.h
	$(CC) $(CFLAGS) -c $< -o $@
################################

clean:
	rm -f *.o $(TARGET)

debug: CFLAGS += -g -DDEBUG -O3
debug: clean all

release: CFLAGS = -O2
release: clean all

run: $(TARGET)
	@./$(TARGET)

.PHONY: all clean debug release run


