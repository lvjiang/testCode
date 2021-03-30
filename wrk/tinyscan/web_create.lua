md5 = require("md5")

user = "b660c00cd827b44bf55dd8aecad3abb6"
token = "fa960e80b4e645429bc218e3857ecd2e"

path = "/v1/web/create"
body = [[{"url": "http://testphp.vulnweb.com/AJAX/", "connect": 3, "email": "lvsj@gaga.com"}]]

request = function()
	local headers = {}
	local time = os.time()
	headers["Scan-Id"] = user
	headers["Scan-Tt"] = time
	headers["Scan-Sign"] = md5.sumhexa(user..time..token)

	return wrk.format('POST', path, headers, body)
end

response = function(status, headers, body)
	if status ~= 200 then
		print(status.."++"..body)
	end
end
