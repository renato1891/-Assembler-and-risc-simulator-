all:
	gcc -Wall -o lista_hash.o -c lista_hash.c
	gcc -Wall -o hash_externa.o -c -lm hash_externa.c
	gcc -Wall -o main lista_hash.o hash_externa.o -lm main.c
run:
	./main
