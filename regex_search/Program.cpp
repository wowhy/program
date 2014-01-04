#include <iostream>
#include "RegexSearch.h"

using namespace std;

void Help()
{
	cout << "usage: " << endl;
}

int main(int argc, char* argv [])
{
	try
	{
		vector<string> args;
		for (int i = 1; i < argc; ++i)
		{
			args.push_back(argv[i]);
		}

		search::RegexSearch app(args);
		app.Start();
	}
	catch (int ex)
	{
		if (ex == search::CommandException)
			Help();
	}

	return 0;
}