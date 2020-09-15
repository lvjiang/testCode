#include<stdio.h>

int min(int a,int b)
{
		return a<b?a:b;
}
void main()
{
		int a,b,c;
		scanf("%d%d",&a,&b);
		c=min(a,b);
		printf("min=%d\n",c);
}
