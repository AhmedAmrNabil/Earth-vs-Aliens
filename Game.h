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
	LinkedQueue <Unit*> UML;
public:
	Game();
	void printarmies();
	void printkilledunits();
	void printUML();
	bool getEarthUnit(UNIT_TYPE type, Unit*& unit);
	bool getAlienUnit(UNIT_TYPE type, Unit*& unit);
	bool getfromUML(Unit*& unit);
	void addToUML(Unit*& unit);
	bool addEarthUnit(Unit*& unit);
	bool addAlienUnit(Unit*& unit);
	void addToKilled(Unit*& unit);
	void handleUnit(Unit* unit);
	void loadInput();
	void gameTick();
	int getTimestep();
	void startGame();
	double getSoldierRatio();
	EarthArmy* getEarthArmy();
	AlienArmy* getAlienArmy();
	~Game();
	
};

#endif