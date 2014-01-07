#include <iostream>
#include <algorithm>
#include <string>

#include "MyStack.h"
#include "tinyxml2.h"

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

void test1()
{
	lowerstr l_str("UPDATE");
	cout << (string) l_str << endl;

	lowerwstr l_wstr(L"INSERT");
	wcout << (wstring) l_wstr << endl;


	upperstr u_str("update");
	cout << (string) u_str << endl;

	upperwstr u_wstr(L"insert");
	wcout << (wstring) u_wstr << endl;
}

void test2()
{
	MyStack<int*> stack([](int* e){ delete e; });

	stack.Push(new int(10));
	stack.Push(new int(20));

	auto clear = [](int* e) -> int
	{
		int t = *e;
		delete e;
		return t;
	};

	cout << clear(stack.Pop()) << endl;
	cout << clear(stack.Pop()) << endl;
}

void test3()
{
	using namespace tinyxml2;

	static const char xml [] =
		"<?xml version=\"1.0\"?>"
		"<root>"
		"<class name=\"TestA\"></class>"
		"<class name=\"TestB\"></class>"
		"</root>";

	XMLDocument doc;
	doc.Parse(xml);

	auto root = doc.FirstChildElement("root");
	auto _class = root->FirstChildElement("class");
	while (_class != nullptr)
	{
		cout << _class->Attribute("name") << endl;
		_class = _class->NextSiblingElement();
	}
}

int main(int argc, char* argv [])
{
	test3();

	return 0;
}