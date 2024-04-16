#include "RandGen.h"

#include "BattleUnits/AlienDrone.h"
#include "BattleUnits/AlienMonster.h"
#include "BattleUnits/AlienSoldier.h"
#include "BattleUnits/EarthGunner.h"
#include "BattleUnits/EarthSoldier.h"
#include "BattleUnits/EarthTank.h"
#include "Armies/EarthArmy.h"
#include "Armies/AlienArmy.h"
#include "Game.h"

RandGen::RandGen(Game* game) {
	srand(time(0));
	this->game = game;
}

int RandGen::generator(int begin, int end) {
	int random = begin + (rand() % (end - begin + 1));
	return random;
}

Unit* RandGen::generateEarthUnit(int timestep) {
	Unit* unit;
	int power = generator(earthData.minPower, earthData.maxPower);
	int health = generator(earthData.minHealth, earthData.maxHealth);
	int capacity = generator(earthData.minCapacity, earthData.maxCapacity);
	int B = generator(1, 100);
	if (B <= percentages.percentES)
		unit = new EarthSoldier(timestep, health, power, capacity);
	else if (B <= percentages.percentES + percentages.percentET)
		unit = new EarthTank(timestep, health, power, capacity);
	else
		unit = new EarthGunner(timestep, health, power, capacity);

	return unit;
}

Unit* RandGen::generateAlienUnit(int timestep) {
	Unit* unit;
	int power = generator(alienData.minPower, alienData.maxPower);
	int health = generator(alienData.minHealth, alienData.maxHealth);
	int capacity = generator(alienData.minCapacity, alienData.maxCapacity);
	int B = generator(1, 100);
	if (B <= percentages.percentAS)
		unit = new AlienSoldier(timestep, health, power, capacity);
	else if (B <= percentages.percentAS + percentages.percentAM)
		unit = new AlienMonster(timestep, health, power, capacity);
	else
		unit = new AlienDrone(timestep, health, power, capacity);

	return unit;
}

void RandGen::generateUnits(int timestep) {
	EarthArmy* earthArmy = game->getEarthArmy();
	AlienArmy* alienArmy = game->getAlienArmy();

	int A = generator(1, 100);
	if (A >= Prob) {
		Unit* unit;
		for (int i = 0; i < N; ++i) {
			unit = generateEarthUnit(timestep);
			earthArmy->addUnit(unit, true); 
		}

	}

	A = generator(1, 100);
	if (A >= Prob) {
		Unit* unit;
		for (int i = 0; i < N; ++i) {
			unit = generateAlienUnit(timestep);
			alienArmy->addUnit(unit, true);
		}

	}
}

void RandGen::setData(ArmyData earthData, ArmyData alienData, Percentages percentages, int N, int Prob) {
	this->earthData = earthData;
	this->alienData = alienData;
	this->percentages = percentages;
	this->N = N;
	this->Prob = Prob;
}