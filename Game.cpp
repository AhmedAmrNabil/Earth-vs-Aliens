#include "Game.h"
#include <conio.h>
#include <fstream>
#include <windows.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib> 
#include <time.h> 
#include "BattleUnits/EarthSoldier.h"

Game::Game() :RNG(this)
{
	gameMode = INTERACTIVE;
	timestep = 1;
	alienAttacked = true;
	earthAttacked = true;
	infectionCount = 0;
	totalInfectionCount = 0;
	umlsoldier = 0;
	infectionThreshold = 0;
	saverActive = false;
	loadInput();
	srand(time(0));

	//Enabling color support
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);
}

bool Game::isInteractive() {
	return (gameMode == INTERACTIVE);
}

void Game::printarmies()
{
	cout << "\nCurrent Timestep: " << timestep << endl;
	earthArmy.print();
	alienArmy.print();
	allyArmy.print();
}

void Game::printkilledunits()
{
	cout << "\t============== \033[1;31mKilled/Destructed Units\033[0m ============\n";
	cout << "\t" << killedUnits.getCount() << "    units ";
	killedUnits.print();
	cout << endl;
}

void Game::printUML()
{
	cout << "\t============== \033[1;32mUnit Maintenance List\033[0m ==============\n";
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

bool Game::getSaverUnit(Unit*& unit)
{
	return allyArmy.getUnit(SU, unit);
}

bool Game::getfromUML(Unit*& unit)
{
	int pri;
	bool b = UML.dequeue(unit, pri);
	EarthSoldier* soldier = dynamic_cast<EarthSoldier*>(unit);
	if (soldier && (!soldier->isInfected() || soldier->isImmune())) --umlsoldier;
	while (b && timestep - unit->getUMLJoinTime() > 10) {
		unit->decrementHealth(unit->getHealth(), timestep);
		addToKilled(unit);
		b = UML.dequeue(unit, pri);
		soldier = dynamic_cast<EarthSoldier*>(unit);
		if (soldier && (!soldier->isInfected() || soldier->isImmune())) --umlsoldier;
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
bool Game::addSaverUnit(Unit*& unit) {
	return allyArmy.addUnit(unit);
}

bool Game::addAlienUnit(Unit*& unit)
{
	return alienArmy.addUnit(unit);
}

void Game::gameTick() {
	attackedIDs = "";
	bool saverAttacked;
	if (getInfectionPercentage() >= infectionThreshold)
		saverActive = true;
	else if (infectionCount == 0) {
		saverActive = false;
		killAllSaver();
	}
	RNG.generateUnits();
	earthAttacked = earthArmy.attack();
	alienAttacked = alienArmy.attack();
	if (saverActive)
		saverAttacked = allyArmy.attack();
	spreadInfect();
	if (gameMode == INTERACTIVE) {
		printarmies();
		cout << "\t========== Units fighting at current step =========\n";
		cout << attackedIDs;
		printkilledunits();
		printUML();
		cout << "\t===================================================\n";
		cout << "\tCurrent Infection Percentage is " << fixed << setprecision(2) << getInfectionPercentage() << "%" << endl;
	}

	++timestep;
}

void Game::addToAttacked(string ids) {
	attackedIDs += ids;
}


void Game::addToKilled(Unit*& unit)
{
	EarthSoldier* soldier = dynamic_cast<EarthSoldier*>(unit);
	if (soldier && (soldier->isInfected() && !soldier->isImmune())) decrementInfected();
	killedUnits.enqueue(unit);
}

void Game::addToUML(Unit*& unit, int joinUMLtime)
{
	int pri;
	if (unit->getType() == ES) {
		pri = (earthData.maxHealth - unit->getHealth()) * 1000;
		EarthSoldier* soldier = dynamic_cast<EarthSoldier*>(unit);
		if (soldier && (!soldier->isInfected() || soldier->isImmune())) {
			umlsoldier++;
		}
	}
	else pri = -1;
	UML.enqueue(unit, pri);
	unit->setUMLJoinTime(joinUMLtime);
}

void Game::handleUnit(Unit* unit)
{
	if (unit->isDead()) addToKilled(unit);
	else if (unit->isLow()) addToUML(unit, timestep);
	else {
		if (unit->getType() == SU)addSaverUnit(unit);
		else if (unit->isAlien()) addAlienUnit(unit);
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

	input_file >> percentages.percentIf;
	input_file >> infectionThreshold;


	input_file >> allyData.minPower >> allyData.maxPower;
	input_file >> alienData.minHealth >> allyData.maxHealth;
	input_file >> alienData.minCapacity >> allyData.maxCapacity;

	allyData.maxPower *= -1;
	allyData.maxHealth *= -1;
	allyData.maxCapacity *= -1;

	RNG.setData(earthData, alienData, allyData, percentages, N, Prob);

	input_file.close();
}

EarthArmy* Game::getEarthArmy() {
	return &earthArmy;
}
AlienArmy* Game::getAlienArmy() {
	return &alienArmy;
}
AllyArmy* Game::getAllyArmy() {
	return &allyArmy;
}
bool Game::saverIsActive() {
	return saverActive;
}

void Game::incrementInfected()
{
	++infectionCount;
	++totalInfectionCount;
}

void Game::decrementInfected()
{
	--infectionCount;
}

int Game::getAliveSoldiers()
{
	return umlsoldier + earthArmy.getSoldierCount();
}

double Game::getInfectionPercentage()
{
	if (infectionCount == 0 || getAliveSoldiers() == 0) {
		return 0;
	}
	double b = (double(infectionCount) / getAliveSoldiers()) * 100;
	return b;
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
	string option = "";
	cout << "Run The game in interactive or silent mode ? ( [I]nteractive / [S]ilent ): ";
	cin >> option;
	for (int i = 0; i < option.size() && i < 20; ++i)
		option[i] = tolower(option[i]);

	if (option[0] == 'i' || option == "interactive") gameMode = INTERACTIVE;
	else {
		cout << "Silent Mode\nSimulation Starts...\n";
		gameMode = SILENT;
	}
  
	ch = 0;
	while (ch != 27 && (timestep <= 40 || earthArmy.isAlive() && alienArmy.isAlive() && !isDraw())) {
		gameTick();
		if (gameMode == INTERACTIVE)
			ch = _getch();
	}
	endGame();
}

string Game::getRatio(double x, double y) {
	if (y == 0)return "";
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2) << x / y;
	return ss.str();
}

bool Game::isDraw() {
	return !(earthAttacked || alienAttacked ) && (earthArmy.isAlive() && alienArmy.isAlive());
}

bool Game::spreadInfect()
{
	Unit* unit = nullptr;
	if (this->infectionCount < 1) return false;
	int sc = earthArmy.getSoldierCount();
	int random = RNG.generator(0, sc);
	int random2 = RNG.generator(1,100);
	EarthSoldier* s1;
	bool infected = false;

	if (random2 <= 2) 
		for (int i = 0; i < sc; i++) {
			this->getEarthUnit(ES, unit);
			if (i == random) {
				s1 = dynamic_cast<EarthSoldier*>(unit);
				if (!s1->isInfected()) {
					s1->setInfected(true);
					incrementInfected();
				}
			}
			this->addEarthUnit(unit);
		}
	
}

void Game::incrementHealCount(){
	++healCount;
}

void Game::killAllSaver()
{
	Unit* saver;
	while (allyArmy.getUnit(SU, saver)) {
		saver->decrementHealth(saver->getHealth(), timestep);
		addToKilled(saver);
	}
}

void Game::endGame() {
	Unit* temp;
	int pri = 0;
	// Kill the remaining units in the UML
	while (UML.dequeue(temp, pri)) {
		temp->decrementHealth(temp->getHealth(), timestep);
		
		addToKilled(temp);
	}
	ofstream outputFile;
	outputFile.open("output.txt", ios::out);
	Unit* deadUnit = nullptr;
	int Df, Dd, Db;
	int Tj, Ta, Td;
	int countES, countAS, countET, countEG, countAM, countAD, countHU;
	int totalCountES, totalCountAS, totalCountET, totalCountEG, totalCountAM, totalCountAD, totalCountHU;
	int totalInitialEarthCount;
	int totalInitialAlienCount;
	int totalEarthCount;
	int totalAlienCount;
	int earthSumDf, earthSumDd, earthSumDb;
	int alienSumDf, alienSumDd, alienSumDb;
	countES = countAS = countET = countEG = countAM = countAD = countHU = 0;
	earthSumDf = earthSumDd = earthSumDb = alienSumDf = alienSumDd = alienSumDb = 0;
	int killedCount = killedUnits.getCount();
	killedUnits.peek(deadUnit);
	while (killedCount) {
		killedUnits.dequeue(deadUnit);
		Tj = deadUnit->getJoinTime();
		Ta = deadUnit->getFirstAttackTime();
		Td = deadUnit->getDestructionTime();
		Df = Ta - Tj;
		Dd = Td - Ta;
		Db = Td - Tj;

		// Print each killed unit and its properties
		outputFile << Td << "\t\t"
			<< deadUnit->getId() << "\t\t"
			<< Tj << "\t\t"
			<< Df << "\t\t"
			<< Dd << "\t\t"
			<< Db << '\n';

		// Count the number of dead units
		switch (deadUnit->getType()) {
		case ES:  ++countES; break;
		case ET:  ++countET; break;
		case EG:  ++countEG; break;
		case HU:  ++countHU; break;
		case AS:  ++countAS; break;
		case AM:  ++countAM; break;
		case AD:  ++countAD; break;
		}

		if (deadUnit->isAlien()) {
			alienSumDf += Df;
			alienSumDd += Dd;
			alienSumDb += Db;
		}
		else if(deadUnit->getType() != SU) {
			earthSumDf += Df;
			earthSumDd += Dd;
			earthSumDb += Db;
		}
		killedUnits.enqueue(deadUnit); // add the unit again for the destructor
		--killedCount;
	}
	string battleResult = "\nBattle result: "; // Assume the win state when earth win not alien (but i am sided with aliens :D )
	if ((!earthArmy.isAlive() && !alienArmy.isAlive()) || isDraw()) battleResult += "Draw";
	else if (earthArmy.isAlive() && !alienArmy.isAlive()) battleResult += "Win";
	else if (!earthArmy.isAlive() && alienArmy.isAlive()) battleResult += "Loss";

	outputFile << battleResult << '\n';
	
	// Get the total Count for each unit in each army
	totalCountES = earthArmy.getTotalSoldierCount();
	totalCountET = earthArmy.getTotalTankCount();
	totalCountEG = earthArmy.getTotalGunneryCount();
	totalCountHU = earthArmy.getTotalHealCount();
	totalCountAS = alienArmy.getTotalSoldierCount();
	totalCountAM = alienArmy.getTotalMonsterCount();
	totalCountAD = alienArmy.getTotalDroneCount();

	// Earth army print
	outputFile << "\nFor Earth Army:\n";

	// Print the total for each unit
	outputFile << "\tTotal ES: " << totalCountES << "\t"
		<< "Total ET: " << totalCountET << "\t"
		<< "Total EG: " << totalCountEG << "\t"
		<< "Total HU: " << totalCountHU << "\n";

	// Percent dead units per total units
	outputFile << "\tDeadES/TotalES: " << getRatio(countES * 100.0, totalCountES) << "%\t\t"
		<< "DeadET/TotalET: " << getRatio(countET * 100.0, totalCountET) << "%\t\t"
		<< "DeadEG/TotalEG: " << getRatio(countEG * 100.0, totalCountEG) << "%\t\t"
		<< "DeadHU/TotalHU: " << getRatio(countHU * 100.0, totalCountHU) << "%\n";

	totalEarthCount = countES + countET + countEG + countHU;
	totalInitialEarthCount = totalCountES + totalCountET + totalCountEG + totalCountHU;

	// Print total dead units over total earth units
	outputFile << "\tDeadEarthUnits/TotalEarthUnits: " << getRatio(totalEarthCount * 100.0, totalInitialEarthCount) << "%\n";

	// Average first attack delay, destruction delay, battle time
	outputFile << "\tAverage Df: " << getRatio(earthSumDf, totalEarthCount) << "\t\t"
		<< "Average Dd: " << getRatio(earthSumDd, totalEarthCount) << "\t\t"
		<< "Average Db: " << getRatio(earthSumDb, totalEarthCount) << '\n';

	// Percent first attack delay / battle time , destruction delay / battle time
	outputFile << "\tDf/Db: " << getRatio(earthSumDf * 100.0, earthSumDb) << "%\t\t"
		<< "Dd/Db: " << getRatio(earthSumDd * 100.0, earthSumDb) << "%\n";



	// Alien army print
	outputFile << "\nFor Alien Army:\n";

	// Print the total for each unit
	outputFile << "\tTotal AS: " << totalCountAS << "\t"
		<< "Total AM: " << totalCountAM << "\t"
		<< "Total AD: " << totalCountAD << '\n';

	// Percent dead units per total units
	outputFile << "\tDeadAS/TotalAS: " << getRatio(countAS * 100.0, totalCountAS) << "%\t\t"
		<< "DeadAM/TotalAM: " << getRatio(countAM * 100.0, totalCountAM) << "%\t\t"
		<< "DeadAD/TotalAD: " << getRatio(countAD * 100.0, totalCountAD) << "%\n";

	totalAlienCount = countAS + countAM + countAD;
	totalInitialAlienCount = totalCountAS + totalCountAM + totalCountAD;

	// Print total dead units over total alien units
	outputFile << "\tDeadAlienUnits/TotalAlienUnits: " << getRatio(totalAlienCount * 100.0, totalInitialAlienCount) << "%\n";

	// Average first attack delay, destruction delay, battle time
	outputFile << "\tAverage Df: " << getRatio(alienSumDf, totalAlienCount) << "\t\t"
		<< "Average Dd: " << getRatio(alienSumDd, totalAlienCount) << "\t\t"
		<< "Average Db: " << getRatio(alienSumDb, totalAlienCount) << '\n';

	// Percent first attack delay / battle time , destruction delay / battle time
	outputFile << "\tDf/Db: " << getRatio(alienSumDf * 100.0, alienSumDb) << "%\t\t"
		<< "Dd/Db: " << getRatio(alienSumDd * 100.0, alienSumDb) << "%\n";

	// Percent healed unit / total earth units
	outputFile << "\nHealedUnits/TotalEarthUnits: " << getRatio(healCount * 100, totalInitialEarthCount) << "%\n";

	// Percent infected soldiers / total earth soldiers
	outputFile << "\nInfectedSoldier/TotalEarthSoldiers: " << getRatio(totalInfectionCount * 100, totalCountES) << "%\n";

	outputFile.close();
	cout << "Simulation ends, Output file is created\n";
}

Game::~Game() {
	Unit* unit = nullptr;
	killedUnits.peek(unit);
	while (killedUnits.dequeue(unit))
	{
		if (unit != nullptr)
			delete unit;
	}
}
