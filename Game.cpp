#include "Game.h"

Game::Game()
{
	timestep = 0;
	earthArmy = new EarthArmy();
	alienArmy = new AlienArmy();
	RNG = new RandGen(earthArmy, alienArmy);
	this->earthArmy->setKilledList(&killedUnits);
	this->alienArmy->setKilledList(&killedUnits);
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

bool Game::addExistingEarthUnit(UNIT_TYPE type, Unit*& unit)
{
	return earthArmy->addUnit(type, unit);
}

bool Game::addExistingAlienUnit(UNIT_TYPE type, Unit*& unit)
{
	return alienArmy->addUnit(type, unit);
}

void Game::addToKilled(Unit*& unit)
{
	killedUnits.enqueue(unit);
}

void Game::loadInput()
{
	ifstream input_file;
	input_file.open("input.txt", ios::in);
	input_file >> randGenParams[0] >> randGenParams[1] >> randGenParams[2] >> randGenParams[3] >> randGenParams[4] >> randGenParams[5];
	for (int i = 6; i < 18; i += 2) {
		loadRange(input_file, randGenParams[i], randGenParams[i+1]);
	}
	input_file.close();
}

void Game::loadRange(ifstream& input_file, int& start, int& end)
{
	input_file >> start >> end;
	end = -1 * end;
}

