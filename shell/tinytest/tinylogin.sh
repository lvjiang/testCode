#!/bin/bash

if [ $# -ne 0 ]; then
	echo "parmeter err! $#"
	exit
fi

while :
do
	for i in 3 124
	do
		for p in root lvsj '123456' ''
		do
			expect ssh.exp root 192.168.1.$i "$p"
			sleep 2
		done
	done
	sleep 2
done
