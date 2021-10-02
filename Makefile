CC=gcc

all:
	${CC} src/*.c -I src/ -o bin/corth

debug:
	${CC} -g src/*.c -I src/ -o bin/corth

clean:
	rm bin/*
