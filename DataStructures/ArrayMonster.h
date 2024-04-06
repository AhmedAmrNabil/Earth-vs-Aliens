#pragma once
#include "../BattleUnits/AlienMonster.h"
#include <cmath>
#include <cstdlib> 
#include <time.h> 


class ArrayMonster
{
private:
	Unit* arrayMonster[1000];
	int monsterCount;
public:
	ArrayMonster() :arrayMonster() {
		srand(time(0));
		monsterCount = 0;
	}

	bool isEmpty() {
		return (monsterCount == 0);
	}

	bool isFull() {
		return (monsterCount == 1000);
	}

	bool insert(Unit* a1) {
		if (!isFull()) {
			arrayMonster[monsterCount++] = a1;
			return true;
		}
		return false;
	}

	bool pick(Unit*& AM) {
		if (!isEmpty()) {
			int random = rand() % monsterCount;
			AM = arrayMonster[random];
			arrayMonster[random] = arrayMonster[--monsterCount];
			return true;
		}
		return false;
	}

	void print() {
		if (isEmpty()) return;
		cout << "[" << arrayMonster[0];
		for (int i = 1; i < monsterCount; i++) {
			cout << ", " << arrayMonster[i];
		}
		cout << "]";
	}
};
