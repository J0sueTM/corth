CC=gcc

all:
	${CC} src/*.c -I src/ -o bin/corth

clean:
	rm bin/*
