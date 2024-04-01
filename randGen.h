#pragma once
#include <time.h>

#include <cstdlib>
#include <fstream>

#include "Armies/Army.h"
#include "BattleUnits/AlienDrone.h"
#include "BattleUnits/AlienMonster.h"
#include "BattleUnits/EarthGunner.h"
#include "BattleUnits/EarthTank.h"
#include "BattleUnits/Soldier.h"

class RandGen {
	int N;
	int percentES;
	int percentET;
	int percentAS;
	int percentAM;
	int Thr;
	int earthMinPower, earthMaxPower;
	int earthMinHealth, earthMaxHealth;
	int earthMinCapacity, earthMaxCapacity;
	int alienMinPower, alienMaxPower;
	int alienMinHealth, alienMaxHealth;
	int alienMinCapacity, alienMaxCapacity;
	Army* earthArmy;
	Army* alienArmy;

public:
	RandGen(Army* earthArmy, Army* alienArmy) {}

	void loadInput() {
		ifstream input_file;
		input_file.open("input.txt", ios::in);
		input_file >> N >> percentES >> percentET >> percentAS >> percentAM >> Thr;
		loadRange(input_file, earthMinPower, earthMaxPower);
		loadRange(input_file, earthMinHealth, earthMaxHealth);
		loadRange(input_file, earthMinCapacity, earthMaxCapacity);
		loadRange(input_file, alienMinPower, alienMaxPower);
		loadRange(input_file, alienMinHealth, alienMaxHealth);
		loadRange(input_file, alienMinCapacity, alienMaxCapacity);
		input_file.close();
	}

	void loadRange(ifstream& input_file, int& start, int& end) {
		input_file >> start >> end;
		end = -1 * end;
	}

	void generate(int timestep) {
		int power, health, capacity;
		srand(time(0));
		int A = (rand() % 100) + 1;
		if (A >= Thr) {
			UNIT_TYPE type;
			for (int i = 0; i < N; ++i) {
				power = earthMinPower + rand() % (earthMaxPower - earthMinPower);
				health = earthMinHealth + rand() % (earthMaxHealth - earthMinHealth);
				capacity = earthMinCapacity + rand() % (earthMaxCapacity - earthMinCapacity);
				int B = (rand() % 100) + 1;
				if (B <= percentES)
					type = S;
				else if (B <= percentES + percentET)
					type = ET;
				else
					type = EG;

				earthArmy->addUnit(type, timestep, health, power, capacity);
			}
		}

		A = (rand() % 100) + 1;
		if (A >= Thr) {
			UNIT_TYPE type;
			for (int i = 0; i < N; ++i) {
				power = alienMinPower + rand() % (alienMaxPower - alienMinPower);
				health = alienMinHealth + rand() % (alienMaxHealth - alienMinHealth);
				capacity = alienMinCapacity + rand() % (alienMaxCapacity - alienMinCapacity);
				int B = (rand() % 100) + 1;
				if (B <= percentAS)
					type = S;
				else if (B <= percentAS + percentAM)
					type = AM;
				else
					type = AD;

				alienArmy->addUnit(type, timestep, health, power, capacity);
			}
		}

	}
};
