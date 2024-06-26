CC = gcc

CFLAGS := -Wall \
          -Wextra \
          -Wformat=2 \
          -Wformat-overflow \
          -Wformat-truncation \
          -Wshadow \
          -Wdouble-promotion \
          -Wundef \
          -fno-common \
          -z noexecstack \
          -Wconversion \
          -fsanitize=undefined \
          -g

LIBS = -lm

SRCS = main.c worstgrad.c tests.c
OBJS = $(SRCS:.c=.o)

BIN_DIR = ./bin
TARGET = $(BIN_DIR)/main

.PHONY: all build run clean

all: build

build: $(TARGET)

$(TARGET): $(OBJS) main.h
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c main.h
	$(CC) $(CFLAGS) -c -o $@ $<

run: build
	$(TARGET)

clean:
	rm -rf *.o $(BIN_DIR)/*.o $(TARGET)

cppcheck:
	cppcheck --enable=all --inconclusive --force --suppress=unusedFunction .

valgrind:
	 valgrind --tool=memcheck --leak-check=full --show-reachable=yes --num-callers=20 -s --track-fds=yes  --track-origins=yes ./bin/main
