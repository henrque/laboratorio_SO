CC=gcc 

P1=ex3_a
P2=ex3_b
P3=ex1
P4=ex2

PROGS=$(P1) $(P2) $(P3) $(P4)
CFLAGS = -lpthread
all: $(PROGS)

$(P1): $(P1).c
	$(CC) $(P1).c -o $(P1) $(CFLAGS)
$(P2): $(P2).c
	$(CC) $(P2).c -o $(P2) $(CFLAGS)
$(P3): $(P3).c
	$(CC) $(P3).c -o $(P3) $(CFLAGS)
$(P4): $(P4).c
	$(CC) $(P4).c -o $(P4) $(CFLAGS)

clean:
	rm $(PROGS)