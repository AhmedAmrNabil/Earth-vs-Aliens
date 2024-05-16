#include "RandGen.h"

#include "BattleUnits/AlienDrone.h"
#include "BattleUnits/AlienMonster.h"
#include "BattleUnits/AlienSoldier.h"
#include "BattleUnits/EarthGunnery.h"
#include "BattleUnits/EarthSoldier.h"
#include "BattleUnits/EarthTank.h"
#include "BattleUnits/HealUnit.h"
#include "BattleUnits/SaverUnit.h"
#include "Armies/EarthArmy.h"
#include "Armies/AlienArmy.h"
#include "Game.h"

RandGen::RandGen(Game* game) {
	earthData = { 0,0,0,0,0,0 };
	alienData = { 0,0,0,0,0,0 };
	allyData = { 0,0,0,0,0,0 };
	percentages = { 0,0,0,0,0,0,0,0 };
	N = 0;
	Prob = 0;

	srand(int(time(0)));
	this->game = game;
}

int RandGen::generator(int begin, int end) {
	int random = min(begin, end) + (rand() % (abs(end - begin) + 1));
	return random;
}

double RandGen::generateDouble(double begin, double end) {
	double random = begin + double(end - begin) * rand() / double(RAND_MAX);
	return random;
}

Unit* RandGen::generateEarthUnit() {
	// Returns nullptr if the ids exceeds 1000
	if (Unit::getEarthLastId() == 1000)return nullptr;
	Unit* unit;
	double power = generateDouble(earthData.minPower, earthData.maxPower);
	double health = generateDouble(earthData.minHealth, earthData.maxHealth);
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
	// Returns nullptr if the ids exceeds 3000
	if (Unit::getAlienLastId() == 3000)return nullptr;
	Unit* unit;
	double power = generateDouble(alienData.minPower, alienData.maxPower);
	double health = generateDouble(alienData.minHealth, alienData.maxHealth);
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

Unit* RandGen::generateAllyUnit() {
	// Returns nullptr if the ids exceeds 4000
	if (Unit::getSaverLastId() == 4000) return nullptr;
	Unit* unit;
	double power = generateDouble(allyData.minPower, allyData.maxPower);
	double health = generateDouble(allyData.minHealth, allyData.maxHealth);
	int capacity = generator(allyData.minCapacity, allyData.maxCapacity);
	unit = new SaverUnit(game, game->getTimestep(), health, power, capacity);
	return unit;

}

void RandGen::generateUnits() {
	EarthArmy* earthArmy = game->getEarthArmy();
	AlienArmy* alienArmy = game->getAlienArmy();
	AllyArmy* allyArmy = game->getAllyArmy();

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
	if (!game->saverIsActive())return;
	unit = nullptr;
	A = generator(1, 100);
	if (A <= Prob) {
		for (int i = 0; i < N; ++i) {
			unit = generateAllyUnit();
			allyArmy->addUnit(unit, true);
		}
	}
}

void RandGen::setData(ArmyData earthData, ArmyData alienData, ArmyData allyData , Percentages percentages, int N, int Prob) {
	this->earthData = earthData;
	this->alienData = alienData;
	this->allyData = allyData;
	this->percentages = percentages;
	this->N = N;
	this->Prob = Prob;
}