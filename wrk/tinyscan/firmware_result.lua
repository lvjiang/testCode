md5 = require("md5")

user = "b660c00cd827b44bf55dd8aecad3abb6"
token = "fa960e80b4e645429bc218e3857ecd2e"
taskid = "1f47c452d5a05bc82f3b030ae61515dd"

path = "/v1/firmware/result?taskid=" .. taskid

request = function()
	local headers = {}
	local time = os.time()
	headers["Scan-Id"] = user
	headers["Scan-Tt"] = time
	headers["Scan-Sign"] = md5.sumhexa(user..time..token)

	return wrk.format('GET', path, headers, nil)
--	return wrk.format('GET', nil, headers, nil)
end

response = function(status, headers, body)
	if status ~= 200 then
		print("++"..body)
	end
end
