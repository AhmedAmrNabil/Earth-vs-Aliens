#ifndef RAND_GEN_H_
#define RAND_GEN_H_
#include <time.h>

#include <cstdlib>
#include <fstream>

#include "Armies/Army.h"

class EarthSoldier; 
class RandGen {
	int N;
	int percentES;
	int percentET;
	int percentAS;
	int percentAM;
	int Thr;
	int earthMinPower, earthMaxPower;
	int earthMinHealth, earthMaxHealth;
	int earthMinCapacity, earthMaxCapacity;
	int alienMinPower, alienMaxPower;
	int alienMinHealth, alienMaxHealth;
	int alienMinCapacity, alienMaxCapacity;
	Army* earthArmy;
	Army* alienArmy;
	int lastEarthId;
	int lastAlienId;

public:
	RandGen();
	int generator(int begin, int end);
	Unit* generateEarthUnit(int timestep, UNIT_TYPE& type);
	Unit* generateAlienUnit(int timestep, UNIT_TYPE& type);
	void initParams(int randGenparams[]);
};

#endif
