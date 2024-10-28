obj-m += testchar.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc tester.c -o tester

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f tester