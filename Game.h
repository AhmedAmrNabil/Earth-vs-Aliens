#ifndef GAME_H
#define GAME_H
#include "Armies/EarthArmy.h"
#include "Armies/AllyArmy.h"
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
	AllyArmy allyArmy;
	RandGen RNG;
	int timestep;
	LinkedQueue <Unit*> killedUnits;
	priQueue <Unit*> UML;
	Percentages percentages;
	ArmyData earthData;
	ArmyData alienData;
	ArmyData allyData;
	GAME_MODE gameMode;
	bool earthAttacked;
	bool alienAttacked;
	int infectionCount;
	int umlsoldier;
	bool saverActive;
	int infectionThreshold;
	int totalInfectionCount;
	string attackedIDs;
public:

	//Initialisations and file loading
	Game();
	void loadInput();

	// Printing in Interactive Mode
	void printarmies();
	void printkilledunits();
	void printUML();
	bool isInteractive();
	void addToAttacked(string ids);



	//Getters and setters for army units
	bool getEarthUnit(UNIT_TYPE type, Unit*& unit);
	bool getAlienUnit(UNIT_TYPE type, Unit*& unit);
	bool getSaverUnit(Unit*& unit);
	bool addEarthUnit(Unit*& unit);
	bool addAlienUnit(Unit*& unit);
	bool addSaverUnit(Unit*& unit);

	//UML Functions
	bool getfromUML(Unit*& unit);
	void addToUML(Unit*& unit , int joinUMLtime);
	bool isUMLEmpty();


	//Game Functions
	void startGame();
	void gameTick();
	void endGame();

	// Getters for Each army
	EarthArmy* getEarthArmy();
	AllyArmy* getAllyArmy();
	AlienArmy* getAlienArmy();

	//Infected soldiers functions
	void incrementInfected();
	void decrementInfected();
	int getAliveSoldiers();
	double getInfectionPercentage();
	bool spreadInfect(Unit*& unit);

	//Output File helper functions
	bool isDraw();
	string getRatio(double x, double y);

	//Ally Army helper functions
	bool saverIsActive();
	void killAllSaver();

	//Getters
	int getTimestep();
	double getSoldierRatio();

	
	void handleUnit(Unit* unit); // Kill unit or add to maitnence list
	void addToKilled(Unit*& unit); // add unit to the killed list
	
	//Destructing units in the killed list
	~Game();
};

#endif