#ifndef GAME_H
#define GAME_H
#include "Armies/EarthArmy.h"
#include "Armies/AlienArmy.h"
#include "RandGen.h"

enum GAME_MODE {
	INTERACTIVE,
	SILENT
};

class Game
{
	EarthArmy earthArmy;
	AlienArmy alienArmy;
	RandGen RNG;
	int timestep;
	LinkedQueue <Unit*> killedUnits;
	priQueue <Unit*> UML;
	Percentages percentages;
	ArmyData earthData;
	ArmyData alienData;
	GAME_MODE gameMode;
	bool earthAttacked;
	bool alienAttacked;
	int infectionCount;
public:
	Game();
	void printarmies();
	void printkilledunits();
	void printUML();
	bool getEarthUnit(UNIT_TYPE type, Unit*& unit);
	bool getAlienUnit(UNIT_TYPE type, Unit*& unit);
	bool getfromUML(Unit*& unit);
	bool isUMLEmpty();
	void addToUML(Unit*& unit , int joinUMLtime);
	bool addEarthUnit(Unit*& unit);
	bool addAlienUnit(Unit*& unit);
	void addToKilled(Unit*& unit);
	void handleUnit(Unit* unit);
	void loadInput();
	void gameTick();
	int getTimestep();
	void startGame();
	bool isInteractive();
	string getRatio(double x, double y);
	void endGame();
	double getSoldierRatio();
	EarthArmy* getEarthArmy();
	AlienArmy* getAlienArmy();
	void incrementInfected();
	void decrementInfected();
	double getInfectionPercentage();
	bool isDraw();
	~Game();
	
};

#endif