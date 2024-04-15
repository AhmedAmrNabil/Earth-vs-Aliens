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
	return earthArmy->getUnit(type, unit);
}

bool Game::getAlienUnit(UNIT_TYPE type, Unit*& unit1, bool rear)
{
	return alienArmy->getUnit(type, unit1,rear);
}

bool Game::addEarthUnit(Unit*& unit)
{
	return (earthArmy->addUnit(unit));
}

bool Game::addAlienUnit(Unit*& unit)
{
	return (alienArmy->addUnit(unit));
}

void Game::generateUnits() {
	int A = RNG->generator(1, 100);
	if (A >= Prob) {
		Unit* unit;
		for (int i = 0; i < N; ++i) {
			unit = RNG->generateEarthUnit(timestep);
			earthArmy->addUnit(unit);
		}

	}

	A = RNG->generator(1, 100);
	if (A >= Prob) {
		Unit* unit;
		for (int i = 0; i < N; ++i) {
			unit = RNG->generateAlienUnit(timestep);
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
	if (unit->isAlien())
		alienArmy->decrementCount(unit);
	else
		earthArmy->decrementCount(unit);
	killedUnits.enqueue(unit);
	killedCount++;
}

//void Game::addToTemp(Unit*& unit)
//{
//	tempUnits.enqueue(unit);
//}
//
//void Game::clearTemp() {
//	Unit* tmp;
//	while (tempUnits.dequeue(tmp)) {
//		if (tmp->getType() > 2)
//			alienArmy->addUnit(tmp);
//		else
//			earthArmy->addUnit(tmp);
//	}
//}

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
		if (earthArmy->getUnit(ES, S1, S2)) {
			earthArmy->addUnit(S1);
			cout << "An Earth Soldier was Picked and inserted back to the original list\n";
		}
	}
	else if (X < 20) {
		Unit* ET1;
		Unit* ET2 = nullptr;
		if (earthArmy->getUnit(ET, ET1, ET2)) {
			addToKilled(ET1);
			cout << "An Earth Soldier was Picked and added to the killed list\n";
		}
	}
	else if (X < 30) {
		Unit* EG1;
		Unit* EG2 = nullptr;
		if (earthArmy->getUnit(EG, EG1, EG2)) {
			EG1->decrementHealth(EG1->getHealth() / 2, timestep);
			earthArmy->addUnit(EG1);
			cout << "An Earth Gunnery was Picked, decremented half its health and inserted back to the original list\n";
		}
	}
	else if (X < 40) {
		Unit* AS1[6];
		AS1[5] = 0;
		int count = 0;
		LinkedQueue<Unit*> temp;
		for (int i = 0; i < 4; i++) {
			if (alienArmy->getUnit(AS, AS1[i], AS1[5])) {
				count++;
				AS1[i]->decrementHealth(AS1[i]->getHealth() / 2, timestep); //assuming it's decremented by half as well
				temp.enqueue(AS1[i]);
			}
		}
		cout << count <<" Alien Soldiers were Picked, decremented half their health, added to a temp list then inserted back to the original list\n";
		while (!temp.isEmpty()) {
			Unit* value;
			temp.dequeue(value);
			addAlienUnit(value);
		}
	}
	else if (X < 50) {
		Unit* AM1;
		Unit* AM2 = nullptr;
		int count = 0;
		for (int i = 0; i < 5; i++) {
			if (alienArmy->getUnit(AM, AM1, AM2)) {
				count++;
				alienArmy->addUnit(AM1);
			}
		}
		cout << count <<" Alien Monsters were Picked and inserted back to the original list\n";
	}
	else if (X < 60) {
		Unit* AD1;
		Unit* AD2 = nullptr;
		int count = 0;
		for (int i = 0; i < 3; i++) {
			if (alienArmy->getUnit(AD, AD1, AD2)) {
				addToKilled(AD1);
				count++;
				if (AD2) {
					addToKilled(AD2);
					count++;
				}
			}
		}
		cout << count <<" Alien Drones were Picked from front and rear of their list and added to the Killed list\n";
	}
	++timestep;
}

double Game::getSoldierRatio()
{
	return (double(earthArmy->getSoldierCount()) / (alienArmy->getSoldierCount())) * 100;
}

int Game::getTimestep()
{
	return timestep;
}


