SHELL := /bin/bash
CC     = gcc
SRC = main.c loop.c exec.c line.c builtin.c
OBJ = $(SRC:.c=.ro)
DBGOBJ = $(SRC:.c=.do)
EXE  = dish
DBGEXE = ddish

all:release debug
debug: CFLAGS = -g -O0 -DDEBUG
release: CFLAGS = -Wall -O3

release: $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

debug: $(DBGOBJ)
	$(CC) $(CFLAGS) -o $(DBGEXE) $(DBGOBJ)

clean:
	rm -f *.o *.do *.ro

$(OBJ):$(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	rename .o .ro *.o

$(DBGOBJ):$(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	rename .o .do *.o
	
c:clean
d:debug
r:release