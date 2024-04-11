#include "Unit.h"

#include <iostream>

int Unit::lastAlienId = 2000;
int Unit::lastEarthId = 1;

Unit::Unit(UNIT_TYPE type, int joinTime, int health, int power, int attackCapacity)
	: type(type), joinTime(joinTime), health(health), power(power), attackCapacity(attackCapacity) {
	firstAttackedTime = -1;
	destructionTime = -1;
	id = isAlien() ? lastAlienId++ : lastEarthId++;
};

std::ostream& operator<<(std::ostream& out, const Unit* unit) {
	out << unit->getId();
	return out;
}

void Unit::decrementHealth(int damage, int timestep) {
	health -= damage;
	if (health <= 0) {
		health = 0;
		destructionTime = timestep;
	}
	if (firstAttackedTime == -1) firstAttackedTime = timestep;
};

void Unit::getAttacked(Unit* enemyUnit, int timestep) {
	int damage = (enemyUnit->power * enemyUnit->health / 100) / sqrt(this->health);
	decrementHealth(damage, timestep);
};

bool Unit::isAlien() {
	return type >= AS;
}

bool Unit::isDead() { return health == 0; };
int Unit::getAttackCapacity() { return attackCapacity; };
int Unit::getHealth() { return health; };
int Unit::getId() const { return id; };
UNIT_TYPE Unit::getType() { return type; };
int Unit::getPriority() const { return priority; }
void Unit::clearAttacked() {
	int tmp;
	while (attackedIDs.dequeue(tmp))
		;
};
