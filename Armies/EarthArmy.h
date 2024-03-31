#pragma once
#include "Army.h"
#include <iostream>
#include "../BattleUnits/Soldier.h"
#include "../BattleUnits/EarthGunner.h"
#include "../BattleUnits/EarthTank.h"
#include "../BattleUnits/Unit.h"
#include "../DataStructures/priQueue.h"
#include <stack> //temporary
using namespace std;

class EarthArmy : public Army
{
	priQueue <EarthGunner*> EarthGunnery;
	stack <EarthTank*> EarthTanks;
public:
	bool addUnit(UNIT_TYPE type, int joinTime, int health, int power, int attackCapacity)
	{
		switch (type) {
			case S:
				Soldier* EarthSoldier = new Soldier(joinTime,health,power,attackCapacity);
				Soldiers.enqueue(EarthSoldier);
				break;
			case AM:
				EarthTank* Tank = new EarthTank(joinTime, health, power, attackCapacity);
				EarthTanks.push(Tank);
				break;
			case AD:
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
			EarthTank* T1 = dynamic_cast <EarthTank*> (unit);
			if (T1)
				EarthTanks.push(T1);
			break;
		case EG:
			EarthGunner* G1 = dynamic_cast <EarthGunner*> (unit);
			if(G1)
				EarthGunnery.enqueue(G1, G1->getPriority());
			break;

		}
	}
	bool getTank(EarthTank*& Tank)
	{
		if (EarthTanks.empty()) return false;
		Tank = EarthTanks.top();
		EarthTanks.pop();			//temporary
		return true;
	}

	bool getGunnery(EarthGunner*& Gunnery,int& priority)
	{
		if (EarthGunnery.isEmpty()) return false;
		EarthGunnery.dequeue(Gunnery,priority);
		return true;
	}

};