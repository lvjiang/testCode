#!/bin/sh
#[ -n ${SSH_CLIENT} ] && echo "wuwu..." && exit 0
if [ -n ${SSH_CLIENT} ]; then
echo "wuwu..."
fi
echo "haha..."


if [ ! -e test ]; then
	echo "exist."
else
	echo "no exist."
fi
