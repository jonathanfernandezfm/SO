CC = gcc
CFLAGS = -std=c99 -Wall -Wpedantic -Wextra

all: clientes servidor proxy

clientes: clientes.c
	$(CC) $(CFLAGS) clientes.c -o clientes

servidor: servidor.c
	$(CC) $(CFLAGS) servidor.c -o servidor

proxy: proxy.c
	$(CC) $(CFLAGS) proxy.c -o proxy

clean:
	rm -f fifo*
	rm -f clientes
	rm -f servidor
	rm -f proxy