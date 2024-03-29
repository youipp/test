
CC = gcc

go : C006
	./C006
C006 : main.c menu.o
	gcc -o C006 main.c menu.o
menu.o : menu.c menu.h
	gcc -c menu.c

clean:
    rm -f *.o
    rm -f C006