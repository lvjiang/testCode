#include <stdio.h>
#include <signal.h>
#include <unistd.h>
typedef void(*sighandler_t)(int);//函数指针
sighandler_t _handler = NULL;
void myhandler()
{
	printf("myhandler\n");
	signal(2,_handler);//恢复默认处理
}
int main()
{
	_handler = signal(2,myhandler);//捕捉2号信号
	while(1);
	return 0;
}

