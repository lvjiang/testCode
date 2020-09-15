#include <stdio.h>

int main()
{
	double sum;
	double rate;
	int month;
	double X;
	int i;

	printf("tolal sum = ?\n");
	scanf("%lf", &sum);
	printf("every month rate = ?\n");
	scanf("%lf", &rate);

	printf("month = ?\n");
	scanf("%d", &month);
	printf("get X = ? every month\n");
	scanf("%lf", &X);

	for(i = 1; i <= month; i++) {
		if(sum >= X) {
			sum = sum + sum * rate - X;
		} 
		if (sum < X) {
			printf("max use %d month\n", i);
			break;
		}
	}

	printf("after %d month sum = %f\n", i, sum);


}
