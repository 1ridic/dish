SHELL := /bin/bash
CC     = gcc
SRC = main.c loop.c exec.c line.c builtin.c postgres.c
LINK= -lreadline -lpq
OBJ = $(SRC:.c=.ro)
DBGOBJ = $(SRC:.c=.do)
EXE  = dish
DBGEXE = ddish

a:all
all:release debug
debug: CFLAGS = -g -O0 -DDEBUG
release: CFLAGS = -Wall -O3

r:release
release: $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ) $(LINK)

d:debug
debug: $(DBGOBJ)
	$(CC) $(CFLAGS) -o $(DBGEXE) $(DBGOBJ) $(LINK)

c: clean
clean:
	rm -f *.o *.do *.ro dish ddish

$(OBJ):$(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	rename .o .ro *.o

$(DBGOBJ):$(SRC)
	$(CC) $(CFLAGS) -c $(SRC) 
	rename .o .do *.o
	
c:clean
d:debug
r:release