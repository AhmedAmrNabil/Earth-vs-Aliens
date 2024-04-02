#ifndef RAND_GEN_H_
#define RAND_GEN_H_
#include <time.h>

#include <cstdlib>
#include <fstream>

#include "Armies/Army.h"

class EarthSoldier; 
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
	int lastEarthId;
	int lastAlienId;

public:
	RandGen(Army* earthArmy, Army* alienArmy);

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

	int generator(int begin, int end) {
		int random = begin + (rand() % (end-begin));
		return random;
	}
	void generate(int timestep);
};

#endif
