target=bin/corth
source=src/*.c

all:
	cc ${source} -o ${target}

clean:
	rm bin/*
