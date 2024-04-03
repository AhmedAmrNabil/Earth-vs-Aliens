#pragma once
#include "../DataStructures/LinkedListStack.h"
#include "Unit.h"

class Game;
class AlienDrone :public Unit
{
public:
	AlienDrone(int id, int joinTime, int health, int power, int attackCapacity) 
		:Unit(AD, id,joinTime, health, power, attackCapacity)
	{}
	void attack(Game* game, int timestep);
};