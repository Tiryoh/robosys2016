#!/bin/bash -eu

[ ! -e /dev/myled0 ] && echo "install myled driver!" && exit 1

for i in 1 0 1 0; do 
	echo $i > /dev/myled0
	sleep 1
	echo "echo $i finished with $?"
done
