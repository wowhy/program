#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <regex>

namespace search
{
	using namespace std;

	const int CommandException = 0x0001;

	enum Command
	{
		NONE,
		DIR,
		EXT,
		REGEX,
		REGEX_IN_FILE,
		CONTENT,
		CONTENT_IN_FILE,
		BACKUP,
		IGNORE
	};

	class RegexSearch
	{
	public:
		RegexSearch(vector<string> args);
		~RegexSearch();

	public:
		void Start();

	private:
		void Check() const;
		int RegexSearch::GetIgnoreSize() const;
		regex RegexSearch::GetRegex() const;

	private:
		unordered_map<Command, string> options;
	};
}
