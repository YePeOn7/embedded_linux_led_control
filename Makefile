CC = gcc
CFLAG = -Wall -I .
# LFLAG = 

CFILE = ${wildcard *.c}
TARGET = led-test

all:
	@echo ${FILE}
	${CC} ${CFLAG} ${CFILE} -o ${TARGET}