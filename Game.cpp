#include "Game.h"
#include <conio.h>

Game::Game():RNG(this)
{
	timestep = 1;
	loadInput();
}

void Game::print()
{
	earthArmy.print();
	alienArmy.print();
	cout << "============== Killed/Destructed Units =============\n";
	cout << killedUnits.getCount() << "    units ";
	killedUnits.print();
	cout << endl;
}

bool Game::getEarthUnit(UNIT_TYPE type, Unit*& unit)
{
	return earthArmy.getUnit(type, unit);
}

bool Game::getAlienUnit(UNIT_TYPE type, Unit*& unit)
{
	return alienArmy.getUnit(type, unit);
}

bool Game::addEarthUnit(Unit*& unit)
{
	return earthArmy.addUnit(unit);
}

bool Game::addAlienUnit(Unit*& unit)
{
	return alienArmy.addUnit(unit);
}

void Game::gameTick() {
	RNG.generateUnits();
	print();
	++timestep;
	earthArmy.fight();
	alienArmy.fight();
}

void Game::addToKilled(Unit*& unit)
{
	killedUnits.enqueue(unit);
}

void Game::loadInput()
{
	int N, Prob;
	Percentages percentages;
	ArmyData earthData;
	ArmyData alienData;
	ifstream input_file;
	input_file.open("input.txt", ios::in);
	input_file >> N;

	input_file >> percentages.percentES >> percentages.percentET >> percentages.percentEG;
	input_file >> percentages.percentAS >> percentages.percentAM >> percentages.percentAD;
	
	input_file >> Prob;
	input_file >> earthData.minPower >> earthData.maxPower;
	input_file >> earthData.minHealth >> earthData.maxHealth;
	input_file >> earthData.minCapacity >> earthData.maxCapacity;

	earthData.maxPower *= -1;
	earthData.maxHealth *= -1;
	earthData.maxCapacity *= -1;

	input_file >> alienData.minPower >> alienData.maxPower;
	input_file >> alienData.minHealth >> alienData.maxHealth;
	input_file >> alienData.minCapacity >> alienData.maxCapacity;

	alienData.maxPower *= -1;
	alienData.maxHealth *= -1;
	alienData.maxCapacity *= -1;

	RNG.setData(earthData, alienData,percentages, N, Prob);

	input_file.close();
}

EarthArmy* Game::getEarthArmy() {
	return &earthArmy;
}
AlienArmy* Game::getAlienArmy() {
	return &alienArmy;
}

double Game::getSoldierRatio()
{
	return (double(earthArmy.getSoldierCount()) / (alienArmy.getSoldierCount())) * 100;
}

int Game::getTimestep()
{
	return timestep;
}

void Game::startGame() {
	char ch = 0;
	while (ch != 27) { // timestep condition for test code.
		gameTick();
		ch = _getch();
	}
}


Game::~Game() {
	Unit* unit;
	while (killedUnits.dequeue(unit)) 
	{
		if (unit != nullptr)
			delete unit;
	}
}