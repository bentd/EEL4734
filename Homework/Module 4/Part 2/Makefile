OBJS = test.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

test: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o test

$(OBJS) : test.cpp
	$(CC) $(CFLAGS) test.cpp

.PHONY: run
run:
	@make test > /dev/null
	@chmod u+x test > /dev/null
	./test -e 7 -a 2 -d 10 -b 4 -c 8

.PHONY: clean
clean:
	rm -rf *.o *~

.PHONY: tar
tar:
	tar -cfv test.tar test.cpp Makefile