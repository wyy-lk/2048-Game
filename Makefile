#Makefile

TARGET = 2048_game
CC = gcc
OPTION = -g -DDBUG
SRC_FILES = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRC_FILES))

%.o : %.c
	${CC} ${OPTION} -c $<

${TARGET}: ${OBJS}
	${CC} ${OPTION} -o $@ $^ 
	
.PHONY: clean
clean:
	rm -rf ${OBJS} ${TARGET}
