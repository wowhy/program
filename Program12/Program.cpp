#include <iostream>
#include <string>
#include <libpq-fe.h>
#include <WinSock2.h>
#include <functional>

#pragma comment(lib, "libpq.lib")
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

class Uncopyable
{
public:
	Uncopyable(){}
	~Uncopyable(){}

private:
	Uncopyable(const Uncopyable& obj){}
	Uncopyable& operator=(const Uncopyable& obj){ return *this; }
};

class CPGconn : public Uncopyable
{
public:
	CPGconn(string connectionString) :conn(PQconnectdb(connectionString.c_str()))
	{
	}

	~CPGconn()
	{
		if (conn != nullptr)
			PQfinish(conn);
	}

	PGconn* GetConnection() const { return conn; }

	ConnStatusType GetStatus() const
	{
		return PQstatus(conn);
	}

	string GetErrorMessage() const { return PQerrorMessage(conn); }

private:
	PGconn *conn;
};

class CPGresult : public Uncopyable
{
public:
	CPGresult(PGresult* res) :res(res)
	{
	}

	~CPGresult()
	{
		if (res != nullptr)
			PQclear(res);
	}

public:
	PGresult* GetResult() { return res; }
	void SetResult(PGresult *res){ this->res = res; }

	int GetTuples()
	{
		return ::PQnfields(res);
	}

	char* GetValue(int tup_num, int field_num)
	{
		return PQgetvalue(res, tup_num, field_num);
	}

	ExecStatusType GetStatus()
	{
		return PQresultStatus(res);
	}

private:
	PGresult *res;
};

class ScopeGuard
{
public:
	explicit ScopeGuard(function<void()> dispose) :_dismissed(false), _dispose(dispose){}
	~ScopeGuard()
	{
		if (!_dismissed)
			_dispose();
	}

	void Dismiss()
	{
		_dismissed = true;
	}

private:
	bool _dismissed;
	function<void()> _dispose;
};

#define SCOPEGUARD_LINENAME_CAT(name, line) name##line
#define SCOPEGUARD_LINENAME(name, line) SCOPEGUARD_LINENAME_CAT(name, line)
#define ON_SCOPE_EXIT(callback) ScopeGuard SCOPEGUARD_LINENAME(EXIT_, __LINE__)(callback)

int main(int argc, char* argv [])
{
	if (argc != 3)
		return 0;

	WSADATA wsaData;
	WSAStartup(WINSOCK_VERSION, &wsaData);
	ON_SCOPE_EXIT([]{ WSACleanup(); });

	string connectionString = "host=localhost port=5432 user=postgres password=hongyuan dbname=sites";
	string cmd = "select id, lastlogintime from sys_user where state = 1 and loginname=$1 and password=md5(loginname||$2||salt) limit 1;";
	CPGconn conn(connectionString);

	try
	{
		if (conn.GetStatus() != CONNECTION_OK)
			throw EXIT_FAILURE;
		
		char *paramValues[2] = { argv[1], argv[2] };
		CPGresult res(PQexecParams(
			conn.GetConnection(),
			cmd.c_str(),
			2,
			nullptr,
			paramValues,
			nullptr,
			nullptr,
			0));

		if (res.GetStatus() != ExecStatusType::PGRES_TUPLES_OK)
			throw EXIT_FAILURE;

		if (res.GetTuples() == 0)
		{
			cout << "用户名或密码错误." << endl;
		}
		else
		{
			cout << "登录成功." << endl;
			cout << "id: " << atoi(res.GetValue(0, 0)) << endl
				<< "lastlogintime: " << res.GetValue(0, 1) << endl;
		}
	}
	catch (int /*error*/)
	{
		cout << conn.GetErrorMessage();
	}

	return EXIT_SUCCESS;
}