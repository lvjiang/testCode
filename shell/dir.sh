#!/bin/bash

WORK_DIR_NAME=$(cd "$(dirname "$0")"; pwd)
cd $WORK_DIR_NAME
pwd


WORK_DIR_NAME="1111111"
echo "1 dir: $WORK_DIR_NAME"
echo "exec subdir"
./test/subdir.sh

echo "2 dir: $WORK_DIR_NAME"


echo "after exec subdir"
pwd
