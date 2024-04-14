#ifndef RAND_GEN_H_
#define RAND_GEN_H_

#include "Armies/Army.h"

class RandGen {
    int percentES;
    int percentET;
    int percentAS;
    int percentAM;
    int earthMinPower, earthMaxPower;
    int earthMinHealth, earthMaxHealth;
    int earthMinCapacity, earthMaxCapacity;
    int alienMinPower, alienMaxPower;
    int alienMinHealth, alienMaxHealth;
    int alienMinCapacity, alienMaxCapacity;


   public:
    RandGen();
    int generator(int begin, int end);
    Unit* generateEarthUnit(int timestep);
    Unit* generateAlienUnit(int timestep);
    void initParams(int randGenparams[]);
};

#endif
