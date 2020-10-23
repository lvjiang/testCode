#!/bin/bash

function GitClone()
{
	if [ "$1" == "" ]; then
		echo "skip line."
		return
	fi
	
	echo $1
	all=${1#*:}
	dir=${all%/*}
	
	if [ -e $dir ]; then
		echo "$dir exists."
	else
		echo "mkdir $dir"
		mkdir $dir
	fi

	cd $dir
		git clone $1
	cd ..


	
}

while read -r line
do
	GitClone $line
done < $1

