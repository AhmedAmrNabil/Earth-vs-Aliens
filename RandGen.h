#ifndef RAND_GEN_H
#define RAND_GEN_H

// Structure to store the generation percentage for each unit type
struct Percentages {
	int percentES;
	int percentET;
	int percentEG;
	int percentHU;
	int percentAS;
	int percentAM;
	int percentAD;
	int percentIf; // Stores the infection percentage of the alien Monster
};

// Stores each unit charateristics
struct ArmyData {
	int minPower, maxPower;
	int minHealth, maxHealth;
	int minCapacity, maxCapacity;
};


class Game;
class Unit;
class RandGen {
	ArmyData earthData;
	ArmyData alienData;
	ArmyData allyData;
	Percentages percentages;
	int N, Prob;
	Game* game;

public:
	RandGen(Game* game);

	// setter for the different army parameters
	void setData(ArmyData earthData, ArmyData alienData, ArmyData allyData,Percentages percentages, int N, int Prob);
	
	// Generic generator given the range
	int generator(int begin, int end); 

	// Generic generator given the range returns double
	double generateDouble(double begin, double end); 
	
	//Units generation
	void generateUnits(); // Wrapper to generate all units and add them to their armies
	Unit* generateEarthUnit(); // generate a single earth unit
	Unit* generateAlienUnit(); // generate a single alien unit
	Unit* generateAllyUnit();  // generate a single saver unit
};

#endif
