md5 = require("md5")

user = "b660c00cd827b44bf55dd8aecad3abb6"
token = "fa960e80b4e645429bc218e3857ecd2e"
path = "/v1/app/create"


function init(args)
	boundary=[[abcd]]
	cr='\r\n'
	
	local f = io.open("/root/wrk/tinyscan/jinronglicai.apk","rb")
	local len = f:seek("end")
	f:seek("set",0)
	local bin = f:read(len)
	
	file = [[--]]..boundary..cr..[[Content-Disposition: form-data; name="apk"; filename="jinronglicai.apk"]]..cr..[[Content-Type: application/octet-stream]]..cr..cr..bin
	email = cr..[[--]]..boundary..cr..[[Content-Disposition: form-data; name="email";]]..cr..cr..[[lvsj@gaga.com]]
	over = cr..[[--]]..boundary..[[--]]..cr
	body = file..email..over
end

request = function()
	local headers = {}
	local time = os.time()
	headers["Scan-Id"] = user
	headers["Scan-Tt"] = time
	headers["Scan-Sign"] = md5.sumhexa(user..time..token)

	headers["Content-Type"] = "multipart/form-data;boundary="..boundary
	
	return wrk.format('POST', path, headers, body)
end

response = function(status, headers, body)
	if status ~= 200 then
		print(status.."++"..body)
	else
		print(status.."--"..body)
	end
end

