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
}

int RandGen::generator(int begin, int end)
{
	int random = begin + (rand() % (end - begin));
	return random;
}

void RandGen::generate(int timestep) {
	int power, health, capacity;
	int A = (rand() % 100) + 1;
	if (A >= Thr) {
		Unit* unit;
		UNIT_TYPE type;

		for (int i = 0; i < N; ++i) {
			power = earthMinPower + rand() % (earthMaxPower - earthMinPower);
			health = earthMinHealth + rand() % (earthMaxHealth - earthMinHealth);
			capacity = earthMinCapacity + rand() % (earthMaxCapacity - earthMinCapacity);
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
				unit = new EarthGunner(lastEarthId++,timestep, health, power, capacity);
			}

			earthArmy->addUnit(type,unit);
		}
	}

	A = (rand() % 100) + 1;
	if (A >= Thr) {
		Unit* unit;
		UNIT_TYPE type;
		for (int i = 0; i < N; ++i) {
			power = alienMinPower + rand() % (alienMaxPower - alienMinPower);
			health = alienMinHealth + rand() % (alienMaxHealth - alienMinHealth);
			capacity = alienMinCapacity + rand() % (alienMaxCapacity - alienMinCapacity);
			int B = (rand() % 100) + 1;
			if (B <= percentAS) { 
				type = AS;
				unit = new AlienSoldier(lastEarthId++, timestep, health, power, capacity);
			}
			else if (B <= percentAS + percentAM) {
				unit = new AlienMonster(lastEarthId++, timestep, health, power, capacity);
				type = AM;
			}
			else {
				unit = new AlienDrone(lastEarthId++, timestep, health, power, capacity);
				type = AD;
			}

			alienArmy->addUnit(type,unit);
		}
	}

}

void RandGen::initParams(int randGenparams[])
{
	N = randGenparams[0];
	percentES = randGenparams[1];
	percentET =randGenparams[2];
	percentAS = randGenparams[3];
	percentAM = randGenparams[4];
	Thr = randGenparams[5];
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
