#!/bin/bash

WORD="world"
A="a"
AA=

echo "--------------"
echo ${A:-$WORD}
echo ${A}
# a
# a

echo ${AA:-$WORD}
echo ${AA}
# world
# 

echo "==============="
echo ${A:=$WORD}
echo ${A}
# a
# a

AA=${AA:=$WORD}
echo ${AA}
# world
# world 
unset AA

echo "+++++++++++++++++"
echo ${A:+$WORD}
echo ${A}
# world
# a

echo ${AA:+$WORD}
echo ${AA}
#
#

echo "?????????????????"
echo ${A:?$WORLD}
echo ${A}
# a
# a
echo ${AA:?$WORLD}
echo ${AA}
# ./grammer.sh: line 46: AA:
#
