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
	AD,
	SU
};

class Army;
class Game;
class Unit {
	int id;
	UNIT_TYPE type;
	int joinTime;
	int firstAttackedTime;
	int joinUMLTime;
	int attackCapacity;
	static int lastEarthId;
	static int lastAlienId;
	static int lastSaverId;
	bool _isHealedBefore;

   protected:
	int destructionTime;
	Game* game;
	double health;
	double power;
	double initialhealth;

   public:

	Unit(Game* game,UNIT_TYPE type, int joinTime, double health, double power, int attackCapacity);
	
	// Helper functions for changing health
	void decrementHealth(double damage, int timestep);
	void incrementHealth(double heal);
	double getHealth() const;
	bool isDead() const;

	// Attack funciton and its helper
	virtual bool attack() = 0;
	void getAttacked(Unit* enemyUnit, int timestep);
	
	//UML helper functions
	void setUMLJoinTime(int jointime);
	int getUMLJoinTime();
	void getHealed(Unit* HealUnit , bool infected);
	bool isLow() const;
	bool isHealedBefore() const; 
	void setFullyHealed();

	// Getters for the output file and printing
	int getId() const;
	UNIT_TYPE getType() const;
	int getDestructionTime() const;
	int getFirstAttackTime() const;
	int getJoinTime() const;

	// Getter for randGen to make it stop generating units
	static int getEarthLastId();
	static int getAlienLastId();
	static int getSaverLastId();

	bool isAlien() const;
	int getAttackCapacity() const;
};

// Overloading the ostream << operator for printing in Datastructrures
std::ostream& operator<<(std::ostream& out, Unit* unit);

//Overloading the string += operator for printing in string when attacking
std::string& operator+=(std::string& out, Unit* unit);

#endif
