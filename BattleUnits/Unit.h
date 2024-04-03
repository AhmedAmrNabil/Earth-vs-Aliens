#pragma once
#include <cmath>
#include "../DataStructures/LinkedQueue.h"

enum UNIT_TYPE {
	ES,
	ET,
	EG,
	AS,
	AM,
	AD
};


class Army;
class Game;
class Unit {

	int id;
	UNIT_TYPE type;
	int joinTime;
	int firstAttackedTime;
	int destructionTime;
	int attackCapacity;
protected:
	LinkedQueue <Unit*>attackedUnits;
	void clearAttacked() {
		Unit* tmp;
		while (attackedUnits.dequeue(tmp));
	}
	int health;
	int power;
public:
	Unit(UNIT_TYPE type, int id, int joinTime, int health, int power, int attackCapacity)
		: type(type), joinTime(joinTime), health(health), power(power), attackCapacity(attackCapacity), id(id) {
		firstAttackedTime = -1;
	};

	virtual void attack(Game* game, int timestep) = 0;

	void getAttacked(Unit* enemyUnit, int timestep) {
		int damage = (enemyUnit->power * enemyUnit->health / 100) / sqrt(this->health);
		decrementHealth(damage, timestep);
	};

	bool isDead() { return health == 0; };

	int getAttackCapacity() { return this->attackCapacity; };

	void decrementHealth(int damage, int timestep) {
		health -= damage;
		if (health <= 0) {
			health = 0;
			destructionTime = timestep;
		}
		if (firstAttackedTime == -1) firstAttackedTime = timestep;
	}

	int getHealth() { return health; }

	friend ostream& operator << (ostream& out, const Unit* unit) {
		out << unit->id;
		return out;
	}
};


