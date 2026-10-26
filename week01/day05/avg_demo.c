#include <stdio.h>

int average(int a, int b)
{
	int res = (a + b) /2;
	return res;
}

int main(void)
{
	int v1 = 1;
	int v2 = 2;
	int avg = average(v1, v2);
	printf("average = %d\n",avg);
	return 0;
}
