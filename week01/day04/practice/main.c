#include <stdio.h> 
#include "temp.h"

int main(void)
{
	float t1 = 0.0f;
	float res1 = celsius_to_fahrenheit(t1);
	printf("%.2f Celsius = %.2f Fahrenheit\n",t1, res1);

	float t2 = 100.0f;
	float res2 = celsius_to_fahrenheit(t2);
	printf("%.2f Celsius = %.2f Fahrenheit\n",t2, res2);

	float t3 = 32.0f;
	float res3 = fahrenheit_to_celsius(t3);
	printf("%.2f Fahrenheit = %.2f Celsius\n",t3, res3);

	return 0;
}
