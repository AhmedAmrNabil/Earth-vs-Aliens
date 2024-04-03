#include "randGen.h"

#include "BattleUnits/EarthSoldier.h"
#include "BattleUnits/AlienSoldier.h"
#include "BattleUnits/EarthGunner.h"
#include "BattleUnits/EarthTank.h"
#include "BattleUnits/AlienMonster.h"
#include "BattleUnits/AlienDrone.h"
#include "./Armies/Army.h"


RandGen::RandGen(Army* earthArmy, Army* alienArmy) {
	this->earthArmy = earthArmy;
	this->alienArmy = alienArmy;
	srand(time(0));
	lastAlienId = 2000;
	lastEarthId = 1;
}

int RandGen::generator(int begin, int end)
{
	int random = begin + (rand() % (end - begin));
	return random;
}

Unit* RandGen::generateEarthUnit(int timestep, UNIT_TYPE& type) {
	Unit* unit;
	int	power = earthMinPower + rand() % (earthMaxPower - earthMinPower);
	int	health = earthMinHealth + rand() % (earthMaxHealth - earthMinHealth);
	int capacity = earthMinCapacity + rand() % (earthMaxCapacity - earthMinCapacity);
	int B = (rand() % 100) + 1;
	if (B <= percentES) {
		type = ES;
		unit = new EarthSoldier(lastEarthId++, timestep, health, power, capacity);
	}
	else if (B <= percentES + percentET) {
		type = ET;
		unit = new EarthTank(lastEarthId++, timestep, health, power, capacity);
	}
	else {
		type = EG;
		unit = new EarthGunner(lastEarthId++, timestep, health, power, capacity);
	}

	return unit;

}

Unit* RandGen::generateAlienUnit(int timestep, UNIT_TYPE& type) {
	Unit* unit;
	int	power = alienMinPower + rand() % (alienMaxPower - alienMinPower);
	int	health = alienMinHealth + rand() % (alienMaxHealth - alienMinHealth);
	int capacity = alienMinCapacity + rand() % (alienMaxCapacity - alienMinCapacity);
	int B = (rand() % 100) + 1;
	if (B <= percentES) {
		type = AS;
		unit = new AlienSoldier(lastAlienId++, timestep, health, power, capacity);
	}
	else if (B <= percentES + percentET) {
		type = AM;
		unit = new AlienMonster(lastAlienId++, timestep, health, power, capacity);
	}
	else {
		type = AD;
		unit = new AlienDrone(lastAlienId++, timestep, health, power, capacity);
	}
	return unit;

}

void RandGen::initParams(int randGenparams[])
{
	percentES = randGenparams[0];
	percentET = randGenparams[1];

	percentAS = randGenparams[3];
	percentAM = randGenparams[4];

	earthMinPower = randGenparams[6];
	earthMaxPower = randGenparams[7];
	earthMinHealth = randGenparams[8];
	earthMaxHealth = randGenparams[9];
	earthMinCapacity = randGenparams[10];
	earthMaxCapacity = randGenparams[11];
	alienMinPower = randGenparams[12];
	alienMaxPower = randGenparams[13];
	alienMinHealth = randGenparams[14];
	alienMaxHealth = randGenparams[15];
	alienMinCapacity = randGenparams[16];
	alienMaxCapacity = randGenparams[17];
}
