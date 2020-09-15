#include<stdio.h>

int main()
{
	int month = 120;
	double X = 4013;
	double rate = 0.005;
	double sum = 0;
	int i;
	printf("store every month X = ?\n");
	scanf("%lf", &X);
	printf("month = ?\n");
	scanf("%d", &month);
	printf("rate of month = ?\n");
	scanf("%lf", &rate);

	for(i = month; i > 0; i--) {
		sum += sum * rate + X;
	}
	printf("sum = %f\n", sum);
}
