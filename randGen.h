#pragma once
#include <cstdlib> 
#include <time.h> 

class RandGen
{
public:
	RandGen()
	{

	}
	int generator(int begin, int end)
	{
		srand(time(0));
		int random = begin + (rand() % (end - begin));
		return random;
	}
};

