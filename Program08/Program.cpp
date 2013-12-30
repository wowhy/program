#include <iostream>
#include <string>
#include <regex>
#include <unordered_map>

using namespace std;

void func1()
{
	unordered_multimap<int, int> m;

	for (int i = 1; i < 10; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			m.insert({ i, j });
		}
	}

	for (int i = 1; i < 10; i++)
	{
		// 1.
		auto count = m.count(i);
		auto iter = m.find(i);
		while (count)
		{
			cout << iter->second << "*"
				<< iter->first << "="
				<< iter->first * iter->second
				<< "\t";
			++iter;
			--count;
		}
	}
}

char* my_itoa(int i)
{
	const int INT_DIGITS = 19;
	static char buf[INT_DIGITS + 2];
	char* p = buf + INT_DIGITS + 2;
	if (i >= 0)
	{
		do
		{
			*--p = '0' + (i % 10);
			i /= 10;
		} while (i != 0);
	}
	else
	{
		do
		{
			*--p = '0' - (i % 10);
			i /= 10;
		} while (i != 0);
	
		*--p = '-';
	}

	return p;
}

void func2()
{
	int a = 100;
	int b = -20;
	int c = 8212391;
	cout << "a = " << my_itoa(a) << endl;
	cout << "b = " << my_itoa(b) << endl;
	cout << "c = " << my_itoa(c) << endl;
}

void func3()
{
	string input = "http://tieba.baidu.com/f?kw=surface";
	regex split(R"((://)|\.|/|\?)");
	sregex_token_iterator
		first{ input.begin(), input.end(), split, -1 },
		last;
	//vector<string> v = { first, last };
	
	while (first != last)
	{
		cout << *first << endl;
		first++;
	}
}

void func4()
{
	string raw_narrow = R"((://)|\.|/|\?)";
	cout << raw_narrow;

}

int main()
{
	func3();
	return 0;
}