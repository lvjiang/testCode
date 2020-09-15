#include <stdio.h>
#include "../include/div.h"

int divide(int x, int y)
{
	if ( x % y != 0) {
		printf("\n Warning: Interger Division May Have Accuracy Loss.\n");
	}
	return x / y;
}
