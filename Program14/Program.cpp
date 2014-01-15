#include <iostream>
#include <string>
#include <functional>

#include "ch01.h"
#include "ch02.h"

using namespace std;

#define ADD_APP(x) AppMain_##x

#define RUN(x) return apps[x - 1]()

function<int(void)> apps[] = 
{
	ADD_APP(1)
	, ADD_APP(2)
};



int main(int argc, char* argv[])
{
	RUN(2);
}