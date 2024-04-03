#include "Game.h"

Game::Game()
{
	timestep = 0;
	killedCount = 0;
	earthArmy = new EarthArmy();
	alienArmy = new AlienArmy();
	RNG = new RandGen();
	loadInput();
	RNG->initParams(randGenParams);
}

void Game::print()
{
	earthArmy->print();
	alienArmy->print();
	cout << "============== Killed/Destructed Units =============\n";
	cout << killedCount << "    units ";
	killedUnits.print();
	cout << endl;
}

bool Game::getEarthUnit(UNIT_TYPE type, Unit*& unit)
{
	Unit* tmp;
	return earthArmy->getUnit(type, unit, tmp);
}

bool Game::getAlienUnit(UNIT_TYPE type, Unit*& unit1, Unit*& unit2)
{
	return alienArmy->getUnit(type, unit1, unit2);
}

void Game::generateUnits() {
	int A = RNG->generator(1, 100);
	if (A >= Prob) {
		UNIT_TYPE type;
		Unit* unit;
		for (int i = 0; i < N; ++i) {
			unit = RNG->generateEarthUnit(timestep, type);
			earthArmy->addUnit(unit);
		}

	}

	A = RNG->generator(1, 100);
	if (A >= Prob) {
		UNIT_TYPE type;
		Unit* unit;
		for (int i = 0; i < N; ++i) {
			unit = RNG->generateAlienUnit(timestep, type);
			alienArmy->addUnit(unit);
		}

	}
}
void Game::gameTick() {
	generateUnits();
	testCode();
	print();
	//earthArmy->fight(game);
	//alienArmy->fight(game);

}

void Game::addToKilled(Unit*& unit)
{
	if (unit->getType() > 2)
		alienArmy->decrementCount(unit);
	else
		earthArmy->decrementCount(unit);
	killedUnits.enqueue(unit);
	killedCount++;
}

void Game::addToTemp(Unit*& unit)
{
	tempUnits.enqueue(unit);
}

void Game::clearTemp() {
	Unit* tmp;
	while (tempUnits.dequeue(tmp)) {
		if (tmp->getType() > 2)
			alienArmy->addUnit(tmp);
		else
			earthArmy->addUnit(tmp);
	}
}

void Game::loadInput()
{
	ifstream input_file;
	input_file.open("input.txt", ios::in);
	input_file >> N;

	for (int i = 0; i < 6; ++i) {
		input_file >> randGenParams[i];
	}

	input_file >> Prob;

	for (int i = 0; i < 6; ++i) {
		input_file >> randGenParams[2 * i + 6] >> randGenParams[2 * i + 7];
		randGenParams[2 * i + 7] *= -1;
	}

	input_file.close();
}

void Game::testCode() {
	cout << "\ncurrent timestep: " << timestep;
	int X = RNG->generator(1, 101);
	cout << ", X: " << X << endl;
	if (X > 0 && X < 10) {
		Unit* S1;
		Unit* S2 = nullptr;
		if (earthArmy->getUnit(ES, S1, S2))
			earthArmy->addUnit(S1);
	}
	else if (X < 20) {
		Unit* ET1;
		Unit* ET2 = nullptr;
		if (earthArmy->getUnit(ET, ET1, ET2))
			addToKilled(ET1);
	}
	else if (X < 30) {
		Unit* EG1;
		Unit* EG2 = nullptr;
		if (earthArmy->getUnit(EG, EG1, EG2)) {
			EG1->decrementHealth(EG1->getHealth() / 2, timestep);
			earthArmy->addUnit(EG1);
		}
	}
	else if (X < 40) {
		Unit* AS1[6];
		AS1[5] = 0;
		for (int i = 0; i < 4; i++) {
			if (alienArmy->getUnit(AS, AS1[i], AS1[5]))
				addToTemp(AS1[i]);
		}
		clearTemp();
	}
	else if (X < 50) {
		Unit* AM1;
		Unit* AM2 = nullptr;
		for (int i = 0; i < 5; i++) {
			if (alienArmy->getUnit(AM, AM1, AM2))
				alienArmy->addUnit(AM1);
		}
	}
	else if (X < 60) {
		Unit* AD1;
		Unit* AD2 = nullptr;
		for (int i = 0; i < 3; i++) {
			if (alienArmy->getUnit(AD, AD1, AD2)) {
				addToKilled(AD1);
				if (AD2)
					addToKilled(AD2);
			}
		}
	}
	++timestep;
}

double Game::getSoldierRatio()
{
	return ((earthArmy->getSoldierCount()) / (alienArmy->getSoldierCount())) * 100;
}


