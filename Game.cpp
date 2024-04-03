#include "Game.h"

Game::Game()
{
	timestep = 0;
	earthArmy = new EarthArmy();
	alienArmy = new AlienArmy();
	RNG = new RandGen(earthArmy, alienArmy);
	this->earthArmy->setKilledList(&killedUnits);
	this->alienArmy->setKilledList(&killedUnits);
	loadInput();
	RNG->initParams(randGenParams);
}

void Game::print()
{
	earthArmy->print();
	alienArmy->print();
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

bool Game::addEarthUnit(UNIT_TYPE type, Unit*& unit)
{
	return earthArmy->addUnit(type, unit);
}

bool Game::addAlienUnit(UNIT_TYPE type, Unit*& unit)
{
	return alienArmy->addUnit(type, unit);
}


void Game::generateUnits() {
	int A = RNG->generator(1, 100);
	if (A >= Prob) {
		UNIT_TYPE type;
		Unit* unit;
		for (int i = 0; i < N; ++i) {
			unit = RNG->generateEarthUnit(timestep, type);
			earthArmy->addUnit(type, unit);
		}

	}

	A = RNG->generator(1, 100);
	if (A >= Prob) {
		UNIT_TYPE type;
		Unit* unit;
		for (int i = 0; i < N; ++i) {
			unit = RNG->generateAlienUnit(timestep, type);
			alienArmy->addUnit(type, unit);
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
	killedUnits.enqueue(unit);
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
	/*cout << "\ncurrent timestep: " << timestep;
	int X = RNG->generator(1, 101);
	cout << ", X: " << X << endl;
	if (X > 0 && X < 10) {
		Unit* S1;
		Unit* S2 = nullptr;
		earthArmy->getUnit(ES, S1, S2);
		earthArmy->addUnit(ES, S1);
	}
	else if (X > 10 && X < 20) {
		Unit* ET1;
		Unit* ET2 = nullptr;
		earthArmy->getUnit(ET, ET1, ET2);
		earthArmy->addToKilled(ET1);
	}
	else if (X > 20 && X < 30) {
		Unit* EG1;
		Unit* EG2 = nullptr;
		earthArmy->getUnit(EG, EG1, EG2);
		earthArmy->addToKilled(EG1);
	}
	else if (X > 30 && X < 40) {
		Unit* AS1;
		Unit* AS2;
		Unit* AS3;
		Unit* AS4 = nullptr;

		alienArmy->getUnit(AS, AS1, AS4);
		alienArmy->getUnit(AS, AS2, AS4);
		alienArmy->getUnit(AS, AS3, AS4);
	}
	else if (X > 40 && X < 50) {
		Unit* AM1;
		Unit* AM2;
		Unit* AM3;
		Unit* AM4 = nullptr;

		alienArmy->getUnit(AM, AM1, AM4);
		alienArmy->getUnit(AM, AM2, AM4);
		alienArmy->getUnit(AM, AM3, AM4);
		alienArmy->addUnit(AM, AM1);
		alienArmy->addUnit(AM, AM2);
		alienArmy->addUnit(AM, AM3);
	}
	else if (X > 50 && X < 60) {
		Unit* AD1;
		Unit* AD2;

		alienArmy->getUnit(AD, AD1, AD1);
		alienArmy->getUnit(AD, AD2, AD2);
		alienArmy->addToKilled(AD1);
		alienArmy->addToKilled(AD2);
	}
	++timestep;*/
}


