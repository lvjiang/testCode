#!/bin/bash


echo "1 subdir: $WORK_DIR_NAME"
WORK_DIR_NAME=$(cd "$(dirname "$0")"; pwd)
cd $WORK_DIR_NAME
echo "2 subdir: $WORK_DIR_NAME"

cd /etc 
ls 
