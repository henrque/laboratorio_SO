CC=gcc -Wall

P1=leitura_fifo
P1=escrita_fifo

PROGS=$(P1) $(P2)


all: $(PROGS)

$(P1): $(P1).c
	$(CC) $(P1) $(P1).c -o $(P1)
$(P2): $(P2).c
	$(CC) $(P2) $(P2).c -o $(P2)

clean:
	rm -f $(PROGS)
