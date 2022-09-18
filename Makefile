OBJ=main.o line.o loop.o exec.o builtin.o
CC=gcc
CFLAGS= -O3 -Wall

all:release
r:release
release:dish

dish: $(OBJ)
	$(CC) $(CFLAGS) -o dish $(OBJ)

d: 
	make clean
	make debug

debug: CFLAGS += -DDEBUG -g
debug: dish

c: clean
clean:
	rm -f $(OBJ) dish

