#!/bin/bash

PROTOCOL="https://"
#IPADDR="39.106.134.147"
#IPADDR="47.95.200.163"
IPADDR="tinyscan.qinglianyun.com"
PORT="8080"

FIRMWARE_CREATE_PATH="/v1/firmware/create"
FIRMWARE_RESULT_PATH="/v1/firmware/result"
FIRMWARE_PDF_PATH="/v1/firmware/pdf"

APP_CREATE_PATH="/v1/app/create"
APP_RESULT_PATH="/v1/app/result"
APP_PDF_PATH="/v1/app/pdf"

WEB_CREATE_PATH="/v1/web/create"
WEB_RESULT_PATH="/v1/web/result"
WEB_PDF_PATH="/v1/web/pdf"

PROFILE_PATH="/v1/user/profile"

SCAN_URL="http://testphp.vulnweb.com/AJAX/"
EMAIL="lvshuaijiang@qinlianyun.com"


function Usage() {
	self=$(basename $0)
	printf "Usage:\n"
	printf "\t$self -c cmd [-f file] [-u userid] [-p password] [-t taskid]\n"
	printf "\t-h show this help\n"
	printf "\t-c CMD\n"
	printf "\t\t 1:firmware create\n"
	printf "\t\t 2:firmware get result\n"
	printf "\t\t 3:firmware get pdf\n"
	printf "\t\t 4:app create\n"
	printf "\t\t 5:app get result\n"
	printf "\t\t 6:app get pdf\n"
	printf "\t\t 7:web create\n"
	printf "\t\t 8:web get result\n"
	printf "\t\t 9:web get pdf\n"
	printf "\t\t10:set user profile\n"
}

while getopts c:f:u:p:t: opt; do
	case $opt in
		c)
			CMD=$OPTARG
			;;
		f)
			FILE=$OPTARG
			;;
		u)
			USERID=$OPTARG
			;;
		p)
			TOKEN=$OPTARG
			;;
		t)
			TASKID=$OPTARG
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

USERID=${USERID:="b660c00cd827b44bf55dd8aecad3abb6"}
TOKEN=${TOKEN:="fa960e80b4e645429bc218e3857ecd2e"}


tt=$(date +%s) 
#tt=$((tt - 1000))
sign=$(echo -n "${USERID}${tt}${TOKEN}" | md5sum | cut -d ' ' -f 1)

function scan_create() {
	curl -v -H "Scan-Id:${USERID}" -H "Scan-Tt:${tt}" -H "Scan-Sign:${sign}" -F "email=${EMAIL}" -F "firmware=@${FILE}" "${PROTOCOL}${IPADDR}:${PORT}${1}" 
}

function scan_result() {
	curl -X GET -v -H "Scan-Id:${USERID}" -H "Scan-Tt:${tt}" -H "Scan-Sign:${sign}" "${PROTOCOL}${IPADDR}:${PORT}${1}?taskid=${TASKID}"
}

function scan_pdf() {
	curl -X GET -H "Scan-Id:${USERID}" -H "Scan-Tt:${tt}" -H "Scan-Sign:${sign}" "${PROTOCOL}${IPADDR}:${PORT}${1}?taskid=${TASKID}" -o ${TASKID}.pdf
}

function scan_app_create() {
	curl -v -H "Scan-Id:${USERID}" -H "Scan-Tt:${tt}" -H "Scan-Sign:${sign}" -F "email=${EMAIL}" -F "apk=@${FILE}" "${PROTOCOL}${IPADDR}:${PORT}${1}" 
}

function scan_web_create() {
	curl -X POST -v -H "Scan-Id:${USERID}" -H "Scan-Tt:${tt}" -H "Scan-Sign:${sign}" "${PROTOCOL}${IPADDR}:${PORT}${1}" -d "{\"url\": \"${SCAN_URL}\", \"connect\": 3, \"email\": \"${EMAIL}\"}"
}

function scan_set_profile() {
	curl -X POST -v -H "Scan-Id:${USERID}" -H "Scan-Tt:${tt}" -H "Scan-Sign:${sign}" "${PROTOCOL}${IPADDR}:${PORT}${1}" -d "{\"project_name\": \"tinyscan_lvsj\", \"company\": \"lvsj\", \"contact\": \"${EMAIL}\", \"tip\":\"lvsj test\", \"cover_logo\":\"cover\", \"header_logo\":\"header\", \"watermark\":\"watermark\"}"
}

case $CMD in
	1)
		echo "firmware create"
		scan_create ${FIRMWARE_CREATE_PATH}
		;;

	2)
		echo "firmare result"
		scan_result ${FIRMWARE_RESULT_PATH}
		;;
	3)
		echo "firmare pdf"
		scan_pdf ${FIRMWARE_PDF_PATH}
		;;
	4)
		echo "app create"
		scan_app_create ${APP_CREATE_PATH}
		;;

	5)
		echo "app result"
		scan_result ${APP_RESULT_PATH}
		;;
	6)
		echo "app pdf"
		scan_pdf ${APP_PDF_PATH}
		;;
	7)
		echo "web create"
		scan_web_create ${WEB_CREATE_PATH}
		;;

	8)
		echo "web result"
		scan_result ${WEB_RESULT_PATH}
		;;
	9)
		echo "web pdf"
		scan_pdf ${WEB_PDF_PATH}
		;;
	10)
		echo "set profile"
		scan_set_profile ${PROFILE_PATH}
		;;
	*)
		echo "invaild CMD"
esac

# new line
echo ""
