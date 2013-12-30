#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma region 1
enum weekdayT
{
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday
};

weekdayT NextDay(weekdayT d)
{
	if (d == Sunday)
		return Monday;

	return (weekdayT) (d + 1);
}

weekdayT PreviousDay(weekdayT d)
{
	if (d == Monday)
		return Sunday;

	return (weekdayT) (d - 1);
}

weekdayT IncrementDay(weekdayT d, int n)
{
	if (n == 0)return d;

	weekdayT result = d;

	if (n > 0)
	{
		for (int i = 0; i < n; i++)
			result = NextDay(result);
	}
	else
	{
		for (int i = 0; i > n; i--)
			result = PreviousDay(result);
	}

	return result;
}

const char* getWeekDay(weekdayT d)
{
	static const char* weekdays[] = 
	{
		"Monday",
		"Tuesday",
		"Wednesday",
		"Thursday",
		"Friday",
		"Saturday",
		"Sunday"
	};

	return weekdays[(int)d];
}

void test1()
{
	weekdayT today = Monday;

	printf("Today is %s.\n", getWeekDay(today));
	printf("NextDay is %s.\n", getWeekDay(NextDay(today)));
	printf("PreviousDay is %s.\n", getWeekDay(PreviousDay(today)));

	printf("IncrementDay(5) is %s.\n", getWeekDay(IncrementDay(today, 5)));
	printf("IncrementDay(-5) is %s.\n", getWeekDay(IncrementDay(today, -5)));
}
#pragma endregion

#pragma region 2
bool IsSorted(int* arr, int n)
{
	int t = *arr;
	for (int i = 1, *p = arr + 1; i < n; i++, p++)
	{
		if (*p < t)
			return false;
		t = *p;
	}

	return true;
}

const char* getIsSorted(bool b)
{
	return b ? "SORTED" : "NOT SORTED";
}

void test2()
{
	int a [] = { 1, 2, 3, 4, 5 };
	int b [] = { 2, 3, 4, 1, 2 };
	printf("[1, 2, 3, 4, 5] is %s\n", getIsSorted(IsSorted(a, sizeof(a) / sizeof(int))));
	printf("[2, 3, 4, 1, 2] is %s\n", getIsSorted(IsSorted(b, sizeof(b) / sizeof(int))));
}

#pragma endregion

#pragma region 3
void test3()
{
	bool a[1001];
	for (int i = 2; i <= 1000; i++)
		a[i] = true;
	for (int i = 2; i <= 500; i++)
	{
		if (!a[i]) continue;

		int j = i * 2;
		while (j <= 1000)
		{
			a[j] = false;
			j += i;
		}
	}

	for (int i = 2; i <= 1000; i++)
	{
		if (a[i])
		{
			printf("%d\t", i);
		}
	}
}
#pragma endregion

#pragma region 4
int RemoveZeroElements(int* arr, int n)
{
	bool flag;
	for (int i = 0; i < n; i++)
	{
		if (arr[i] == 0)
		{
			flag = false;
			for (int j = i + 1; j < n; j++)
			{
				if (arr[j] != 0)
				{
					flag = true;
					arr[i] = arr[j];
					arr[j] = 0;
					break;
				}
			}

			if (!flag)
			{
				return i;
			}
		}
	}

	//for (int i = 0; i < n; i++)
	//{
	//	if (arr[i] == 0)
	//		return i;
	//}

	return n;
}

void test4()
{
	int scores [] = { 0, 65, 0, 95, 79, 0, 0, 0, 82, 84, 0, 94, 0, 0, 86, 90, 91, 0 };
	int n = sizeof(scores) / sizeof(int);
	n = RemoveZeroElements(scores, n);
	for (int i = 0; i < n; i++)
	{
		printf("%d\t", scores[i]);
	}
}

#pragma endregion

int main(int argc, char* argv[])
{
	if (argc == 1)
		return 0;

	if (strcmp(argv[1], "-1") == 0)
	{
		test1();
	}

	if (strcmp(argv[1], "-2") == 0)
	{
		test2();
	}

	if (strcmp(argv[1], "-3") == 0)
	{
		test3();
	}

	if (strcmp(argv[1], "-4") == 0)
	{
		test4();
	}

	return 0;
}