#include <Windows.h>
#undef IGNORE

#include <iostream>
#include <unordered_map>
#include <string>
#include <regex>
#include <fstream>
#include <sstream>

#include "RegexSearch.h"


#define DEFAULT_IGNORE_SIZE 20480000

using namespace std;
using namespace search;

static unordered_map<string, Command> commands =
{
	{ "-d", Command::DIR },
	{ "-t", Command::EXT },
	{ "-s", Command::REGEX },
	{ "-sf", Command::REGEX_IN_FILE },
	{ "-i", Command::IGNORE }
};

static unordered_map<Command, string> GetOptions(vector<string> args)
{
	unordered_map<Command, string> options = 
	{
		{ DIR, "D:\\开发相关\\源代码\\MUI\\1.0\\FirstFloor.ModernUI" },
		{ EXT, "*.cs" },
		{ REGEX, "System" }
	};
	return options;
}

static void GetFiles(vector<string> &files, string dir, string ext)
{
	WIN32_FIND_DATA data = {};
	HANDLE hSearch = nullptr;

	hSearch = FindFirstFile((dir + "\\" + ext).c_str(), &data);
	if (hSearch == INVALID_HANDLE_VALUE)
		return;

	do
	{
		if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			files.push_back(dir + "\\" + data.cFileName);
		}
	} while (FindNextFile(hSearch, &data));

	FindClose(hSearch);
}

static void GetAllFiles(vector<string> &files, string dir, string ext)
{
	WIN32_FIND_DATA data = {};
	HANDLE hSearch = nullptr;

	GetFiles(files, dir, ext);

	hSearch = FindFirstFile((dir + "\\*").c_str(), &data);
	if (hSearch == INVALID_HANDLE_VALUE)
		return;

	do
	{
		if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (strcmp(data.cFileName, ".") == 0 ||
				strcmp(data.cFileName, "..") == 0)
				continue;

			GetAllFiles(files, dir + "\\" + data.cFileName, ext);
		}
	} while (FindNextFile(hSearch, &data));

	FindClose(hSearch);
}

static vector<string> GetAllFiles(string dir, string ext)
{
	vector<string> files;
	GetAllFiles(files, dir, ext);
	return files;
}

static bool Search(string filepath, regex search)
{
	ifstream file(filepath);
	if (file.fail())
	{
		return false;
	}

	stringstream ss;
	ss << file.rdbuf();
	file.close();

	if (regex_match(ss.str(), search, regex_constants::match_any))
		return true;

	return false;
}

RegexSearch::RegexSearch(vector<string> args) :options(GetOptions(args))
{
}

RegexSearch::~RegexSearch()
{
}

void RegexSearch::Check() const
{
}

int RegexSearch::GetIgnoreSize() const
{
	auto iter = options.find(Command::IGNORE);
	if (iter != options.end())
	{
		return atoi(iter->second.c_str());
	}

	return DEFAULT_IGNORE_SIZE;
}

regex RegexSearch::GetRegex() const
{
	auto iter = options.find(Command::REGEX);
	if (iter != options.end())
	{
		return regex(iter->second);
	}
	else
	{
		auto path = options.find(Command::REGEX_IN_FILE)->second;
		ifstream file(path);
		if (file.fail())
			throw CommandException;

		stringstream ss;
		ss << file.rdbuf();
		file.close();
		return regex(ss.str());
	}
}

void RegexSearch::Start()
{
	// 检查参数
	this->Check();

	auto size = this->GetIgnoreSize();
	auto searchDir = options[Command::DIR];
	auto ext = options[Command::EXT];
	auto regex = this->GetRegex();

	auto files = GetAllFiles(searchDir, ext);
	cout << "result: " << endl;
	for (auto& file : files)
	{
		if (Search(file, regex))
			cout << file << endl;
	}
}
