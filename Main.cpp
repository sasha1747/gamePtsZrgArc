#include "game.cpp"
using namespace std;

int main() {
	Game game;



















	return 0;


	/*
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
	cout << "fff";
	SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
	printf("Green\n");
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("Green\n");
	*/



	/*
		Scene scene;
		//Forest: battlecruiser, Archon
		//Sand: goliath, zealot
		//Water: InfestedTerran, dragon
		scene.createGameField();
		scene.printGameField();
		Hospital* hospital = scene.createHospital(TerranSquad);
		scene.addHospital(hospital, 4, 5);
		//combatBase base1 = *new combatBase();
		combatBase base1 = scene.createBase();
		Warrior* unitA = base1.createUnit(TerranSquad, Battlecruiser_TRN);
		int x, y;
		cin >> x >> y;
		scene.addUnit(unitA, x, y);
		Warrior* unitB = base1.createUnit(ProtossSquad, Dragoon_PTS);
		cin >> x >> y;
		scene.addUnit(unitB, x, y);
		scene.addBase(&base1, 7, 8);
		//scene.removeBaseHealth(1000, &base1);
		scene.printGameField();
		//scene.removeUnitHealth(1000, terran);
		scene.fight(unitA, unitB);
		scene.printGameField();
		cin >> x >> y;
		scene.removeUnitFromCoord(x, y);
		Scene scene1 = scene;
		scene1.printGameField();
		Iter I = *scene.createIterator(scene.fieldSize);
		//I.next();
		//while (1) {
			//tuple<int, int> check = I.currentItem();
			//I.next();
			//check = I.currentItem();

		//scene.moveUnit(unitA, 3, 7);
		scene.getValueUnitFrom(3, 7);
		scene.printGameField();
		return 0;*/
}