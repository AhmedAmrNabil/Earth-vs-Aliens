#include <iostream>

#include "Armies/AlienArmy.h"
#include "Armies/EarthArmy.h"
#include "Game.h"
#include <conio.h>
using namespace std;

int main() {
    Game G;

    int number;
    char ch;
    bool loop = true;
    while (loop)
    {
        G.gameTick();
    	ch = _getch();
    	if (ch == 27)
    		loop = false;
    }
    return 0;
}


