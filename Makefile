all: border

border: main.c
	gcc -Wall -g -o border main.c `pkg-config --cflags --libs gtk+-2.0`

