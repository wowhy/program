#include <iostream>
#include "RegexSearch.h"

using namespace std;

void Help()
{
}

int main(int argc, char* argv [])
{
	try
	{
		search::RegexSearch app({ argv[0], argv[0] });
		app.Start();
	}
	catch (int ex)
	{
		if (ex == search::CommandException)
			Help();
	}

	return 0;
}