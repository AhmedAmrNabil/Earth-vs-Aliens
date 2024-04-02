#pragma once
#include "../Game.h"
#include "../DataStructures/LinkedListStack.h"

class AlienDrone :public Unit
{
public:
	AlienDrone(int id, int joinTime, int health, int power, int attackCapacity) 
		:Unit(AM, id,joinTime, health, power, attackCapacity)
	{}
	void attack(Game* game, int timestep);
};