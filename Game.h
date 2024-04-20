#ifndef GAME_H
#define GAME_H
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
	LinkedQueue <Unit*> killedUnits;
public:
	Game();
	void print();
	bool getEarthUnit(UNIT_TYPE type, Unit*& unit);
	bool getAlienUnit(UNIT_TYPE type, Unit*& unit);
	bool addEarthUnit(Unit*& unit);
	bool addAlienUnit(Unit*& unit);
	void addToKilled(Unit*& unit);
	void loadInput();
	void gameTick();
	void testCode();
	int getTimestep();
	void startGame();
	double getSoldierRatio();
	EarthArmy* getEarthArmy();
	AlienArmy* getAlienArmy();
	~Game();
	
};

#endif