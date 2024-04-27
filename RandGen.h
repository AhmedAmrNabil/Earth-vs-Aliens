#ifndef RAND_GEN_H
#define RAND_GEN_H


struct Percentages {
	int percentES;
	int percentET;
	int percentEG;
	int percentHU;
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
class Unit;
class RandGen {
	ArmyData earthData;
	ArmyData alienData;
	Percentages percentages;
	int N, Prob;
	Game* game;

public:
	RandGen(Game* game);
	int generator(int begin, int end);
	double generateDouble(double begin, double end);
	Unit* generateEarthUnit();
	Unit* generateAlienUnit();
	void generateUnits();
	void setData(ArmyData earthData, ArmyData alienData,Percentages percentages, int N, int Prob);
};

#endif
