#include "Game.h"

Game::Game():RNG(this)
{
	timestep = 0;
	killedCount = 0;
	loadInput();
}

void Game::print()
{
	earthArmy.print();
	alienArmy.print();
	cout << "============== Killed/Destructed Units =============\n";
	cout << killedCount << "    units ";
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
	return (earthArmy.addUnit(unit));
}

bool Game::addAlienUnit(Unit*& unit)
{
	return (alienArmy.addUnit(unit));
}

void Game::gameTick() {
	RNG.generateUnits();
	testCode();
	print();
	//earthArmy->fight(game);
	//alienArmy->fight(game);

}

void Game::addToKilled(Unit*& unit)
{
	killedUnits.enqueue(unit);
	killedCount++;
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
		Unit* S2 = nullptr;
		if (earthArmy.getUnit(ES, S1))
			earthArmy.addUnit(S1);
	}
	else if (X < 20) {
		Unit* ET1;
		Unit* ET2 = nullptr;
		if (earthArmy.getUnit(ET, ET1))
			addToKilled(ET1);
	}
	else if (X < 30) {
		Unit* EG1;
		Unit* EG2 = nullptr;
		if (earthArmy.getUnit(EG, EG1)) {
			EG1->decrementHealth(EG1->getHealth() / 2, timestep);
			earthArmy.addUnit(EG1);
		}
	}
	else if (X < 40) {
		/*Unit* AS1[6];
		AS1[5] = 0;
		for (int i = 0; i < 4; i++) {
			if (alienArmy->getUnit(AS, AS1[i], AS1[5]));
				addToTemp(AS1[i]);
		}
		clearTemp();*/
	}
	else if (X < 50) {
		Unit* AM1;
		Unit* AM2 = nullptr;
		for (int i = 0; i < 5; i++) {
			if (alienArmy.getUnit(AM, AM1))
				alienArmy.addUnit(AM1);
		}
	}
	else if (X < 60) {
		Unit* AD1;
		Unit* AD2 = nullptr;
		for (int i = 0; i < 3; i++) {
			if (alienArmy.getUnit(AD, AD1)) {
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
	return (double(earthArmy.getSoldierCount()) / (alienArmy.getSoldierCount())) * 100;
}

int Game::getTimestep() {
	return timestep;
}

Game::~Game() {
	Unit* unit;
	while (killedUnits.dequeue(unit)) delete unit;
}