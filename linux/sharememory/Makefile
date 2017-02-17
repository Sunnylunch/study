sersrc=serve.c comm.c
clisrc=client.c comm.c
ser=serve
cli=client
commh=comm.h
cc=gcc

.PHONY:all
all:$(ser) $(cli)

$(ser):$(sersrc) $(commh)
	$(cc) -o $@ $<


$(cli):$(clisrc) $(commh)
	$(cc) -o $@ $<

.PHONY:clean
clean:
	rm -r $(ser) $(cli)
