#include <stdio.h>
#include "temp.h"

float celsius_to_fahrenheit(float c)
{
	float F = c * 9.0f / 5.0f + 32.0f;
	return F;
}
//baijiaojiao
float fahrenheit_to_celsius(float f)
{
	float C = (f - 32.0f) * 5.0f / 9.0f;
	return C;
}

