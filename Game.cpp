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
	testCode();
	print();
	++timestep;
	//earthArmy->fight(game);
	//alienArmy->fight(game);

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
void Game::testCode() {
	cout << "\ncurrent timestep: " << timestep;
	int X = RNG.generator(1, 100);
	cout << ", X: " << X << endl;
	if (X > 0 && X < 10) {
		Unit* S1;
		if (getEarthUnit(ES, S1)) {
			addEarthUnit(S1);
			cout << "An Earth Soldier was Picked and inserted back to the original list\n";
		} else {
			cout << "No Earth Soldiers found for Picking\n";
		}
	}
	else if (X < 20) {
		Unit* ET1;
		if (getEarthUnit(ET, ET1)) {
			addToKilled(ET1);
			cout << "An Earth Tank was Picked and added to the killed list\n";
		} else {
			cout << "No Earth Tank found for Picking\n";
		}
	}
	else if (X < 30) {
		Unit* EG1;
		if (getEarthUnit(EG, EG1)) {
			EG1->decrementHealth(EG1->getHealth() / 2, timestep);
			addEarthUnit(EG1);
			cout << "An Earth Gunnery was Picked, decremented half its health and inserted back to the original list\n";
		} else {
			cout << "No Earth Gunnery found for Picking\n";
		}
	}
	else if (X < 40) {
		Unit* AS1;
		LinkedQueue<Unit*> temp;
		for (int i = 0; i < 5; i++) {
			if (getAlienUnit(AS, AS1)) {
				AS1->decrementHealth(AS1->getHealth() / 2, timestep); //assuming it's decremented by half as well
				temp.enqueue(AS1);
			} else {
				break;
			}
		}
		cout << temp.getCount() <<" Alien Soldiers were Picked, decremented half their health, added to a temp list then inserted back to the original list\n";
		while (!temp.isEmpty()) {
			Unit* value;
			temp.dequeue(value);
			addAlienUnit(value);
		}
	}
	else if (X < 50) {
		Unit* AM1;
		int count = 0;
		for (int i = 0; i < 5; i++) {
			if (getAlienUnit(AM, AM1)) {
				count++;
				addAlienUnit(AM1);
			} else {
				break;
			}
		}
		cout << count <<" Alien Monsters were Picked and inserted back to the original list\n";
	}
	else if (X < 60) {
		Unit* AD1;
		int count = 0;
		for (int i = 0; i < 6; i++) {
			if (getAlienUnit(AD, AD1)) {
				addToKilled(AD1);
				count++;
			} else {
				break;
			}
		}
		cout << count <<" Alien Drones were Picked from front and rear of their list and added to the Killed list\n";
	}
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
	while (ch != 27 && timestep <= 50) { // timestep condition for test code.
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