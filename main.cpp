#include <iostream>
#include "BattleUnits/Soldier.h"
#include "BattleUnits/EarthGunner.h"
#include "Armies/Army.h"
#include "DataStructures/LinkedQueue.h"
#include "DataStructures/priQueue.h"
using namespace std;

int main() {
	priQueue<int> Q;
	Q.enqueue(1,10);
	Q.enqueue(7,5);
	Q.enqueue(5,8);
	Q.enqueue(4,7);
	Q.print();

	//cout << "Hello World";
	//return 0;
}