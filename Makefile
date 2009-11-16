all: border

border: main.c
	gcc -Wall -g -o border_adder main.c `imlib2-config --cflags` `imlib2-config --libs`

