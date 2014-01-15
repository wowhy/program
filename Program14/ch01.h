#ifndef CH_01_H
#define CH_01_H

#include <iostream>
#include <assert.h>

using namespace std;

/*
第一章：左旋转字符串

题目描述
定义字符串的左旋转操作:
	把字符串前面的若干个字符移动到字符串的尾部,如把字符串 abcdef 左旋转 2 位得到字符串 cdefab。
	请实现字符串左旋转的函数,要求对长度为 n 的字符串操作的时间复杂度为 O(n),空间复杂度为 O(1)。

*/


// 解法一、暴力移位法

// 左移动一位
void left_shift_one(char *s, int n)
{
	assert(s != nullptr);
	char t = *s;
	int i = 0;
	
	while(i++ < n)
	{
		*(s+i-1) = *(s+i);
	}

	*(s+n-1) = t;
}

char* left_shift_m(char *s, int n, int m)
{
	while(m--)
	{
		left_shift_one(s, n);
	}

	return s;
}


// 解法二、三步翻转法
void __reverse(char *s, int from, int to)
{
	assert(s != nullptr);
	assert(from >= 0);

	while(from < to)
	{
		char tmp = s[from];
		s[from++] = s[to];
		s[to--] = tmp;
	}
}

char* left_shift(char *s, int n, int m)
{
	assert(m >= 0);
	m %= n;	

	if(m == 0) return s;

	//__reverse(s, 0, m - 1);
	//__reverse(s, 0, n - 1);
	//__reverse(s, 0, n - m - 1);

	__reverse(s, 0, m - 1);
	__reverse(s, m, n - 1);
	__reverse(s, 0, n - 1);

	return s;
}

int AppMain_1()
{
	char str[] = "hello, world!";

	cout << "func 1:" << endl;
	cout << "before: " << str << endl;
	cout << "after: " << left_shift_m(str, strlen(str), 4) << endl;

	strcpy_s(str, "hello, world!");

	cout << "func 2:" << endl;
	cout << "before: " << str << endl;
	cout << "after: " << left_shift(str, strlen(str), 4) << endl;

	return 0;
}

#endif