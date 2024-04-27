#ifndef ARRAY_MONSTER_H
#define ARRAY_MONSTER_H
#include "../BattleUnits/Unit.h"

class ArrayMonster
{
private:
	Unit* arrayMonster[1000];
	int monsterCount;
public:

	ArrayMonster();
	bool isEmpty();
	bool isFull();
	bool insert(Unit* a1);
	bool pick(Unit*& AM);
	bool peek(Unit*& AM);
	void print();
	int getCount();
};

#endif