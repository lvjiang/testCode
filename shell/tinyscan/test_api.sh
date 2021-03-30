PROTOCOL="https://"
IPADDR="39.106.134.147"
PORT="8087"
FIRMWARE_PATH="/v1/firmware/create"
FIRMWARE_PDF="/v1/firmware/pdf"

id="6512ea34f32663528144a310496ca71a"
token="9eb79e436c7377074ed23ef95fa83168"
taskid="2522855e97dedf920ba2fc495fe5c204"



tt=$(date +%s) 
#tt=$((tt - 1000))
sign=$(echo -n "${id}${tt}${token}" | md5sum | cut -d ' ' -f 1)
#echo $sign
#echo "${PROTOCL}${IPADDR}:${PORT}${FIRMWARE_PATH}"
#curl -k -H "Scan-Id:${id}" -H "Scan-Tt:${tt}" -H "Scan-Sign:${sign}" -F "email=lala@gaga" -F "firmware=@$1" "${PROTOCOL}${IPADDR}:${PORT}${FIRMWARE_PATH}" 

curl -v -X GET -k -H "Scan-Id:${id}" -H "Scan-Tt:${tt}" -H "Scan-Sign:${sign}" "${PROTOCOL}${IPADDR}:${PORT}${FIRMWARE_PDF}?taskid=${taskid}" -o lvsj.pdf

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

