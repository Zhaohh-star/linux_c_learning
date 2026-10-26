static int add(int a, int b)
{
	int result = a + b;
	return result;
}
int main(void)
{
	int x = 3;
	int y = 4;
	int sum = add(x, y);
	return sum == 7 ? 0 : 1;
}
