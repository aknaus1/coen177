all: genTestInput.c fifo.c lru.c sec_chance.c
	gcc -o genTestInput genTestInput.c
	gcc -o lru lru.c
	gcc -o fifo fifo.c
	gcc -o sec_chance sec_chance.c

clean:; rm -f *.out genTestInput lru fifo sec_chance