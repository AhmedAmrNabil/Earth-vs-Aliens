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
    RandGen RNG;
    int timestep;
    int N, ES, ET, EG, AS, AM, AD, prob;
    int powerEmin,powerEmax, attackEmin, attackEmax, healthEmin, healthEmax;
    int powerAmin, powerAmax, attackAmin, attackAmax, healthAmin, healthAmax;

    int power, health, attackcap;
public:
    Game()
    {
        timestep = 0;
        loadInput();
    }
    void loadInput()
    {
        ifstream input_file;
        input_file.open("input.txt", ios::in);
        input_file >> N >> ES >> ET >> EG >> AS >> AM >> AD >> prob;
        loadRange(input_file, powerEmin, powerEmax);
        loadRange(input_file, healthEmin, healthEmax);
        loadRange(input_file, attackEmin, attackEmax);
        loadRange(input_file, powerAmin, powerAmax);
        loadRange(input_file, healthAmin, healthAmax);
        loadRange(input_file, attackAmin, attackAmax);
        power = RNG.generator(powerEmin, powerEmax);
        health= RNG.generator(healthEmin, healthEmax);
        attackcap = RNG.generator(attackEmin, attackEmax);
        
        cout <<  powerEmin << "  " <<  powerEmax <<endl;
        cout << healthEmin << "  " << healthEmax << endl;
        cout << attackEmin << "  " << attackEmax << endl;
        cout <<  powerAmin << "  " <<  powerAmax << endl;
        cout << healthAmin << "  " << healthAmax << endl;
        cout << attackAmin << "  " << attackAmax << endl;
        cout << power << "  " << health << "  " << attackcap;
        
        input_file.close();
    }
    void loadRange(ifstream &input_file,int& start, int& end)
    {
        input_file >> start >> end;
        end = -1 * end;
    }
    void print()
    {
        EA->print();
        AA->print();
    }

};