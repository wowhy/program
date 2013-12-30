#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv [])
{
	if (argc == 1)
		return 0;

	if (strcmp(argv[1], "-1") == 0)
	{
		double C = atof(argv[2]);
		printf("F = %.2f", 9.0 / 5.0 * C + 32);
	}

	if (strcmp(argv[1], "-2") == 0)
	{
		double M = atof(argv[2]);
		printf("M1 = %.4f, M2 = %.4f",
			M * (1 / 0.0254),
			M * (1 / 0.0254) / 12);
	}

	if (strcmp(argv[1], "-3") == 0)
	{
		int sum = 0;
		for (int i = 1; i <= 100; i++){
			sum += i;
		}

		printf("1 + 2 + 3 ... + 100 = %d", sum);
	}

	if (strcmp(argv[1], "-4") == 0)
	{
		int N = atoi(argv[2]);
		int sum = 0;
		for (int i = 0; i < N; i++){
			sum += (2 * i) + 1;
		}

		printf("sum = %d", sum);
	}

	if (strcmp(argv[1], "-5") == 0)
	{
		printf("This program finds the largest integer in a list.\n"
			"Enter 0 to signal the end of the list.\n");

		int x = 0;
		int max = 0;
		do
		{
			if (x > max)
				max = x;
			printf("? ");
		} while (scanf_s("%d", &x) == 1 && x != 0);
	
		printf("The largest value is %d\n", max);
	}

	if (strcmp(argv[1], "-6") == 0)
	{
		printf("This program reverses the digits in an integer.\n"
			"Enter a positive integer: ");
		long long x;
		if (scanf_s("%lld", &x))
		{
			printf("The reversed number is ");
			while (x != 0)
			{
				printf("%d", x % 10);
				x /= 10;
			}
		}
	}

	return 0;
}