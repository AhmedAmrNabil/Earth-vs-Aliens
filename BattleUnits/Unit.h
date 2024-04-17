#ifndef UNIT_H_
#define UNIT_H_
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
	bool isDead();
	int getAttackCapacity();
	int getHealth();
	int getId() const;
	UNIT_TYPE getType();
	void getAttacked(Unit* enemyUnit, int timestep);
	void decrementHealth(int damage, int timestep);
	bool isAlien();
};

ostream& operator<<(ostream& out, const Unit* unit);

#endif
