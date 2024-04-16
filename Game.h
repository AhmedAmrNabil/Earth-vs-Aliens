#ifndef GAME_H_
#define GAME_H_
#include <iostream>
#include <fstream>
#include "Armies/EarthArmy.h"
#include "Armies/AlienArmy.h"
#include "RandGen.h"

class Game
{
	EarthArmy earthArmy;
	AlienArmy alienArmy;
	RandGen RNG;
	int timestep;
	int randGenParams[20];
	int N;
	int Prob;
	LinkedQueue <Unit*> killedUnits;
	int killedCount;
public:
	Game();
	void print();
	bool getEarthUnit(UNIT_TYPE type, Unit*& unit);
	bool getAlienUnit(UNIT_TYPE type, Unit*& unit1, bool rear = false);
	bool addEarthUnit(Unit*& unit);
	bool addAlienUnit(Unit*& unit);
	void addToKilled(Unit*& unit);
	void loadInput();
	void gameTick();
	void testCode();
	double getSoldierRatio();
	EarthArmy* getEarthArmy();
	AlienArmy* getAlienArmy();
	~Game();
	
};

#endif