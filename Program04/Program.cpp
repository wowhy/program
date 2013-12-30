#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <exception>

using namespace std;

template<typename T, typename V>
T func1(T b, T e, V f)
{
	T r = e;
	while (b != e){
		if (*b == f){
			r = b;
			break;
		}

		b++;
	}

	return r;
}

void test1()
{
	vector<int> v{ 2, 3, 4, 10, 20, 500 };
	auto i = func1(v.begin(), v.end(), 10);
	if (i != v.end())
		cout << *i << endl;
	else
		cout << "Not found.\n";
}

void test2()
{
	deque<string> dq;
	string input;
	while (cin >> input)
		dq.push_back(input);

	for (auto i = dq.begin(); i != dq.end(); i++)
	{
		cout << *i << endl;
	}
}

void test3()
{
	list<int> l = { 1, 2, 3, 4 };
	vector<double> v1(l.begin(), l.end());
	vector<int> v2(l.begin(), l.end());
	vector<int> v3(v2);
}

void test4()
{
	list<char*> l = { "hello", "world" };
	vector<string> v;
	v.assign(l.begin(), l.end());

	for (auto& s : v){
		cout << s << endl;
	}
}

void test5()
{
	try
	{
		vector<int> v;
		v.at(1);
	}
	catch (out_of_range& ex)
	{
		cout << ex.what() << endl;
	}
}

void test6()
{
	list<int> l = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	auto it = l.begin();
	while (it != l.end()){
		if (*it % 2 == 0)
			it = l.erase(it);
		else
			it++;
	}

	for (auto i : l){
		cout << i << endl;
	}
}

void test7()
{
	vector<int> v = { 1, 2, 3, 4, 5 };
	auto b = v.rbegin();
	while (b != v.rend())
	{
		cout << *b << endl;
		b++;
	}
}

void test8()
{
	map<string, size_t> word_count;
	set<string> exclude = { "The", "But", "And", "Or", "An", "A",
							"the", "but", "and", "or", "an", "a" };
	string word;
	char ch;
	while (cin >> word){
		ch = word[word.size() - 1];
		if (ch == '.' ||
			ch == ',' ||
			ch == '?' ) {
			word.erase(word.end() - 1);
		}

		if (exclude.find(word) == exclude.end())
			++word_count[word];
	}

	for (const auto &w : word_count){
		cout << "[ " << w.first << " ] " << w.second << endl;
		//cout << w.first << "  " << w.second << endl;
	}
}

void test9()
{
	string word;
	int count;
	vector<pair<string, int>> v;

	while (
		(cin >> word) &&
		(cin >> count)){
		v.push_back(make_pair(word, count));
	}

	for (const auto &pair : v){
		cout << "first: \"" << pair.first << "\", second: " << pair.second << endl;
	}
}

int main(int argc, char* argv [])
{
	test9();

	return 0;
}