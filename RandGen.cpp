#include "RandGen.h"

#include "BattleUnits/AlienDrone.h"
#include "BattleUnits/AlienMonster.h"
#include "BattleUnits/AlienSoldier.h"
#include "BattleUnits/EarthGunnery.h"
#include "BattleUnits/EarthSoldier.h"
#include "BattleUnits/HealUnit.h"
#include "BattleUnits/EarthTank.h"
#include "Armies/EarthArmy.h"
#include "Armies/AlienArmy.h"
#include "Game.h"

RandGen::RandGen(Game* game) {
	srand(time(0));
	this->game = game;
}

int RandGen::generator(int begin, int end) {
	int random = min(begin, end) + (rand() % (abs(end - begin) + 1));
	return random;
}

double generateDouble(double begin, double end) {
	double random = begin + (end - begin) * rand() / double(RAND_MAX);
	return random;
}

Unit* RandGen::generateEarthUnit() {
	Unit* unit;
	double power = generator(earthData.minPower, earthData.maxPower);
	double health = generator(earthData.minHealth, earthData.maxHealth);
	int capacity = generator(earthData.minCapacity, earthData.maxCapacity);
	int B = generator(1, 100);
	if (B <= percentages.percentES)
		unit = new EarthSoldier(game, game->getTimestep(), health, power, capacity);
	else if (B <= percentages.percentES + percentages.percentET)
		unit = new EarthTank(game, game->getTimestep(), health, power, capacity);
	else if (B <= percentages.percentES + percentages.percentET + percentages.percentEG)
		unit = new EarthGunnery(game, game->getTimestep(), health, power, capacity);
	else
		unit = new HealUnit(game, game->getTimestep(), health, power, capacity);

	return unit;
}

Unit* RandGen::generateAlienUnit() {
	Unit* unit;
	double power = generator(alienData.minPower, alienData.maxPower);
	double health = generator(alienData.minHealth, alienData.maxHealth);
	int capacity = generator(alienData.minCapacity, alienData.maxCapacity);
	int B = generator(1, 100);
	if (B <= percentages.percentAS)
		unit = new AlienSoldier(game, game->getTimestep(), health, power, capacity);
	else if (B <= percentages.percentAS + percentages.percentAM)
		unit = new AlienMonster(game, game->getTimestep(), health, power, capacity,percentages.percentIf);
	else
		unit = new AlienDrone(game, game->getTimestep(), health, power, capacity);

	return unit;
}

void RandGen::generateUnits() {
	EarthArmy* earthArmy = game->getEarthArmy();
	AlienArmy* alienArmy = game->getAlienArmy();
	Unit* unit = nullptr;

	int A = generator(1, 100);
	if (A <= Prob) {
		for (int i = 0; i < N; ++i) {
			unit = generateEarthUnit();
			earthArmy->addUnit(unit, true);
		}
	}
	unit = nullptr;
	A = generator(1, 100);
	if (A <= Prob) {
		for (int i = 0; i < N; ++i) {
			unit = generateAlienUnit();
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