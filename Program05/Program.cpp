#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

const string ENV[24] = {
	"COMSPEC", "DOCUMENT_ROOT", "GATEWAY_INTERFACE",
	"HTTP_ACCEPT", "HTTP_ACCEPT_ENCODING",
	"HTTP_ACCEPT_LANGUAGE", "HTTP_CONNECTION",
	"HTTP_HOST", "HTTP_USER_AGENT", "PATH",
	"QUERY_STRING", "REMOTE_ADDR", "REMOTE_PORT",
	"REQUEST_METHOD", "REQUEST_URI", "SCRIPT_FILENAME",
	"SCRIPT_NAME", "SERVER_ADDR", "SERVER_ADMIN",
	"SERVER_NAME", "SERVER_PORT", "SERVER_PROTOCOL",
	"SERVER_SIGNATURE", "SERVER_SOFTWARE" };

int main(int argc, char* argv [])
{
	cout << "Content-type:text/html\r\n\r\n";
	cout << "<html>" << endl;
	cout << "<head>" << endl;
	cout << "<title>Index</title>" << endl;
	cout << "</head>" << endl;
	cout << "<body>" << endl;
	cout << "<h1>Hello, World!</h1>" << endl;


	cout << "<table border = \"0\" cellspacing = \"2\">";
	for (int i = 0; i < 24; i++)
	{
		cout << "<tr><td>" << ENV[i] << "</td><td>";
		char buffer[1024];
		size_t len;
		if (getenv_s(&len, buffer, ENV[i].c_str()) == 0){
			cout << buffer;
		}
		else{
			cout << "Environment variable does not exist.";
		}

		cout << "</td></tr>\n";
	}

	cout << "</table>\n";
	cout << "</body>" << endl;
	cout << "</html>" << endl;

	return 0;
}