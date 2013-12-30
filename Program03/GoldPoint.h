#ifndef GOLDPOINT_H
#define GOLDPOINT_H

#include <list>
#include <mutex>

using namespace std;

class GoldPoint
{
public:
	GoldPoint() :
		g(0.0),
		far(0.0),
		nFar(0.0),
		near(100.0),
		nNear(100.0)
	{
	}

public:
	void AddPoint(double n)
	{
		if (n > 0.0 && n < 100.0){
			lock_guard<mutex> lck(m);
			points.push_back(n);
			this->Compute();
		}
	}

	int GetScore(double n)
	{
		lock_guard<mutex> lck(m);
		if (n == nFar)
			return -2;

		if (n == nNear)
			return points.size();

		return 0;
	}

	double GetG()
	{
		lock_guard<mutex> lck(m);
		return g;
	}

	list<double> GetPoints()
	{
		lock_guard<mutex> lck(m);
		return points;
	}

private:
	void Compute()
	{
		this->G();
		for (auto i : points)
		{
			if (i - g > far){
				far = i - g;
				nFar = i;
			}

			if (abs(i - g) < near){
				near = abs(i - g);
				nNear = i;
			}
		}
	}

	void G()
	{
		double sum = 0.0;
		for (auto i : points)
		{
			sum += i;
		}

		g = sum / points.size() * 0.618;
	}

private:
	list<double> points;
	mutex m;
	double g;
	double far;
	double nFar;
	double near;
	double nNear;
};


#endif