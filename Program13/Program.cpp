#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

void tolowerstr(string& input)
{
	transform(input.begin(), input.end(), input.begin(), tolower);
}

void tolowerwstr(wstring& input)
{
	transform(input.begin(), input.end(), input.begin(), towlower);
}

template<typename T, void (func)(T&)>
class baselower
{
public:
	baselower(T input) :str(input)
	{
		func(this->str);
	}

public:
	baselower& operator=(const T& input)
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

typedef baselower<string, tolowerstr> lowerstr;
typedef baselower<wstring, tolowerwstr> lowerwstr;

int main(int argc, char* argv [])
{
	lowerstr str("UPDATE");
	cout << (string) str << endl;

	lowerwstr wstr(L"INSERT");
	wcout << (wstring) wstr << endl;
	return 0;
}