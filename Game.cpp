#include "Game.h"
#include <conio.h>
#include <fstream>
#include <fstream>



Game::Game():RNG(this)
{
	timestep = 1;
	loadInput();
}

void Game::printarmies()
{
	cout << "\nCurrent Timestep: " << timestep << endl;
	earthArmy.print();
	alienArmy.print();
}

void Game::printkilledunits()
{
	cout << "\t============== Killed/Destructed Units ============\n";
	cout << "\t" << killedUnits.getCount() << "    units ";
	killedUnits.print();
	cout << endl;
}

void Game::printUML()
{
	cout << "\t============== Unit Maintenance List ==============\n";
	cout << "\t" << UML.getCount() << "    units ";
	UML.print();
	cout << endl;
}

bool Game::getEarthUnit(UNIT_TYPE type, Unit*& unit)
{
	return earthArmy.getUnit(type, unit);
}

bool Game::getAlienUnit(UNIT_TYPE type, Unit*& unit)
{
	return alienArmy.getUnit(type, unit);
}

bool Game::getfromUML(Unit*& unit)
{
	int pri;
	bool b = UML.dequeue(unit , pri);
	while (b && timestep - unit->getUMLJoinTime() > 10) {
		addToKilled(unit);
		b = UML.dequeue(unit , pri);
	}
	return b;
}

bool Game::isUMLEmpty()
{
	return (UML.isEmpty());
}

bool Game::addEarthUnit(Unit*& unit)
{
	return earthArmy.addUnit(unit);
}

bool Game::addAlienUnit(Unit*& unit)
{
	return alienArmy.addUnit(unit);
}

void Game::gameTick() {
	RNG.generateUnits();
	printarmies();
	earthArmy.fight();
	alienArmy.fight();
	printkilledunits();
	printUML();
	++timestep;
}

void Game::addToKilled(Unit*& unit)
{
	killedUnits.enqueue(unit);
}

void Game::addToUML(Unit*& unit , int joinUMLtime)
{
	int pri;
	if (unit->getType() == ES) pri = (earthData.maxHealth - unit->getHealth()) * 1000;
	else pri = -1;
	UML.enqueue(unit , pri);
	unit->setUMLJoinTime(joinUMLtime);
}

void Game::handleUnit(Unit*& unit)
{
	if (unit->isDead()) addToKilled(unit);
	else if (unit->isLow()) addToUML(unit , timestep);
	else {
		if (unit->isAlien()) addAlienUnit(unit);
		else addEarthUnit(unit);
	}
}
 
void Game::loadInput()
{
	int N, Prob;
	ifstream input_file;
	input_file.open("input.txt", ios::in);
	input_file >> N;

	input_file >> percentages.percentES >> percentages.percentET >> percentages.percentEG >> percentages.percentHU;
	input_file >> percentages.percentAS >> percentages.percentAM >> percentages.percentAD;
	
	input_file >> Prob;
	input_file >> earthData.minPower >> earthData.maxPower;
	input_file >> earthData.minHealth >> earthData.maxHealth;
	input_file >> earthData.minCapacity >> earthData.maxCapacity;

	earthData.maxPower *= -1;
	earthData.maxHealth *= -1;
	earthData.maxCapacity *= -1;

	input_file >> alienData.minPower >> alienData.maxPower;
	input_file >> alienData.minHealth >> alienData.maxHealth;
	input_file >> alienData.minCapacity >> alienData.maxCapacity;

	alienData.maxPower *= -1;
	alienData.maxHealth *= -1;
	alienData.maxCapacity *= -1;

	RNG.setData(earthData, alienData,percentages, N, Prob);

	input_file.close();
}

EarthArmy* Game::getEarthArmy() {
	return &earthArmy;
}
AlienArmy* Game::getAlienArmy() {
	return &alienArmy;
}

double Game::getSoldierRatio()
{
	return (double(earthArmy.getSoldierCount()) / (alienArmy.getSoldierCount())) * 100;
}

int Game::getTimestep()
{
	return timestep;
}

void Game::startGame() {
	char ch = 0;
	while (ch != 27 && (earthArmy.isAlive() && alienArmy.isAlive() || timestep < 40)) { 
		gameTick();
		ch = _getch();
	}
	endGame();
}

void Game::endGame() {
	ofstream outputFile;
	outputFile.open("output.txt", ios::out);
	Unit* deadUnit;
	int Df,Dd,Db;
	int Tj, Ta, Td;
	int countES, countAS, countET, countEG, countAM, countAD, countHU;
	int totalCountES, totalCountAS, totalCountET, totalCountEG, totalCountAM, totalCountAD, totalCountHU;
	int totalInitialEarthCount;
	int totalInitialAlienCount;
	int totalEarthCount;
	int totalAlienCount;
	int earthSumDf,earthSumDd,earthSumDb;
	int alienSumDf,alienSumDd,alienSumDb;
	countES = countAS = countET = countEG = countAM = countAD = countHU = 0;
	earthSumDf = earthSumDd = earthSumDb = alienSumDf = alienSumDd = alienSumDb = 0;
	while (killedUnits.dequeue(deadUnit)) {
		Tj = deadUnit->getJoinTime();
		Ta = deadUnit->getFirstAttackTime();
		Td = deadUnit->getDestructionTime();
		Df = Ta - Tj;
		Dd = Td - Ta;
		Db = Td - Tj;
		outputFile  << Td << '\t'
					<< deadUnit->getId() << '\t'
					<< Tj << '\t'
					<< Df << '\t'
					<< Dd << '\t'
					<< Db << '\n';
		switch (deadUnit->getType()) {
		case ES: ++countES; break;
		case ET: ++countET; break;
		case EG: ++countEG; break;
		case HU: ++countHU; break;
		case AS: ++countAS; break;
		case AM: ++countAM; break;
		case AD: ++countAD; break;
		}
		
		if(deadUnit->isAlien()){
			alienSumDf += Df;
			alienSumDd += Dd;
			alienSumDb += Db;
		} else {
			earthSumDf += Df;
			earthSumDd += Dd;
			earthSumDb += Db;
		}

	}

	string battleResult = ""; // Assume the win state when earth win not alien (but i am sided with aliens :D )
	if (earthArmy.isAlive() && !alienArmy.isAlive())battleResult = "Win";
	else if (!earthArmy.isAlive() && alienArmy.isAlive())battleResult = "Loss";
	else if (!earthArmy.isAlive() && !alienArmy.isAlive())battleResult = "Drawn";
	outputFile << battleResult << '\n';
	totalCountES = earthArmy.getTotalSoldierCount();
	totalCountET = earthArmy.getTotalTankCount();
	totalCountEG = earthArmy.getTotalGunneryCount();
	totalCountHU = earthArmy.getTotalHealCount();
	totalCountAS = alienArmy.getTotalSoldierCount();
	totalCountAM = alienArmy.getTotalMonsterCount();
	totalCountAD = alienArmy.getTotalDroneCount();

	//earth army print
	outputFile  << totalCountES << '\t'
				<< totalCountET << '\t'
				<< totalCountEG << '\t'
				<< totalCountHU << '\n';
	
	outputFile	<< countES * 100.0 / totalCountES << '\t'
				<< countET * 100.0 / totalCountET << '\t'
				<< countEG * 100.0 / totalCountEG << '\t'
				<< countHU * 100.0 / totalCountHU << '\n';

	totalEarthCount = countES + countET + countEG + countHU;
	totalInitialEarthCount = totalCountES + totalCountET + totalCountEG + totalCountHU;
	
	outputFile  << totalEarthCount * 100.0 / totalInitialEarthCount << '\n';
	
	outputFile  <<	double(earthSumDf) / totalEarthCount << '\t'
				<<	double(earthSumDd) / totalEarthCount << '\t'
				<<	double(earthSumDb) / totalEarthCount << '\n'; 

	outputFile  <<	double(earthSumDf) * 100.0 / earthSumDb << '\t'
				<<	double(earthSumDd) * 100.0 / earthSumDb << '\n'; 

	// Alien army print
	outputFile  << totalCountAS << '\t'
				<< totalCountAM << '\t'
				<< totalCountAD << '\n';
	
	outputFile	<< countAS * 100.0 / totalCountAS << '\t'
				<< countAM * 100.0 / totalCountAM << '\t'
				<< countAD * 100.0 / totalCountAD << '\n';

	totalAlienCount = countAS + countAM + countAD;
	totalInitialAlienCount = totalCountAS + totalCountAM + totalCountAD;

	outputFile  << totalAlienCount * 100.0 / totalInitialAlienCount << '\n';
	
	outputFile  <<	double(alienSumDf) / totalAlienCount << '\t'
				<<	double(alienSumDd) / totalAlienCount << '\t'
				<<	double(alienSumDb) / totalAlienCount << '\n'; 

	outputFile  <<	double(alienSumDf) * 100.0 / alienSumDb << '\t'
				<<	double(alienSumDd) * 100.0 / alienSumDb << '\n'; 
				

	outputFile.close();
}

Game::~Game() {
	Unit* unit;
	while (killedUnits.dequeue(unit)) 
	{
		if (unit != nullptr)
			delete unit;
	}
}
