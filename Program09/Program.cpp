#include <iostream>
#include <string>
#include <regex>
#include <vector>

// "(select)(.+)(from)"   "[,]"
// "(from)(.+)( where | on | having | groups+by |orders+by | ;)"     "(,|s+lefts+joins+|s+rights+joins+|s+inners+joins+)"

namespace sql_formatter
{
	using namespace std;

	class SqlSegment
	{
	public:
		SqlSegment(string caluse, string split) :_caluse(caluse), _split(split)
		{
		}

		string GetCaluse()
		{
			return _caluse;
		}

		string GetSplit()
		{
			return _split;
		}

	private:
		string _caluse;
		string _split;
	};

	class BaseSqlFormatter
	{
	public:
		BaseSqlFormatter(string originalSql) :_originalSql(originalSql)
		{
		}

		virtual ~BaseSqlFormatter()
		{
		}

	protected:
		string _originalSql;
		vector<SqlSegment> _segments;

	public:
		virtual string ToString() = 0;
	};

	class SelectSqlFormatter : public BaseSqlFormatter
	{
	public:
		SelectSqlFormatter(string originalSql) :BaseSqlFormatter(originalSql)
		{
			InitSqlSegments();
		}

		~SelectSqlFormatter()
		{
		}

	public:
		string ToString()
		{
			string result = "";

			for (auto& segment : _segments)
			{
				regex reg(segment.GetCaluse());
				sregex_iterator first = {
					_originalSql.begin(),
					_originalSql.end(),
					reg
				}, last;

				while (first != last)
				{
					if (first->length() > 0)
					{
						cout << first->begin()->str() << endl;
					}

					++first;
				}
			}

			return result;
		}

	private:
		void InitSqlSegments()
		{
			// (select)(.+)(from)
			// (from)(.+)( where | group by | having | order by |;)
			// (where)(.+)( group by | having | order by |;)
			// group by
			// having
			// order by

			//_segments.push_back(SqlSegment("(select)(.+)(from)", "[,]"));
			//_segments.push_back(SqlSegment(
			//	"(from) (. + )(where | on | having | groups + by | orders + by | ;)",
			//	"(, | s + lefts + joins + | s + rights + joins + | s + inners + joins + )"));
		}
	};

	class UpdateSqlFormatter : public BaseSqlFormatter
	{
	public:
		UpdateSqlFormatter(string originalSql) :BaseSqlFormatter(originalSql){}

	public:
		string ToString()
		{
			return "";
		}
	};

	class InsertSqlFormatter : public BaseSqlFormatter
	{
	public:
		InsertSqlFormatter(string originalSql) :BaseSqlFormatter(originalSql){}

	public:
		string ToString()
		{
			return "";
		}
	};

	class SqlFormatterUtil
	{
	public:
		static string GetFormatSql(string sql)
		{
			return "";
		}
	};
}

int main(int argc, char* argv [])
{
	std::string sql = "select * from tables";
	sql_formatter::SelectSqlFormatter formatter(sql);
	std::cout << formatter.ToString();
}