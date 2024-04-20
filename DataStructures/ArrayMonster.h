#pragma once
#include "../BattleUnits/AlienMonster.h"

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
