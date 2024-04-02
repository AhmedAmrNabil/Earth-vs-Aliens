#include <iostream>

#include "Armies/AlienArmy.h"
#include "Armies/EarthArmy.h"
#include "Game.h"
using namespace std;

int main() {
    Game G;
    for (int i = 0; i < 10; i++) {
        G.print();
    }
    G.print();
    return 0;
}

// int number;
// char ch;

// bool loop = false;
// while (loop == false)
//{
//	G.testCode();
//	G.print();
//	ch = _getch();
//	if (ch == 27)
//		loop = true;
// }
