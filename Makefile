CC = gcc
CFLAGS = -Wall -Werror -pedantic -lrt -lpthread
OBJ = minimetro.o


.PHONY: clean

all: main

%minimetro.o: %minimetro.c
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o minimetro $^ $(CFLAGS)
	@ echo "~~FINE COMPILAZIONE~~"

clean :
	-rm *.o
	-rm minimetro
