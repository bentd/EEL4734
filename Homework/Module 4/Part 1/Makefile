OBJS = a.o b.o c.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

a.o : a.cpp a.h c.h
	$(CC) $(CFLAGS) a.cpp

b.o : b.cpp b.h c.h
	$(CC) $(CFLAGS) b.cpp

c.o : c.cpp c.h
	$(CC) $(CFLAGS) c.cpp

.PHONY: clean
clean:
	rm -rf *.o *~

.PHONY: tar
tar:
	tar -cvf abc.tar a.cpp a.h b.cpp b.h c.cpp c.h