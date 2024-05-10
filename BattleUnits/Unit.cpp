#include "Unit.h"
#include <iostream>
#include <cmath>
#include "EarthSoldier.h"

int Unit::lastAlienId = 2000;
int Unit::lastEarthId = 1;

Unit::Unit(Game* game,UNIT_TYPE type, int joinTime, double health, double power, int attackCapacity)
	: game(game),type(type), joinTime(joinTime), health(health), power(power), attackCapacity(attackCapacity) {
	firstAttackedTime = -1;
	destructionTime = -1;
	initialhealth = health;
	joinUMLTime = -1;
	id = isAlien() ? lastAlienId++ : lastEarthId++;
}

std::ostream& operator<<(std::ostream& out, Unit* unit) {
	EarthSoldier* soldier = dynamic_cast <EarthSoldier*>(unit);
	if (soldier && (soldier->isInfected() && !soldier->isImmune())) {
		out << "XX ";
	}
	out << unit->getId();
	return out;
}

void Unit::decrementHealth(double damage, int timestep) {
	health -= damage;
	if (health <= 0) {
		health = 0;
		destructionTime = timestep;
	}
	if (firstAttackedTime == -1) firstAttackedTime = timestep;
}

void Unit::getAttacked(Unit* enemyUnit, int timestep) {
	double damage = (enemyUnit->power * enemyUnit->health / 100.0) / sqrt(this->health);
	decrementHealth(damage, timestep);
}

void Unit::getHealed(Unit* healUnit) {
	double heal = (healUnit->power * healUnit->health / 100.0) / sqrt(this->health);
	health += heal;
}

void Unit::setUMLJoinTime(int jointime) {
	joinUMLTime = jointime;
}



bool Unit::isLow() const {
	double ratio = (health / initialhealth) * 100;
	return (ratio < 20 && ratio > 0) && (type == ES || type == ET) ;
}

int Unit::getJoinTime() const { return joinTime; }
int Unit::getFirstAttackTime() const { return firstAttackedTime; }
int Unit::getUMLJoinTime() { return joinUMLTime; }
bool Unit::isDead() const { return health == 0; }
bool Unit::isAlien() const { return type >= AS; }
double Unit::getHealth() const { return health; }
int Unit::getAttackCapacity() const { return attackCapacity; }
int Unit::getId() const { return id; }
int Unit::getDestructionTime() const{ return destructionTime; }
UNIT_TYPE Unit::getType() const { return type; }
