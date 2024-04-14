#include "RandGen.h"

#include "BattleUnits/AlienDrone.h"
#include "BattleUnits/AlienMonster.h"
#include "BattleUnits/AlienSoldier.h"
#include "BattleUnits/EarthGunner.h"
#include "BattleUnits/EarthSoldier.h"
#include "BattleUnits/EarthTank.h"

RandGen::RandGen() {
    srand(time(0));

}

int RandGen::generator(int begin, int end) {
    int random = begin + (rand() % (end - begin + 1));
    return random;
}

Unit* RandGen::generateEarthUnit(int timestep) {
    Unit* unit;
    int power = generator(earthMinPower, earthMaxPower);
    int health = generator(earthMinHealth, earthMaxHealth);
    int capacity = generator(earthMinCapacity, earthMaxCapacity);
    int B = generator(1, 100);
    if (B <= percentES)
        unit = new EarthSoldier(timestep, health, power, capacity);
    else if (B <= percentES + percentET)
        unit = new EarthTank(timestep, health, power, capacity);
    else
        unit = new EarthGunner(timestep, health, power, capacity);

    return unit;
}

Unit* RandGen::generateAlienUnit(int timestep) {
    Unit* unit;
    int power = generator(alienMinPower, alienMaxPower);
    int health = generator(alienMinHealth, alienMaxHealth);
    int capacity = generator(alienMinCapacity, alienMaxCapacity);
    int B = generator(1, 100);
    if (B <= percentAS)
        unit = new AlienSoldier(timestep, health, power, capacity);
    else if (B <= percentAS + percentAM)
        unit = new AlienMonster(timestep, health, power, capacity);
    else
        unit = new AlienDrone(timestep, health, power, capacity);

    return unit;
}

void RandGen::initParams(int randGenparams[]) {
    percentES = randGenparams[0];
    percentET = randGenparams[1];
    percentAS = randGenparams[3];
    percentAM = randGenparams[4];
    earthMinPower = randGenparams[6];
    earthMaxPower = randGenparams[7];
    earthMinHealth = randGenparams[8];
    earthMaxHealth = randGenparams[9];
    earthMinCapacity = randGenparams[10];
    earthMaxCapacity = randGenparams[11];
    alienMinPower = randGenparams[12];
    alienMaxPower = randGenparams[13];
    alienMinHealth = randGenparams[14];
    alienMaxHealth = randGenparams[15];
    alienMinCapacity = randGenparams[16];
    alienMaxCapacity = randGenparams[17];
}
