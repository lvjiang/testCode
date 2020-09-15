#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int value_1 ;
int value_2;
int count;

pthread_mutex_t lock;//定义锁的变量

void *handler_1(void *arg);
void *handler_2(void *arg);

int main(int argc, const char *argv[])
{
	pthread_t *thread_1;
	pthread_t *thread_2;

	//锁的初始化
	if (pthread_mutex_init(&lock, NULL) != 0)
	{
		perror("fail to init lock");
		return -1;
	}

	if (pthread_create(thread_1, NULL, handler_1, NULL)  !=0 )
	{
		perror("fail to pthread_create");
		return -1;
	}

	if (pthread_create(thread_2, NULL, handler_2, NULL)  !=0 )
	{
		perror("fail to pthread_create");
		return -1;
	}

	pthread_join(*thread_1, NULL);
	pthread_join(*thread_2, NULL);

	pthread_mutex_destroy(&lock);//销毁一把锁
	return 0;
}

void *handler_1(void *arg)
{
	while (1)
	{
		count++;
		//对临界资源加锁，保证了两条赋值语句的完整性
//		pthread_mutex_lock(&lock);
		value_1 = count;
		value_2 = count;
//		pthread_mutex_unlock(&lock);
	}
}

void *handler_2(void *arg)
{
	while (1)
	{
//		pthread_mutex_lock(&lock);
		if (value_1 != value_2)
			printf("value_1 = %d, value_2 = %d\n", value_1, value_2);
//		pthread_mutex_unlock(&lock);
	}
}
