#include "GoldPoint.h"
#include <thread>
#include <Windows.h>

GoldPoint game;

int main()
{
	thread t1([]{
		game.AddPoint(65);
		game.AddPoint(74);
		game.AddPoint(99.999);
	});

	thread t2([]{
		game.AddPoint(20);
		game.AddPoint(31.618);
	});
	t1.join();
	t2.join();

	printf("G = %f\n", game.GetG());
	for (auto i : game.GetPoints())
	{
		printf("%f = %d\n", i, game.GetScore(i));
	}


	
	return 0;
}