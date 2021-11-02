#include "Scene.cpp"
#include "windows.h"
class Game {
private:
	Scene scene;
public:
	Game() {
		//scene = *new Scene;
		startMenu();
	}
	void startMenu() {
		cout << "Exit = 1\nstart new game = 2\n";
		int com;
		cin >> com;
		if (com == 2) {
			game();
		}
		else {
			return;
		}
	}
	void game() {
		scene.createGameField();
		while (true) {
			Sleep(1000);////
			scene.printGameField();
			cout << "\n info = 1\n combat base management = 2\n unit management = 3\n hospital management = 4\n exit = 5 \n ";
			int com;
			cin >> com;
			if (com == 1) {
				scene.printGameField();
				infoMenu();
			}
			if (com == 2) {
				scene.printGameField();
				basesMenu();
			}
			if (com == 3) {
				scene.printGameField();
				unitsMenu();
			}
			if (com == 4) {
				scene.printGameField();
				hospitalsMenu();
			}
			if (com == 5)
				break;
		}
		//system("cls");
		cout << "\n----------------END---------------- \n";
		//Sleep(5000);
		return;
	}
	void infoMenu() {
		cout << "\nTotal units on map = 1\nTotal bases on map = 2\nTotal hospitals on map = 3\n";
		int com;
		cin >> com;
		if (com == 1) {
			scene.totalUnitsOnMap();
		}
		if (com == 2) {
			scene.totalBasesOnMap();
		}
		if (com == 3) {
			scene.totalHospitalsOnMap();
		}
	}

	void unitsMenu() {
		cout << "\n make new unit = 1\n interaction with existing = 2\n";
		int com;
		cin >> com;
		scene.printGameField();
		if (com == 1) {
			cout << "\n enter the coordinates of the base on which you are going to create a unit\n";
			int x, y;
			cin >> x >> y;
			combatBase* base = scene.getBaseFromCoord(x, y);
			Warrior* unit = nullptr;
			if (base == nullptr) {
				cout << "\n incorrect input\n";
			}
			else {
				cout << "\n which squad:\n Protoss = 1\n Zerg = 2\n Terran = 3\n";
				int squad;
				cin >> squad;
				scene.printGameField();
				if (squad == 1) {
					cout << "\n which type:\n Archon = 1\n Dragoon = 2\n";
					int type;
					cin >> type;
					if (type == 1) {
						unit = base->createUnit(ProtossSquad, Archon_PTS);
					}
					if (type == 2) {
						unit = base->createUnit(ProtossSquad, Dragoon_PTS);
					}
				}

				if (squad == 2) {
					cout << "\n which type:\n Zealot = 1\n InfestedTerran = 2\n";
					int type;
					cin >> type;
					if (type == 1) {
						unit = base->createUnit(ZergSquad, Zealot_ZRG);
					}
					if (type == 2) {
						unit = base->createUnit(ZergSquad, InfestedTerran_ZRG);
					}
				}

				if (squad == 3) {
					cout << "\n which type:\n Battlecruiser = 1\n Goliath = 2\n";
					int type;
					cin >> type;
					if (type == 1) {
						unit = base->createUnit(TerranSquad, Battlecruiser_TRN);
					}
					if (type == 2) {
						unit = base->createUnit(TerranSquad, Goliath_TRN);
					}
				}
			}
			if (unit == nullptr) {
				cout << "\n Incorrect input\n";
			}
			else {
				scene.printGameField();
				cout << "\n choose the location of the loyal unit placement\n";
				int x, y;
				cin >> x >> y;
				scene.addUnit(unit, x, y);
			}
		}
		else {
			cout << "\n move = 1\n to be treated = 2\n attack = 3\n health = 4\n armour = 5\n attack = 6\n unit info = 7\n";
			int com;
			cin >> com;
			scene.printGameField();
			cout << "\n Insert coord of unit\n";
			int x, y;
			cin >> x >> y;
			Warrior* unit = scene.getUnitFromCoord(x, y);
			scene.printGameField();
			if (unit != nullptr) {
				if (com == 1) {
					cout << "\n Insert w,a,s, or d to move\n";
					char myStep;
					cin >> myStep;
					scene.step(unit, myStep);
				}
				if (com == 2) {
					cout << "\n Insert coord of hospital\n";
					int hx, hy;
					cin >> hx >> hy;
					Hospital* hospital = scene.getHospitalFromCoord(x, y);
					if (hospital != nullptr) {
						hospital->therapy(unit);
					}
				}
				if (com == 3) {
					cout << "\n enter the coordinates of the unit to attack\n";
					int ax, ay;
					cin >> ax >> ay;
					Warrior* enemyUnit = scene.getUnitFromCoord(x, y);
					if (enemyUnit != nullptr) {
						scene.fight(unit, enemyUnit);
					}
				}
				if (com == 4) {
					cout << scene.getUnitHealth(unit) << endl;
				}
				if (com == 5) {
					cout << scene.getUnitArmour(unit) << endl;
				}
				if (com == 6) {
					cout << scene.getUnitAttack(unit) << endl;
				}
				if (com == 7) {
					cout << scene.getUnitInfo(unit) << endl;
				}
			}
		}
	}
	void basesMenu() {
		cout << "\n create new base = 1\n information for an existing base = 2\n";
		int com;
		cin >> com;
		scene.printGameField();
		if (com == 1) {
			cout << "\n enter the coordinates for the base\n";
			int x, y;
			cin >> x >> y;
			//combatBase base = scene.createBase();
			scene.addBase(new combatBase, x, y);
		}
		if (com == 2) {
			cout << "\n enter the coordinates of the base\n";
			int x, y;
			cin >> x >> y;
			combatBase* base = nullptr;
			base = scene.getBaseFromCoord(x, y);
			if (base != nullptr) {
				cout << "\n how many have already been created = 1\n how many can be created in total = 2\n";
				int func;
				cin >> func;
				if (func == 1) {
					cout << scene.countOfUnitsOnBase(base) << endl;
				}
				if (func == 2) {
					cout << scene.maximumCountOfUnitsOnBase(base) << endl;
				}
			}
		}
	}
	void hospitalsMenu() {
		cout << "\n create hospital = 1\n info = 2 \n";
		int com;
		cin >> com;
		scene.printGameField();
		if (com == 1) {
			cout << "\n insert the coord to add hospital\n";
			int x, y;
			cin >> x >> y;
			scene.printGameField();
			cout << "\n which squad:\n Protoss = 1\n Zerg = 2\n Terran = 3\n";
			int func;
			cin >> func;
			if (func == 1) {
				scene.addHospital(scene.createHospital(ProtossSquad), x, y);
			}
			if (func == 2) {
				scene.addHospital(scene.createHospital(ZergSquad), x, y);
			}
			if (func == 3) {
				scene.addHospital(scene.createHospital(TerranSquad), x, y);
			}
		}
		if (com == 2) {
			cout << "\n insert the coord of hospital\n";
			int x, y;
			cin >> x >> y;
			Hospital* hospital = scene.getHospitalFromCoord(x, y);
			if (hospital != nullptr) {
				scene.getHospitalInfo(hospital);
			}
		}
	}

};