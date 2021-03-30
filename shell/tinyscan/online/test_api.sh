PROTOCOL="https://"
IPADDR="tinyscan.qinglianyun.com"
PORT="8080"
FIRMWARE_PATH="/v1/firmware/create"
FIRMWARE_PDF="/v1/firmware/pdf"
FIRMWARE_RESULT="/v1/firmware/result"

id="d38aba3a5af02051ede45d16b30a10e5"
token="6dcba9a8f4ae365da5e8d499d53d8f96"
taskid="ddaf98033be68f445d2c655519fe3b49"



tt=$(date +%s) 
#tt=$((tt - 1000))
sign=$(echo -n "${id}${tt}${token}" | md5sum | cut -d ' ' -f 1)
#echo $sign
#echo "${PROTOCL}${IPADDR}:${PORT}${FIRMWARE_PATH}"
#curl -k -H "Scan-Id:${id}" -H "Scan-Tt:${tt}" -H "Scan-Sign:${sign}" -F "email=lala@gaga" -F "firmware=@$1" "${PROTOCOL}${IPADDR}:${PORT}${FIRMWARE_PATH}" 
curl -v -H "Scan-Id:${id}" -H "Scan-Tt:${tt}" -H "Scan-Sign:${sign}" "${PROTOCOL}${IPADDR}:${PORT}${FIRMWARE_RESULT}?taskid=${taskid}"
#curl -v -X GET -k -H "Scan-Id:${id}" -H "Scan-Tt:${tt}" -H "Scan-Sign:${sign}" "${PROTOCOL}${IPADDR}:${PORT}${FIRMWARE_PDF}?taskid=${taskid}" -o lvsj.pdf

exit
i=0
while ((i < 100))
do
	echo -n "$i "
	tt=$(date +%s) 
	tt=$((tt - 1000))
	sign=$(echo -n "${id}${tt}${token}" | md5sum | cut -d ' ' -f 1)
	curl -k -H "Scan-Id:${id}" -H "Scan-Tt:${tt}" -H "Scan-Sign:${sign}" -F "email=lala@gaga" -F "firmware=@$1" "${PROTOCOL}${IPADDR}:${PORT}${FIRMWARE_PATH}" 
	echo ""
	((i++))
done

