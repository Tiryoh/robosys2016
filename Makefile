obj-m:=myled.o

myled.ko: myled.c
	make -C /usr/src/linux M=`pwd` V=1 modules

clean:
	make -C /usr/src/linux M=`pwd` V=1 clean

install: myled.ko
	sudo insmod ./myled.ko
	sudo chmod 666 /dev/myled0

uninstall:
	sudo rmmod myled
