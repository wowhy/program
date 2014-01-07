#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

namespace formatter
{
	enum Symbols
	{
		NONE,
		SELECT,
		FROM,
		WHERE,
		GROUPBY,
		HAVING,
		ORDERBY,
		WITH,
		INSERT,
		UPDATE,
		DELETE,


		BraceLeft, // (
		BraceRight, // )
		DoubleQuot, // "
		Comment, // --
	};

	const char Symbols2String [] =
	{
		"",
		"SELECT",
		"FROM",
		"WHERE",
		"GROUP BY",
		"HAVING",
		"ORDERBY",
		"WITH",
		"INSERT",
		"UPDATE",
		"DELETE",


		"(",
		")",
		"\"",
		"--"
	};

	class SymbolToken
	{
	public:
		SymbolToken()
		{}

		~SymbolToken(){}

	private:
		Symbols symbol;
		string split;
		string start;
		string end;
	};


}

int main(int argc, char* argv [])
{
	return 0;
}