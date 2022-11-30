CC=gcc 

P1=ex2

PROGS=$(P1)
CFLAGS = -lpthread
all: $(PROGS)

$(P1): $(P1).c
	$(CC) $(P1).c -o $(P1) $(CFLAGS)


clean:
	rm $(PROGS)