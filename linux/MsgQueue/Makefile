ser=serve
sersrc=serve.c comm.c
cli=client
clisrc=client.c comm.c
cc=gcc
com=comm
comh=comm.h

.PHONY:all
all:$(ser) $(cli)

$(ser):$(sersrc) $(comh) 
	$(cc) -o $@ $<

$(cli):$(clisrc) $(comh) 
	$(cc) -o $@ $<



.PHONY:clean
clean:
	rm -r $(ser) $(cli)
