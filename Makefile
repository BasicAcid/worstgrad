CC = gcc
CFLAGS = -Wall -Wextra -Wformat=2 -Wformat-overflow -Wformat-truncation -Wshadow -Wdouble-promotion -Wundef -fno-common -z noexecstack -Wconversion -fsanitize=undefined -g
DEBUG_FLAGS = -O0 -DDEBUG
LIBS = -lm

SRCS = main.c worstgrad.c neuron.c layer.c
OBJS = $(SRCS:.c=.o)

BIN_DIR = ./bin
TARGET = $(BIN_DIR)/main
DEBUG_TARGET = $(BIN_DIR)/debug_main

.PHONY: all build debug run tags clean

all: build

build: $(TARGET)

debug: $(DEBUG_TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(DEBUG_TARGET): CFLAGS += $(DEBUG_FLAGS)
$(DEBUG_TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

run: build
	$(TARGET)

tags:
	etags main.c worstgrad.c neuron.c layer.c main.h

clean:
	rm -rf *.o $(BIN_DIR)/*.o $(TARGET) $(DEBUG_TARGET)

cppcheck:
	cppcheck --enable=all --inconclusive --force .

valgrind:
	 valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 -s --track-fds=yes  --track-origins=yes ./bin/main
