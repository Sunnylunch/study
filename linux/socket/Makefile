
.PHONY:all
all:client server
client:client.c
	gcc -o $@ $^ -static
server:server.c
	gcc -o $@ $^ -static

.PHONY:clean
clean:
	rm -r client server

