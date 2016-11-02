obj-m:=led_blink.o

led_blink.ko: led_blink.c
	make -C /usr/src/linux M=`pwd` V=1 modules

clean:
	make -C /usr/src/linux M=`pwd` V=1 clean
