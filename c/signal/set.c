#include<stdio.h>
#include<signal.h>

void printsigset(sigset_t *pending)
{
	int i = 1;
	for(;i < 32;i++)
	{
		//pending信号集中的有效信号如果包含i，返回1，不包含返回0
		if(sigismember(pending,i))
			printf("1 ");
		else
			printf("0 ");
	}
	printf("\n");
}

int main() {
	sigset_t set;
	sigemptyset(&set);
	

	sigprocmask(SIG_BLOCK, NULL, &set);

	printsigset(&set);

}
