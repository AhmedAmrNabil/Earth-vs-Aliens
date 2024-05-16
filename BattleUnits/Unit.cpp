#include "Unit.h"
#include <iostream>
#include <cmath>
#include <string>
#include "EarthSoldier.h"

int Unit::lastAlienId = 2000;
int Unit::lastEarthId = 1;
int Unit::lastSaverId = 3000;

Unit::Unit(Game* game, UNIT_TYPE type, int joinTime, double health, double power, int attackCapacity)
	: game(game), type(type), joinTime(joinTime), health(health), power(power), attackCapacity(attackCapacity) {
	firstAttackedTime = -1;
	destructionTime = -1;
	initialhealth = health;
	joinUMLTime = -1;
	id = (type == SU) ? ++lastSaverId : isAlien() ? ++lastAlienId : ++lastEarthId;
}

std::ostream& operator<<(std::ostream& out, Unit* unit) {
	
	EarthSoldier* soldier = dynamic_cast <EarthSoldier*>(unit);
	if (soldier && (soldier->isInfected() && !soldier->isImmune())) {
		out << "\033[1;31m(\033[1;34m" << unit->getId() << "\033[1;31m)\033[0m";
		return out;
	}
	std::string color = "";
	switch (unit->getType()) {
	case ES:color = "\033[1;34m"; break;
	case ET:color = "\033[1;36m"; break;
	case EG:color = "\033[1;32m"; break;
	case AS:color = "\033[1;33m"; break;
	case AM:color = "\033[1;31m"; break;
	case AD:color = "\033[1;35m"; break;
	default: color = "\033[1;37m"; break;
	}

	out << color <<unit->getId() << "\033[0m";
	return out;
}

std::string& operator+=(std::string& out, Unit* unit) {
	EarthSoldier* soldier = dynamic_cast <EarthSoldier*>(unit);
	if (soldier && (soldier->isInfected() && !soldier->isImmune())) {
		out += "\033[1;31m(\033[1;34m" + std::to_string(unit->getId()) + "\033[1;31m)\033[0m";
		return out;
	}
	switch (unit->getType()) {
	case ES:out += "\033[1;34m"; break;
	case ET:out += "\033[1;36m"; break;
	case EG:out += "\033[1;32m"; break;
	case AS:out += "\033[1;33m"; break;
	case AM:out += "\033[1;31m"; break;
	case AD:out += "\033[1;35m"; break;
	default: out += "\033[1;37m"; break;
	}

	out += std::to_string(unit->getId()) + "\033[0m";
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

void Unit::incrementHealth(double heal)
{
	health += heal;
}

void Unit::getAttacked(Unit* enemyUnit, int timestep) {
	double damage = (enemyUnit->power * enemyUnit->health / 100.0) / sqrt(this->health);
	decrementHealth(damage, timestep);
}

void Unit::getHealed(Unit* healUnit  , bool infected) {
	double heal = (healUnit->power * healUnit->health / 100.0) / sqrt(this->health);
	if(infected) incrementHealth(heal / 2);
	else incrementHealth(heal);
}

void Unit::setUMLJoinTime(int jointime) {
	joinUMLTime = jointime;
}



bool Unit::isLow() const {
	double ratio = (health / initialhealth) * 100;
	return (ratio < 20 && ratio > 0) && (type == ES || type == ET);
}

int Unit::getJoinTime() const { return joinTime; }
int Unit::getFirstAttackTime() const { return firstAttackedTime; }
int Unit::getUMLJoinTime() { return joinUMLTime; }
bool Unit::isDead() const { return health == 0; }
bool Unit::isAlien() const { return AS <= type && type <= AD; }
double Unit::getHealth() const { return health; }
int Unit::getAttackCapacity() const { return attackCapacity; }
int Unit::getId() const { return id; }
int Unit::getDestructionTime() const { return destructionTime; }
UNIT_TYPE Unit::getType() const { return type; }
int Unit::getEarthLastId() { return lastEarthId; }
int Unit::getAlienLastId() { return lastAlienId; }
int Unit::getSaverLastId() { return lastSaverId; }
