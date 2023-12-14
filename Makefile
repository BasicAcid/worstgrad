CFLAGS=`pkg-config libgvc --cflags` -Wall -g -O2
LDLIBS=`pkg-config libgvc --libs`

build:
	gcc -O2 -Wall -Wextra -Wformat=2 -Wformat-overflow -Wformat-truncation -Wshadow -Wdouble-promotion -Wundef -fno-common -z noexecstack -Wconversion -fsanitize=undefined -g -o ./bin/main main.c worstgrad.c neuron.c -lm -lgvc -lcgraph

run:
	./bin/main
tags:
	etags main.c worstgrad.c neuron.c main.h
