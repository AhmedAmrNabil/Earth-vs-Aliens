#pragma once
#include <iostream>
#include <fstream>
#include "Armies/Army.h"
#include "Armies/EarthArmy.h"
#include "Armies/AlienArmy.h"
#include "RandGen.h"
class Game
{
    EarthArmy* EA;
    AlienArmy* AA;
    RandGen* RNG;
    int timestep;
    int N, ESn, ETn, EGn, ASn, AMn, ADn, prob;
    int powerEmin,powerEmax, attackEmin, attackEmax, healthEmin, healthEmax;
    int powerAmin, powerAmax, attackAmin, attackAmax, healthAmin, healthAmax;

    int powerE, healthE, attackcapE;
    int powerA, healthA, attackcapA;
    LinkedQueue <Unit*> killedUnits;
public:
    Game()
    {
        timestep = 0;
        EA = new EarthArmy(&killedUnits);
        AA = new AlienArmy(&killedUnits);
        RNG = new RandGen(EA, AA);
    }
  
    void print()
    {
        EA->print();
        //AA->print();
    }
    void testCode() {
        RNG->generate(timestep);
        int X = RNG->generator(1, 100);
        if (X > 0 && X < 10) {
            Unit* S1;
            Unit* S2 = nullptr;
            EA->getUnit(ES, S1, S2);
            EA->addExisting(ES, S1);
        }
        else if (X > 10 && X < 20) {
            Unit* ET1;
            Unit* ET2 = nullptr;
            EA->getUnit(ET, ET1, ET2);
            EA->addToKilled(ET1);
        }
        else if (X > 20 && X < 30) {
            Unit* EG1;
            Unit* EG2 = nullptr;
            EA->getUnit(EG, EG1, EG2);
            EA->addToKilled(EG1);
        }
        else if (X > 30 && X < 40) {
            Unit* AS1;
            Unit* AS2;
            Unit* AS3;
            Unit* AS4 = nullptr;

            AA->getUnit(AS, AS1, AS4);
            AA->getUnit(AS, AS2, AS4);
            AA->getUnit(AS, AS3, AS4);
        }
        else if (X > 40 && X < 50) {
            Unit* AM1;
            Unit* AM2;
            Unit* AM3;
            Unit* AM4 = nullptr;

            AA->getUnit(AM, AM1, AM4);
            AA->getUnit(AM, AM2, AM4);
            AA->getUnit(AM, AM3, AM4);
            AA->addExisting(AM, AM1);
            AA->addExisting(AM, AM2);
            AA->addExisting(AM, AM3);
        }
        else if (X > 50 && X < 60) {
            Unit* AD1;
            Unit* AD2;

            AA->getUnit(AD, AD1, AD1);
            AA->getUnit(AD, AD2, AD2);
            AA->addToKilled(AD1);
            AA->addToKilled(AD2);
        }
    }
};