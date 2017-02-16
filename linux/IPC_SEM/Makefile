commh=comm.h
src=sem.c comm.c
dst=sem
cc=gcc



$(dst):$(src) $(commh)
	$(cc) -o $@ $<

.PHONY:clean
clean:
	rm -rf $(dst)
