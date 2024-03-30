#pragma once
#include "Army.h"
#include <iostream>
#include "../BattleUnits/Soldier.h"
#include "../BattleUnits/EarthGunner.h"
#include "../BattleUnits/Unit.h"
#include "../DataStructures/priQueue.h"
using namespace std;

class EarthArmy : public Army
{
	priQueue <EarthGunner*> EarthGunnery;
public:
	bool addUnit(UNIT_TYPE type, int joinTime, int health, int power, int attackCapacity)
	{
		switch (type) {
			case S:
				Soldier* EarthSoldier = new Soldier(joinTime,health,power,attackCapacity);
				Soldiers.enqueue(EarthSoldier);
				break;
			case ET:
				break;
			case EG:
				EarthGunner* EarthGunnery1 = new EarthGunner(joinTime, health, power, attackCapacity);
				EarthGunnery.enqueue(EarthGunnery1, EarthGunnery1->getPriority());
				break;

		}

	}
	bool addExisting(UNIT_TYPE type, Unit* unit)
	{
		switch (type) {
		case S:
			Soldier* S1 = dynamic_cast <Soldier*> (unit);
			if(S1)
			Soldiers.enqueue(S1);
			break;
		case ET:
			break;
		case EG:
			EarthGunner* G1 = dynamic_cast <EarthGunner*> (unit);
			if(G1)
			EarthGunnery.enqueue(G1, G1->getPriority());
			break;

		}
	}

};