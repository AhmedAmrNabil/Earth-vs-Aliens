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
	//Army objects
	EarthArmy earthArmy;
	AlienArmy alienArmy;
	AllyArmy allyArmy;
	RandGen RNG;

	// Parameters loaded from the input file
	Percentages percentages;
	ArmyData earthData;
	ArmyData alienData;
	ArmyData allyData;

	LinkedQueue <Unit*> killedUnits;
	priQueue <Unit*> UML;
	GAME_MODE gameMode;

	//Check if any army has attacked
	bool earthAttacked;
	bool alienAttacked;

	bool saverActive;
	int timestep;
	int umlsoldier;

	int healCount;
	int infectionThreshold;
	int infectionCount;
	int totalInfectionCount;

	// String to print ids of attacked units
	string attackedIDs;
public:

	// Initialisations and file loading
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
	void incrementHealCount();

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
	void spreadInfect();

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