md5 = require("md5")

user = "b660c00cd827b44bf55dd8aecad3abb6"
token = "fa960e80b4e645429bc218e3857ecd2e"
path = "/v1/firmware/create"

function init(args)
	boundary=[[abcd]]
	cr='\r\n'
	file = [[--]]..boundary..cr..[[Content-Disposition: form-data; name="firmware"; filename="test.sh"]]..cr..[[Content-Type: application/octet-stream]]..cr..cr..[[helloworld]]
	email = cr..[[--]]..boundary..cr..[[Content-Disposition: form-data; name="email";]]..cr..cr..[[lvsj@gaga.com]]
	over = cr..[[--]]..boundary..[[--]]..cr
	body = file..email..over
end

function delay()
	return 100
end

request = function()
	local headers = {}
	local time = os.time()
	headers["Scan-Id"] = user
	headers["Scan-Tt"] = time
	headers["Scan-Sign"] = md5.sumhexa(user..time..token)
	headers["Content-Type"] = "multipart/form-data;boundary="..boundary
	
	local req =  wrk.format('POST', path, headers, body)
	print(req)
	return req

	--return wrk.format('POST', path, headers, body)
end

response = function(status, headers, body)
	if status ~= 200 then
		print(status.."++"..body)
	else
		print(status.."--"..body)
	end
end

