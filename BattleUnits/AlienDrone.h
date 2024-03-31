#pragma once

class AlienDrone :public Unit
{
public:
	AlienDrone(int joinTime, int health, int power, int attackCapacity) :Unit(AM, joinTime, health, power, attackCapacity)
	{}
	void attack(Army* enemyArmy, int timestep) {}
};