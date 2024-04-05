#ifndef GAME_H_
#define GAME_H_
#include <iostream>
#include <fstream>
#include "Armies/EarthArmy.h"
#include "Armies/AlienArmy.h"
#include "RandGen.h"

class Game
{
	EarthArmy* earthArmy;
	AlienArmy* alienArmy;
	RandGen* RNG;
	int timestep;
	int randGenParams[18];
	int N;
	int Prob;
	LinkedQueue <Unit*> killedUnits;
	//LinkedQueue <Unit*> tempUnits;
	int killedCount;
public:
	Game();
	void print();
	bool getEarthUnit(UNIT_TYPE type, Unit*& unit);
	bool getAlienUnit(UNIT_TYPE type, Unit*& unit1, Unit*& unit2);
	bool addEarthUnit(Unit*& unit);
	bool addAlienUnit(Unit*& unit);
	void addToKilled(Unit*& unit);
	/*void addToTemp(Unit*& unit);
	void clearTemp();*/
	void loadInput();
	void generateUnits();
	void gameTick();
	void testCode();
	double getSoldierRatio();
	
};

#endif