#!/bin/bash

WORK_DIR_NAME=$(cd "$(dirname "$0")"; pwd)
TAR_DIR_NAME=$WORK_DIR_NAME/my_tar
cd $WORK_DIR_NAME

function makeDir()
{
	for val in $1; do
		tmp=${val#*:}
		dir=${tmp%/*}

		if [ -e $dir ]; then
			echo "$dir exists."
		else
			echo "mkdir $dir"
			mkdir $dir
		fi
	done

	return
}

function gitClone()
{
	for val in $1; do
		tmp=${val#*:}
		dir=${tmp%/*}
		repository=${tmp%.*}

		if [ -e $repository ]; then
			echo "$repository exists....."
		else
			cd $dir
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
		dir=${tmp%/*}
		repository=${tmp%.*}

		tarDir=$TAR_DIR_NAME/$dir

		if [ ! -e $tarDir ]; then
			mkdir -p $tarDir || echo "err: mkdir -p $tarDir" 
		   	echo "OK..."
		fi

		echo "tar $TAR_DIR_NAME/$repository.tar.xz"
		tar -C $dir -cJf $TAR_DIR_NAME/$repository.tar.xz ${repository#*/}
	done

	return
}

function delRopository()
{
	for val in $1; do
		tmp=${val#*:}
		dir=${tmp%/*}
	
		if [ -e $dir ]; then
			rm -rf $dir
		fi
	done

	return
}



declare -a file
i=0

while read -r line
do
	if [ "$line" == "" ]; then
#		echo "skip line."
		continue
	fi

	file[$i]=$line
	((i++))

done < $1


for val in ${file[@]}; do
	echo $val
done

echo "------ start task ------"

case $2 in
	clone)
		echo "task: clone"
		gitClone "${file[*]}"
		;;

	fetch)
		echo "task: fetch"	
		;;
	pull)
		echo "task: pull --all"
		gitPull "${file[*]}"
		;;
	tar)
		echo "task: tar -cJf"
		tarRopository "${file[*]}"
		;;
	del)
		echo "task: del Ropository"
		delRopository "${file[*]}"	
		;;
	*)
		echo "invaild"
esac
			


