#ifndef RAND_GEN_H_
#define RAND_GEN_H_

#include "Armies/Army.h"

struct Percentages {
	int percentES;
	int percentET;
	int percentEG;
	int percentAS;
	int percentAM;
	int percentAD;
};

struct ArmyData {
	int minPower, maxPower;
	int minHealth, maxHealth;
	int minCapacity, maxCapacity;
};


class Game;
class RandGen {
	ArmyData earthData;
	ArmyData alienData;
	Percentages percentages;
	int N, Prob;
	Game* game;

public:
	RandGen(Game* game);
	int generator(int begin, int end);
	Unit* generateEarthUnit(int timestep);
	Unit* generateAlienUnit(int timestep);
	void generateUnits(int timestep);
	void setData(ArmyData earthData, ArmyData alienData,Percentages percentages, int N, int Prob);
};

#endif
