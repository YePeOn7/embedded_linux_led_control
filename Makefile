CC = gcc
CFLAG = -Wall -I .
LFLAG = -lpthread

CFILE = ${wildcard *.c}
CFILE := ${filter-out test.c, ${CFILE}}
OFILE = ${CFILE:.c=.o}
TARGET = led-test

all: ${OFILE}
	${CC} ${CFLAG} ${OFILE} ${LFLAG} -o ${TARGET}

%.o: %.c
	${CC} ${CFLAG} -c $< -o $@  

test: test.c led.c
	${CC} ${CFLAG} -c test.c led.c
	${CC} ${CFLAG} test.o led.o ${LFLAG} -o test 
	
clean:
	rm -rf ${TARGET}
	rm -rf *.o
	rm -rf test