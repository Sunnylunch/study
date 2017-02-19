dst=consumer
src=consumer.c
cc=gcc

$(dst):$(src)
	$(cc) -o $@ $^ -lpthread

.PHONY:clean
clean:
	rm -r $(dst)
