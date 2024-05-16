#include "ArrayMonster.h"
#include <cstdlib> 
#include <time.h> 
#include <iostream>
using std::cout;

ArrayMonster::ArrayMonster() :arrayMonster()
{
	srand(int(time(0)));
	monsterCount = 0;
}

bool ArrayMonster::isEmpty()
{
	return (monsterCount == 0);
}

bool ArrayMonster::isFull()
{
	return (monsterCount == 1000);
}

bool ArrayMonster::insert(Unit* a1)
{
	if (!isFull()) {
		arrayMonster[monsterCount++] = a1;
		return true;
	}
	return false;
}

bool ArrayMonster::pick(Unit*& AM)
{
	if (!isEmpty()) {
		int random = rand() % monsterCount;
		AM = arrayMonster[random];
		arrayMonster[random] = arrayMonster[--monsterCount];
		return true;
	}
	return false;
}

bool ArrayMonster::peek(Unit*& AM)
{
	if (!isEmpty()) {
		int random = rand() % monsterCount;
		AM = arrayMonster[random];
		return true;
	}
	return false;
}

int ArrayMonster::getCount() {
	return monsterCount;
}

void ArrayMonster::print()
{
	if (isEmpty()) return;
	cout << "[" << arrayMonster[0];
	for (int i = 1; i < monsterCount; i++) {
		cout << ", " << arrayMonster[i];
	}
	cout << "]";
}

