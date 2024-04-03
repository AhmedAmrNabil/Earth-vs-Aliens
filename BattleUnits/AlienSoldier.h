#pragma once

#include "../Armies/Army.h"
#include "../DataStructures/LinkedQueue.h"
#include "Unit.h"
class Game;

class AlienSoldier : public Unit {

public:
	AlienSoldier(int id,int joinTime ,int health, int power, int attackCapacity) 
		: Unit(AS,id , joinTime, health, power, attackCapacity){
	};

	void attack(Game* game, int timestep) override;


};