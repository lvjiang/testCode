#include <stdio.h>
#include <string.h>

int tool_ip2str(int ip,char *const str, size_t size)
{
	if (NULL == str) {
		printf("tool %s input error!", __FUNCTION__);
		return -1;
	}
	memset(str, 0, size);
	snprintf(str, size, "%u.%u.%u.%u",
			(ip>>24)&0xff, (ip>>16)&0xff, (ip>>8)&0xff, ip&0xff);
	return 0;
}


int main(int argc, const char *argv[])
{
	int ip = 0x12345678;
	char strip[18];

	tool_ip2str(ip, strip, sizeof(strip));
	printf("strip=%s\n", strip);
	return 0;
}
