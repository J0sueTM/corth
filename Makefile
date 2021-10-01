target=bin/corth
source=src/*.c
CC=gcc

all:
	${CC} ${source} -o ${target}

clean:
	rm bin/*
