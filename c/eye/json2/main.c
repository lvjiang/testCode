#include <stdio.h>
#include <stdlib.h>
#include "tiny_json.h"

int main(int argc, const char *argv[]) 
{
	cJSON *lv = cJSON_CreateObject();				
	cJSON_AddStringToObject(lv, "xing", "lv");
	cJSON_AddStringToObject(lv, "ming", "jiang");
	char *str = cJSON_PrintUnformatted(lv);	
	printf("%s\n",str);
	free(str);
	cJSON_Delete(lv);

	cJSON *r = cJSON_CreateObject();
	cJSON_AddStringToObject(r, "mac", "99:02:01:01:01:01");
	cJSON_AddNumberToObject(r, "pid", 1002878951);
	cJSON_AddStringToObject(r, "sign", "b05c196de5bc995283e1042f24259f92");
	cJSON_AddNumberToObject(r, "tt", 1560391844);
	cJSON_AddNumberToObject(r, "init", 1);

	cJSON *data = cJSON_CreateArray();
	cJSON_AddItemToObject(r, "data", data);

	cJSON *pro = cJSON_CreateArray();
	cJSON_AddItemToArray(data, pro);
	
	cJSON_AddItemToArray(pro, cJSON_CreateString("lvsj"));
	cJSON_AddItemToArray(pro, cJSON_CreateNumber(0.000207));
	cJSON_AddItemToArray(pro, cJSON_CreateNumber(0.643592));
	cJSON_AddItemToArray(pro, cJSON_CreateString("deja-dup --prompt"));
	cJSON_AddItemToArray(pro, cJSON_CreateNumber(2866));
	cJSON_AddItemToArray(pro, cJSON_CreateNumber(1969));
	cJSON_AddItemToArray(pro, cJSON_CreateNumber(1560309548));
	cJSON_AddItemToArray(pro, cJSON_CreateString("lvsj"));
	
	pro = cJSON_CreateArray();
	cJSON_AddItemToArray(data, pro);
	
	str = cJSON_PrintUnformatted(r);	
	printf("%s\n",str);
	free(str);

	str = cJSON_PrintBuffered(r, 8, 0);
	printf("%s\n", str);
	
	char line[2560];
	FILE *fp=fopen("history","r");
	fgets(line, sizeof(line), fp);
	printf("line=%s\n", line);
	cJSON *item = cJSON_Parse(line+2);
	printf("cjson=%s", cJSON_Print(item));
	fclose(fp);
}
