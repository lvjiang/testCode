#!/bin/bash

#"%s?act=%s&url=%s&maxConnect=%d&type=%s&t=%d&username=%s&password=%s&cookie=%s&disallow=%s&exts=%s

function Usage() {
	self=$(basename $0)
	printf "Usage:\n"
	printf "\t$self -u URL -c Cookie\n"
	printf "\t$self -h\n"
}

while getopts c:u:h opt; do
	case $opt in
		c)
			COOKIE=$OPTARG
			;;
		u)
			URL=$OPTARG
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


ADDR="http://192.168.1.233/aiscanner/api.php"
ACT="add"

CONNECT=6
TYPE="normal"
TIME=$(date +%s)

USER="tinyscan"
PASSWORD="590a574a40aeda0e57c1c1e3e1c2d1a5"

EXTS="SqlScanner,XSS,Pollution,Struts,Include,URLRedirect,Nginx,SVN,PaddingOracle,DirectoryListing,ApacheCGI,DNS,FlashCrossdomain,Mysql,Ftp,WordPress,Webs,Overflows,Systems,Finger,Robots,Domain"

OLD_IFS=$IFS
IFS=','
for val in $EXTS; do
	echo "$ADDR?act=$ACT&url=$URL&maxConnect=$CONNECT&type=$TYPE&t=$TIME&username=$USER&password=$PASSWORD&cookie=$COOKIE&disallow=$DISALLOW&exts=$val"
	curl "$ADDR?act=$ACT&url=$URL&maxConnect=$CONNECT&type=$TYPE&t=$TIME&username=$USER&password=$PASSWORD&cookie=$COOKIE&disallow=$DISALLOW&exts=$val"
done
IFS=$OLD_IFS
