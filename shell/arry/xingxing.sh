#!/bin/bash

arry=("a aa","b bb","c cc")
b=(db c d)
echo $b

function showArr() {
	
	arr=$1
	echo ${arr[*]}
}


echo ${arry[*]}
echo ${arry[@]}

showArr "${arry[*]}"
showArr "${arry[@]}"


showArr $*
showArr "$*"
showArr $@
showArr "$@"

