#ifndef UNIT_H
#define UNIT_H
#include <iostream>


enum UNIT_TYPE {
	HU,
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
	int joinUMLTime;
	int attackCapacity;
	static int lastEarthId;
	static int lastAlienId;

   protected:
	Game* game;
	double health;
	double power;
	double initialhealth;

   public:
	Unit(Game* game,UNIT_TYPE type, int joinTime, double health, double power, int attackCapacity);
	virtual void attack() = 0;
	void decrementHealth(double damage, int timestep);
	void getAttacked(Unit* enemyUnit, int timestep);
	void getHealed(Unit* HealUnit);
	void setUMLJoinTime(int jointime);
	int getUMLJoinTime();
	bool isDead() const;
	bool isAlien() const;
	bool isLow() const;
	int getAttackCapacity() const;
	double getHealth() const;
	int getId() const;
	int getDestructionTime() const;
	int getFirstAttackTime() const;
	int getJoinTime() const;
	UNIT_TYPE getType() const;
};

std::ostream& operator<<(std::ostream& out, const Unit* unit);

#endif
