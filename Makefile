OBJ=main.o line.o
CC=gcc
CFLAGS= -O3 -Wall

all:debug

release:dish

dish: $(OBJ)
	$(CC) $(CFLAGS) -o dish $(OBJ)

debug: CFLAGS += -DDEBUG -g
debug: dish

clean:
	rm -f $(OBJ) dish

