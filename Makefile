CC = gcc
EXEC = C006.exe
SRC = main.c menu.c
OBJ = $(SRC:.c=.o)

go : $(EXEC)
	.\$(EXEC)
$(EXEC) : main.c menu.o
	$(CC) -o $(EXEC) main.c menu.o
menu.o : menu.c menu.h
	$(CC) -c menu.c

# clean: 
#     del menu.o
#     del C006.exe