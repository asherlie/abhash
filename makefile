CC=gcc
CFLAGS= -pthread -Wall -Wextra -Wpedantic -Werror -O3

all: demo

huct.o: huct.c huct.h
demo: huct.o demo.c

.PHONY:
clean:
	rm -f huct *.o
