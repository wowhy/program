#include <iostream>
#include <algorithm>
#include <string>

#include "MyStack.h"

using namespace std;

void tolowerstr(string& input)
{
	transform(input.begin(), input.end(), input.begin(), tolower);
}

void tolowerwstr(wstring& input)
{
	transform(input.begin(), input.end(), input.begin(), towlower);
}

void toupperstr(string& input)
{
	transform(input.begin(), input.end(), input.begin(), toupper);
}

void toupperwstr(wstring& input)
{
	transform(input.begin(), input.end(), input.begin(), towupper);
}

template<class T, void (_transform)(T&)>
class base_str
{
public:
	base_str(T input) :str(input)
	{
		_transform(this->str);
	}

public:
	base_str& operator=(const T& input)
	{
		str = input;
		func(str);
		return *this;
	}

	operator T(){ return this->str; }

	T tostr()
	{
		return this->str;
	}

private:
	T str;
};

typedef base_str<string, tolowerstr> lowerstr;
typedef base_str<wstring, tolowerwstr> lowerwstr;
typedef base_str<string, toupperstr> upperstr;
typedef base_str<wstring, toupperwstr> upperwstr;

int main(int argc, char* argv [])
{
	lowerstr l_str("UPDATE");
	cout << (string) l_str << endl;

	lowerwstr l_wstr(L"INSERT");
	wcout << (wstring) l_wstr << endl;


	upperstr u_str("update");
	cout << (string) u_str << endl;

	upperwstr u_wstr(L"insert");
	wcout << (wstring) u_wstr << endl;


	MyStack<int*> stack([](int* e){ delete e; });

	stack.Push(new int(10));
	stack.Push(new int(20));

	auto action = [](int* e) -> int 
	{
		int t = *e;
		delete e;
		return t;
	};

	cout << action(stack.Pop()) << endl;
	cout << action(stack.Pop()) << endl;

	return 0;
}