#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct student {
	struct list_head node;
	int num;
	int age;
};

struct list_head HEAD;
int main()
{
	struct student *st = NULL;
	struct student *tmp = NULL;
	INIT_LIST_HEAD(&HEAD);

	if(list_empty(&HEAD)){
		printf("%d:list is empty\n", __LINE__);
	}
	
	st = malloc(sizeof(struct student));
	if (NULL == st) {
		printf("%d:malloc fail\n", __LINE__);
	}
	
	st->num = 1;
	st->age = 21;
	list_add(&st->node, &HEAD);

	if(list_empty(&HEAD)){
		printf("%d:list is empty\n", __LINE__);
	}

	st = malloc(sizeof(struct student));
	if (NULL == st) {
		printf("%d:malloc fail\n", __LINE__);
	}
	
	st->num = 2;
	st->age = 21;
	list_add(&st->node, &HEAD);
	
	list_for_each_entry_safe(st,tmp,&HEAD,node){
		list_del(&st->node);	
		printf("st->number=%d\n", st->num);
		free(st);
	}

}	
