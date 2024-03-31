#pragma once
#include <cstdlib> 
#include <time.h> 

class RandGen
{
public:
	RandGen()
	{
	
	}
	int generator(int beg, int end) 
	{
		srand(time(0));
		int random = beg + (rand() % (end-beg));
		return random;
	}
};

