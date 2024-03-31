#pragma once

#include "../BattleUnits/Unit.h"
#include "./Army.h"
#include "../BattleUnits/AlienMonster.h"
#include "../DataStructures/ArrayMonster.h"

class AlienArmy:public Army 
{
	ArrayMonster arrayMonster;
   public:
	   bool getDronePair(Unit*& drone1, Unit*& drone2) {}
	   bool addUnit(UNIT_TYPE type, int joinTime, int health, int power, int attackCapacity)
	   {
		   switch (type)
		   {
		   case S:
		   {
			   Soldier* AlienSoldier = new Soldier(joinTime, health, power, attackCapacity);
			   Soldiers.enqueue(AlienSoldier);
		   }
		   break;

		   case AM:
		   {
			   AlienMonster* alienMonster = new AlienMonster(joinTime, health, power, attackCapacity);
			   arrayMonster.insert(alienMonster);
		   }
		   break;

		   case AD:
		   {
			   AlienDrone* alienDrone = new AlienDrone(joinTime, health, power, attackCapacity);
		   }
		   break;
		   }
	   }

};