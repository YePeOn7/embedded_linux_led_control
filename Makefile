CC = gcc
CFLAG = -Wall -I .
LFLAG = -lpthread

LED_C = led.c
LED_OBJ = led.o

# TARGET = led-set-command
TARGET = led-test
TARGET_OBJ = ${TARGET:%=%.o}

all: ${LED_OBJ} ${TARGET_OBJ}
	${CC} ${CFLAG} ${LED_OBJ} ${TARGET_OBJ} ${LFLAG} -o ${TARGET}

%.o: %.c
	${CC} ${CFLAG} -c $< -o $@  

test: test.c led.c
	${CC} ${CFLAG} -c test.c led.c
	${CC} ${CFLAG} test.o led.o ${LFLAG} -o test 
	
clean:
	rm -rf ${TARGET}
	rm -rf *.o
	rm -rf test