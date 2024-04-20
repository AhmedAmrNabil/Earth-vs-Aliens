#ifndef UNIT_H
#define UNIT_H
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
	static int lastEarthId;
	static int lastAlienId;

   protected:
	Game* game;
	int health;
	int power;


   public:
	Unit(Game* game,UNIT_TYPE type, int joinTime, int health, int power, int attackCapacity);
	virtual void attack() = 0;
	void decrementHealth(int damage, int timestep);
	void getAttacked(Unit* enemyUnit, int timestep);
	bool isDead();
	bool isAlien() const;
	int getAttackCapacity() const;
	int getHealth() const;
	int getId() const;
	UNIT_TYPE getType() const;
};

ostream& operator<<(ostream& out, const Unit* unit);

#endif
