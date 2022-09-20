SHELL := /bin/bash
CC     = gcc
SRC = main.c loop.c exec.c line.c builtin.c
LINK= -lreadline
OBJ = $(SRC:.c=.ro)
DBGOBJ = $(SRC:.c=.do)
EXE  = dish
DBGEXE = ddish

all:release debug
debug: CFLAGS = -g -O0 -DDEBUG
release: CFLAGS = -Wall -O3

release: $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ) $(LINK)

debug: $(DBGOBJ)
	$(CC) $(CFLAGS) -o $(DBGEXE) $(DBGOBJ) $(LINK)

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