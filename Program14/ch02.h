#ifndef CH_02_H
#define CH_02_H

#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

/*
第二章：字符串是否包含问题

题目描述

	假设这有一个各种字母组成的字符串A，和另外一个字符串B，字符串里B的字母数相对少一些。
	什么方法能最快的查出所有小字符串B里的字母在大字符串A里都有？
	为了简单起见，我们规定输入的字符串只包含大写英文字母。实现函数bool compare(string &A,string &B)
*/

// 解法一、暴力轮询
bool compare_01(string &a, string &b)
{
	if(b.length() > a.length())
		return false;

	for(char ch : b)
	{
		auto iter = begin(a);
		while(iter != end(a) && *iter != ch)
			++iter;

		if(iter == end(a))
			return false;
	}

	return true;
}


// 解法二、普通排序
bool compare_02(string a, string b)
{
	if(b.length() > a.length()) return false;

	sort(a.begin(), a.end());
	sort(b.begin(), b.end());

	auto pa = a.begin();
	auto pb = b.begin();

	while(pb != b.end())
	{
		while(pa != a.end() && *pa < *pb)
			++pa;

		if(pa == a.end() || *pa > *pb)
			return false;

		++pb;
	}
	
	return true;
}


// 解法三、hashtable
bool compare_03(string &a, string &b)
{
	unordered_map<char, int> have;
	for(auto ch : a)
	{
		auto find = have.find(ch);
		if(find == have.end())
			have.insert(make_pair(ch, 1));
	}

	for(auto ch : b)
	{
		if(have.find(ch) == have.end())
			return false;
	}

	return true;
}

// 解法四、素数相乘
bool compare_04(string &a, string &b)
{
	const int p[26] = 
	{
		2, 3, 5, 7, 11, 13, 17, 
		19, 23, 29, 31, 37, 41, 
		43, 47, 53, 59,61, 67, 
		71, 73, 79, 83, 89, 97, 
		101
	};

	for(int n = 0; n < a.length(); n+=7)
	{
		long long f = 1;
		int count = min(n + 7, (int)a.length());
		for(int i = n; i < count; ++i)
		{
			int x = p[a[i] - 'A'];
			if(f % x)
			{
				f *= x;
			}
		}


	}

	long long f = 1;
	for(auto ch : a)
	{
		int x = p[ch - 'A'];
		if(f % x)
		{
			f *= x;
		}
	}

	for(auto ch : b)
	{
		int x = p[ch - 'A'];
		if(f % x)
			return false;
	}

	return true;
}

string b2s(bool i)
{
	return i ? "true" : "false";
}

#define __COUT_RESULT(MSG, x) cout << #MSG ": " << b2s((x)) << endl; 
#define COUT_RESULT(x) __COUT_RESULT(x, x);

int AppMain_2()
{
	string a = "ABCDEFGHLMNOPQRS";
	string b = "DDDCCCGSRQPO";

	cout << "str a: " << a << endl;
	cout << "str b: " << b << endl;

	COUT_RESULT(compare_01(a,b));
	COUT_RESULT(compare_02(a,b));
	COUT_RESULT(compare_03(a,b));
	COUT_RESULT(compare_04(a,b));

	return 0;
}

#endif