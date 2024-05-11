#include "Unit.h"
#include <iostream>
#include <cmath>
#include <windows.h>
#include "EarthSoldier.h"

int Unit::lastAlienId = 2000;
int Unit::lastEarthId = 1;

Unit::Unit(Game* game, UNIT_TYPE type, int joinTime, double health, double power, int attackCapacity)
	: game(game), type(type), joinTime(joinTime), health(health), power(power), attackCapacity(attackCapacity) {
	firstAttackedTime = -1;
	destructionTime = -1;
	initialhealth = health;
	joinUMLTime = -1;
	id = isAlien() ? lastAlienId++ : lastEarthId++;
}

std::ostream& operator<<(std::ostream& out, Unit* unit) {
	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsole, &info);
	EarthSoldier* soldier = dynamic_cast <EarthSoldier*>(unit);
	if (soldier && (soldier->isInfected() && !soldier->isImmune())) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | 0xf0 & info.wAttributes);
		out << "(";
	}
	unsigned short int color = 0;
	switch (unit->getType()) {
	case ES:color = FOREGROUND_BLUE; break;
	case ET:color = FOREGROUND_BLUE | FOREGROUND_GREEN; break;
	case EG:color = FOREGROUND_GREEN; break;
	case AS:color = FOREGROUND_BLUE | FOREGROUND_RED; break;
	case AM:color = FOREGROUND_RED; break;
	case AD:color = FOREGROUND_RED | FOREGROUND_GREEN; break;
	default: color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break;
	}
	color |= FOREGROUND_INTENSITY;
	SetConsoleTextAttribute(hConsole, color | 0xf0 & info.wAttributes);

	out << unit->getId();
	if (soldier && (soldier->isInfected() && !soldier->isImmune())) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | 0xf0 & info.wAttributes);
		out << ")";
	}
	SetConsoleTextAttribute(hConsole, info.wAttributes);
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
	return (ratio < 20 && ratio > 0) && (type == ES || type == ET);
}

int Unit::getJoinTime() const { return joinTime; }
int Unit::getFirstAttackTime() const { return firstAttackedTime; }
int Unit::getUMLJoinTime() { return joinUMLTime; }
bool Unit::isDead() const { return health == 0; }
bool Unit::isAlien() const { return type >= AS; }
double Unit::getHealth() const { return health; }
int Unit::getAttackCapacity() const { return attackCapacity; }
int Unit::getId() const { return id; }
int Unit::getDestructionTime() const { return destructionTime; }
UNIT_TYPE Unit::getType() const { return type; }
int Unit::getEarthLastId() { return lastEarthId; }
int Unit::getAlienLastId() { return lastAlienId; }
