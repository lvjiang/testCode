#!/bin/bash

WORK_DIR_NAME=$(cd "$(groupname "$0")"; pwd)
TAR_DIR_NAME=$WORK_DIR_NAME/my_tar
cd $WORK_DIR_NAME

function Usage() {
	self=$(basename $0)
	printf "Usage:\n"
	printf "\t$self -f FILE -c [clone|pull|tar|del]\n"
	printf "\t$self -h\n"
}

while getopts c:f:h opt; do
	case $opt in
		c)
			CMD=$OPTARG
			;;
		f)
			FILE=$OPTARG
			;;
		h)
			Usage
			exit 0
			;;
		?)
			Usage
			exit 1
			;;
	esac
done


function gitClone()
{
	for val in $1; do
		tmp=${val#*:}
		group=${tmp%/*}
		repository=${tmp%.*}

		if [ ! -e $group ]; then
			echo "mkgroup $group"
			mkdir $group
		fi

		if [ ! -e $repository ]; then
			cd $group
			git clone $val
			cd -

			cd $repository
			git branch -r | grep -v '\->' | grep -v 'master' | while read remote; do git branch --track "${remote#origin/}" "$remote"; done
			cd -
		fi
	done

	return
}

function gitPull()
{
	for val in $1; do
		tmp=${val#*:}
		repository=${tmp%.*}

		cd $repository
		pwd
		git pull --all
		cd -

	done
	return
}

function tarRopository()
{
	echo $1
	for val in $1; do
		tmp=${val#*:}
		group=${tmp%/*}
		repository=${tmp%.*}

		tarDir=$TAR_DIR_NAME/$group

		if [ ! -e $tarDir ]; then
			mkdir -p $tarDir || echo "err: mkgroup -p $tarDir" 
		   	echo "OK..."
		fi

		echo "tar $TAR_DIR_NAME/$repository.tar.xz"
		tar -C $group -cJf $TAR_DIR_NAME/$repository.tar.xz ${repository#*/}
	done

	return
}

function delRopository()
{
	for val in $1; do
		tmp=${val#*:}
		group=${tmp%/*}
	
		if [ -e $group ]; then
			rm -rf $group
		fi
	done

	return
}



declare -a list
i=0

while read -r line
do
	if [ "$line" == "" ]; then
#		echo "skip line."
		continue
	fi

	list[$i]=$line
	((i++))

done < $FILE


for val in ${list[@]}; do
	echo $val
done

echo "------ start task ------"
case $CMD in
	clone)
		echo "task: clone"
		gitClone "${list[*]}"
		;;

	fetch)
		echo "task: fetch"	
		;;
	pull)
		echo "task: pull --all"
		gitPull "${list[*]}"
		;;
	tar)
		echo "task: tar -cJf"
		tarRopository "${list[*]}"
		;;
	del)
		echo "task: del Ropository"
		delRopository "${list[*]}"	
		;;
	*)
		echo "invaild CMD"
esac
			

