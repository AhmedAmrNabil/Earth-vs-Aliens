#pragma once
#include <iostream>
#include <fstream>
#include "Armies/Army.h"
#include "RandGen.h"
class Game
{
	Army* earthArmy;
	Army* alienArmy;
	RandGen* RNG;
	int timestep;
	int N, ESn, ETn, EGn, ASn, AMn, ADn, prob;
	int powerEmin, powerEmax, attackEmin, attackEmax, healthEmin, healthEmax;
	int powerAmin, powerAmax, attackAmin, attackAmax, healthAmin, healthAmax;

	int powerE, healthE, attackcapE;
	int powerA, healthA, attackcapA;
	LinkedQueue <Unit*> killedUnits;
public:
	Game(Army* earthArmy, Army* alienArmy)
	{
		timestep = 0;
		this->earthArmy = earthArmy;
		this->alienArmy = alienArmy;
		RNG = new RandGen(earthArmy, alienArmy);
		this->earthArmy->setKilledList(&killedUnits);
		this->alienArmy->setKilledList(&killedUnits);

	}

	void print()
	{
		earthArmy->print();
		//AA->print();
	}

	bool getEarthUnit(UNIT_TYPE type, Unit*& unit) {
		Unit* tmp;
		return earthArmy->getUnit(type, unit, tmp);
	}

	bool getAlienUnit(UNIT_TYPE type, Unit*& unit1, Unit*& unit2) {
		return alienArmy->getUnit(type, unit1, unit2);
	}


	bool addExistingEarthUnit(UNIT_TYPE type, Unit*& unit) {
		return earthArmy->addExisting(type, unit);
	}

	bool addExistingAlienUnit(UNIT_TYPE type, Unit*& unit) {
		return alienArmy->addExisting(type, unit);
	}

	void addToKilled(Unit*& unit) {
		killedUnits.enqueue(unit);
	}

	void testCode() {
		cout << "\ncurrent timestep: " << timestep;
		RNG->generate(timestep);
		int X = RNG->generator(1, 100);
		cout << ", X: " << X << endl;
		if (X > 0 && X < 10) {
			Unit* S1;
			Unit* S2 = nullptr;
			earthArmy->getUnit(ES, S1, S2);
			earthArmy->addExisting(ES, S1);
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
			alienArmy->addExisting(AM, AM1);
			alienArmy->addExisting(AM, AM2);
			alienArmy->addExisting(AM, AM3);
		}
		else if (X > 50 && X < 60) {
			Unit* AD1;
			Unit* AD2;

			alienArmy->getUnit(AD, AD1, AD1);
			alienArmy->getUnit(AD, AD2, AD2);
			alienArmy->addToKilled(AD1);
			alienArmy->addToKilled(AD2);
		}
		++timestep;
	}
};