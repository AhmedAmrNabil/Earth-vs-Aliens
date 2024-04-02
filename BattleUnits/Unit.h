#pragma once
#include <cmath>
#include "../DataStructures/LinkedQueue.h"

enum UNIT_TYPE {
	S,
	ET,
	EG,
	AM,
	AD
};


class Army;
class Unit {
	static int lastEarthId;
	static int lastAlienId;
	int id;
	UNIT_TYPE type;
	int joinTime;
	int firstAttackedTime;
	int destructionTime;
	int attackCapacity;
	virtual bool isAlien() = 0;

protected:
	LinkedQueue <Unit*>attackedUnits;
	void clearAttacked() {
		Unit* tmp;
		while (attackedUnits.dequeue(tmp));
	}
	int health;
	int power;
public:
	Unit(UNIT_TYPE type, int joinTime, int health, int power, int attackCapacity) 
		: type(type), joinTime(joinTime), health(health), power(power), attackCapacity(attackCapacity) {
		this->id = isAlien() ? lastAlienId++ : lastEarthId++;
		firstAttackedTime = -1;
	};

	virtual void attack(Army* enemyArmy, int timestep) = 0;

	void getAttacked(Unit* enemyUnit, int timestep) {
		health -= (enemyUnit->power * enemyUnit->health / 100) / sqrt(this->health);
		if (health <= 0)
		{
			health = 0;
			destructionTime = timestep;
		}
		if (firstAttackedTime == -1) firstAttackedTime = timestep;
	};

	bool isDead() { return health == 0; };

	int getAttackCapacity() { return this->attackCapacity; };
	//void printID() { cout << id; }
	
	friend ostream& operator << (ostream& out, const Unit& unit) {
		out << unit.id;
		return out;
	}
};

int Unit::lastEarthId = 0;
int Unit::lastAlienId = 2000;
