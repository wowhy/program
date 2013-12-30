#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

/* ตฺ5ีย */

static inline void MoveSingleTower(int n, char start, char finish)
{
	static char buffer[256];
	sprintf_s(buffer, "Move No.%d disk from %c to %c.\n", n, start, finish);
	cout << buffer;
}

void MoveTower(int n, char start, char finish, char temp)
{
	if (n == 1)
	{
		MoveSingleTower(n, start, finish);
		return;
	}

	MoveTower(n - 1, start, temp, finish);
	MoveSingleTower(n, start, finish);
	MoveTower(n - 1, temp, finish, start);
}


/* ตฺ6ีย */
typedef struct { int x, y; } pointT;
typedef enum { North, East, South, West } directionT;

vector<vector<char>> marze;

static inline void PointToIndex(pointT pt, int &i, int &j)
{
	i = marze.size() - pt.y - 1;
	j = pt.x;
}

static inline pointT IndexToPoint(int i, int j)
{
	return { j, marze.size() - i - 1 };
}

void ReadMazeMap(string filename)
{
	ifstream file(filename);
	if (file.fail())
		throw "can't open file.";
	string input;
	while (getline(file, input))
	{
		marze.push_back({ input.begin(), input.end() });
	}
}

pointT GetStartPosition()
{
	pointT pt;
	bool flag = false;
	for (int i = 0; i < marze.size(); ++i)
	{
		for (int j = 0; j < marze[i].size(); ++j)
		{
			if (marze[i][j] == 'S' || marze[i][j] == 's')
			{
				flag = true;
				pt = IndexToPoint(i, j);
				break;
			}
		}
	}

	if (!flag)
		throw "can't find start position";

	return pt;
}

bool OutsideMaze(pointT pt)
{
	//pointT tmp;
	//int i, j;
	//for (int dir = 0; dir < 4; ++dir)
	//{
	//	tmp = pt;
	//	switch ((directionT) dir)
	//	{
	//	case directionT::North:
	//		pt.y++;
	//		break;

	//	case directionT::East:
	//		pt.x++;
	//		break;

	//	case directionT::South:
	//		pt.y--;
	//		break;

	//	case directionT::West:
	//		pt.x--;
	//	}

	//	PointToIndex(pt, i, j);
	//	if (i < 0 || j < 0)
	//		return true;
	//	if (i == marze.size() ||
	//		j == marze[i].size())
	//		return true;
	//}

	//return false;

	int i, j;
	PointToIndex(pt, i, j);
	if (i < 0 || j < 0)
		return true;
	if (i >= marze.size() ||
		j >= marze[i].size())
		return true;

	return false;
}

static inline bool IsWallChar(char ch)
{
	return ch == '+' || ch == '-' || ch == '|';
}

bool WallExists(pointT pt, directionT dir)
{
	switch (dir)
	{
	case directionT::North:
		pt.y++;
		break;

	case directionT::East:
		pt.x++;
		break;

	case directionT::South:
		pt.y--;
		break;

	case directionT::West:
		pt.x--;
		break;
	}

	int i, j;
	PointToIndex(pt, i, j);
	if (i < 0 || j < 0)
		return false;
	if (i >= marze.size() ||
		j >= marze[i].size())
		return false;
	return IsWallChar(marze[i][j]);
}

void MarkSquare(pointT pt)
{
	int i, j;
	PointToIndex(pt, i, j);
	if (marze[i][j] == ' ')
		marze[i][j] = 'x';
}

void UnmarkSquare(pointT pt)
{
	int i, j;
	PointToIndex(pt, i, j);
	marze[i][j] = ' ';
}

bool IsMarked(pointT pt)
{
	int i, j;
	PointToIndex(pt, i, j);
	return marze[i][j] == 'x';
}

pointT AdjacentPoint(pointT pt, directionT dir)
{
	int x = pt.x;
	int y = pt.y;

	switch (dir)
	{
	case directionT::North:
		y++;
		break;

	case directionT::East:
		x++;
		break;

	case directionT::South:
		y--;
		break;

	case directionT::West:
		x--;
		break;
	}

	return { x, y };
}

bool SolveMarze(pointT pt)
{
	if (OutsideMaze(pt)) return true;
	if (IsMarked(pt)) return false;

	MarkSquare(pt);
	for (int i = 0; i < 4; i++)
	{
		if (!WallExists(pt, (directionT) i))
		{
			if (SolveMarze(AdjacentPoint(pt, (directionT) i)))
			{
				return true;
			}
		}
	}

	UnmarkSquare(pt);
	return false;
}

void PrintPoint(pointT pt)
{
	cout << "(" << pt.x << "," << pt.y << ")" << endl;
}

void PrintMarze()
{
	for (auto& v : marze)
	{
		cout << string(v.begin(), v.end()) << endl;
	}
}

int main(int argc, char* argv [])
{
	// MoveTower(8, 'a', 'c', 'b');

	ReadMazeMap("Program11.txt");
	if (SolveMarze(GetStartPosition()))
	{
		cout << "The marked squares show a solution path." << endl;
		PrintMarze();
	}
	else
	{
		cout << "No solution exists." << endl;
	}

	getchar();
}