#!/bin/bash -eu

[ ! -e /dev/myled0 -a ! -e /dev/myswitch0 ] && echo "install myled driver!" && exit 1 || echo "push switch to turn off led"

while true; do 
	cat /dev/myswitch0 > /dev/myled0
	RESULT=$?
	sleep 0.01
	if [[ ! $RESULT -eq 0 ]]; then
		echo "finished with $RESULT"
	fi
done
