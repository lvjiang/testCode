#define _XOPEN_SOURCE
#include <stdio.h>
#include <string.h>
#include <time.h>

char *string = "Jan 24 13:17:21 huawei admin[14546]: Mon Jan 24  13:17:21  CST 2000 : admin pts/1 192.168.7.36: 14410: /home/admin: ls: 0";
typedef struct {
	char *username, *userip, *session_id, *cmd;
	time_t t;
}history_item;

static int history_parse_line(char *line, history_item *it)
{
	char *ts;
	char *p, *next;
	struct tm tm;

	/* Jan 24 13:17:21 huawei admin[14546]: Mon Jan 24  13:17:21  CST 2000 : admin pts/1 192.168.7.36: 14410: /home/admin: ls: 0 */
	if ((ts = strchr(line, ']') + 3)    //Jan 24 09:44:31 huawei admin[12352]
			&& (p = strchr(ts, ':'))  //: Mon Jan 24  09:
			&& (p = strtok_r(p + 5, ":", &next))
			&& (it->username = strtok_r(NULL, ": ", &next))) {
		printf("p: %shh\n", p);
		printf("1 %s\n", next);
	} else {
		goto err;
	}
		printf("2 %s\n", ts);

	if(strptime(ts, "%a %b %d %H:%M:%S CST %Y", &tm) && (it->t = mktime(&tm)) != -1) {
	} else {
		it->t = time(NULL);
	}

	if((p = strtok_r(NULL, ": ", &next))    //pts/1
			&& (it->userip = strtok_r(NULL, ": ", &next))
			&& (it->session_id = strtok_r(NULL, ": ", &next))   //pid
			&& (p = strtok_r(NULL, ": ", &next))   //pwd
			&& (it->cmd = strtok_r(NULL, ": ", &next))) {   //cmd
		printf("3 %s\n", next);
	} else {
		goto err;
	}
	return 0;

err:
	return -1;
}

int main(int argc, char *argv[])
{
	char line[256];
	history_item it;
	
	sprintf(line, "%s", string);
	history_parse_line(line, &it);
	printf("%s-%s-%s:%s:%ld\n", it.userip, it.username, it.session_id, it.cmd, it.t);
	
	printf("line: %shhh\n", line);

	return 0;
}
