#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

namespace formatter
{
	class Base
	{
	public:
		Base(){}
		virtual ~Base(){}


	public:
		virtual string ToString()
		{
			return content;
		}

	private:
		int depth;
		string content;
	};

	class Keyword : public Base
	{
	};

	class Select : public Keyword
	{
	};

	class Where : public Keyword
	{
	};

	class QueryFormatter : public Base
	{
	public:
		static QueryFormatter Create(string content)
		{
			return QueryFormatter();
		}

	public:
		virtual string ToString()
		{
			string result;
			for (auto i : nodes)
			{
				result += i->ToString();
			}
		}

	private:
		vector<Base*> nodes;
	};

	class InsertFormatter : public Base
	{
	};

	class UpdateFormatter : public Base
	{
	};

	string Formatter(string content)
	{
		// if content is SELECT
		// if content is INSERT
		// if content is UPDATE
		// if content is DELETE
	}
}

int main(int argc, char* argv [])
{
	return 0;
}