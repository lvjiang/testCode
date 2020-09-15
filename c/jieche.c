#include <stdio.h>
int main()
{
	int Sum = 0;
	int i, j, temp;
	for(i = 1; i <= 10; i++) {
		temp = i;
		for(j = i -1; j > 0; j--) {
			temp *= j;
		}
		Sum += temp;
	}
	printf("Sum = %d\n", Sum);
}


