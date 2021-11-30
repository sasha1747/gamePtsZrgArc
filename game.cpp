#include "Scene.cpp"
#include "windows.h"
#include "logs.cpp"
using namespace std;
class Game {
private:
	Scene scene;
	Caretaker* caretaker;
public:
	MyLog* log;
	Game() {
		log = new MyLog;
		scene = *new Scene;
		caretaker = new Caretaker(&scene);
		startMenu();
	}
	void startMenu() {
		cout << "Exit = 1\nstart new game = 2\n";
		int com;
		cin >> com;
		if (com == 2) {
			log->makeNewLog("user: start new game");
			game();
		}
		else {
			log->makeNewLog("user: Exit");
			return;
		}
	}
	void game() {
		string sizeOfField = scene.createGameField();
		log->makeNewLog("the user created a field with the size: " + sizeOfField + " X " + sizeOfField);
		while (true) {
			Sleep(1000);////
			scene.printGameField();
			cout << "\n info = 1\n combat base management = 2\n unit management = 3\n hospital management = 4\n exit = 5 \n save = 6\n take last save = 7\n ";
			int com;
			cin >> com;
			if (com == 1) {
				log->makeNewLog("user: info");
				scene.printGameField();
				infoMenu();
			}
			if (com == 2) {
				log->makeNewLog("user: combat base management");
				scene.printGameField();
				basesMenu();
			}
			if (com == 3) {
				log->makeNewLog("user: unit management");
				scene.printGameField();
				unitsMenu();
			}
			if (com == 4) {
				log->makeNewLog("user: hospital management");
				scene.printGameField();
				hospitalsMenu();
			}
			if (com == 5) {
				log->makeNewLog("user: exit");
				break;
			}
			if (com == 6) {
				log->makeNewLog("user: save");
				caretaker->backup();
				//cout<<"\n DONE \n;"
			}
			if (com == 7) {
				log->makeNewLog("user: take last save");
				caretaker->lastFromHistory();
			}
		}
		//system("cls");
		cout << "\n----------------END---------------- \n";
		//log->outputLogs();
		Log* adaptLog = new Adapter(log);
		cout << "\nwhere to output logs\nConsole = 1\nlog.txt = 2\n";
		int comm;
		cin >> comm;
		pair<string, string>  res = adaptLog->printLog(comm);
		ofstream fout;
		fout.open(res.second);
		fout << res.first;
		/*if (comm == 1) {
			system("pause");
		}*/
		//Sleep(5000);
		return;
	}
	void infoMenu() {
		cout << "\nTotal units on map = 1\nTotal bases on map = 2\nTotal hospitals on map = 3\n";
		int com;
		cin >> com;
		if (com == 1) {
			log->makeNewLog("user: Total units on map");
			scene.totalUnitsOnMap();
		}
		if (com == 2) {
			log->makeNewLog("user: Total bases on map");
			scene.totalBasesOnMap();
		}
		if (com == 3) {
			log->makeNewLog("user: Total hospitals on map");
			scene.totalHospitalsOnMap();
		}
	}

	void unitsMenu() {
		cout << "\n make new unit = 1\n interaction with existing = 2\n";
		int com;
		cin >> com;
		scene.printGameField();
		if (com == 1) {
			log->makeNewLog("user: make new unit");
			cout << "\n enter the coordinates of the base on which you are going to create a unit\n";
			log->makeNewLog("user: enter the coordinates of the new base");
			int x, y;
			cin >> x >> y;
			combatBase* base = scene.getBaseFromCoord(x, y);
			Warrior* unit = nullptr;
			if (base == nullptr) {
				log->makeNewLog("user: entered incorrect coordinates");
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
						log->makeNewLog("user: entered Archon_PTS");
					}
					if (type == 2) {
						unit = base->createUnit(ProtossSquad, Dragoon_PTS);
						log->makeNewLog("user: entered Dragoon_PTS");

					}
				}

				if (squad == 2) {
					cout << "\n which type:\n Zealot = 1\n InfestedTerran = 2\n";
					int type;
					cin >> type;
					if (type == 1) {
						unit = base->createUnit(ZergSquad, Zealot_ZRG);
						log->makeNewLog("user: entered Zealot_ZRG");
					}
					if (type == 2) {
						unit = base->createUnit(ZergSquad, InfestedTerran_ZRG);
						log->makeNewLog("user: entered InfestedTerran_ZRG");
					}
				}

				if (squad == 3) {
					cout << "\n which type:\n Battlecruiser = 1\n Goliath = 2\n";
					int type;
					cin >> type;
					if (type == 1) {
						unit = base->createUnit(TerranSquad, Battlecruiser_TRN);
						log->makeNewLog("user: entered Battlecruiser_TRN");
					}
					if (type == 2) {
						unit = base->createUnit(TerranSquad, Goliath_TRN);
						log->makeNewLog("user: entered Goliath_TRN");
					}
				}
			}
			if (unit == nullptr) {
				cout << "\n Incorrect input\n";
				log->makeNewLog("user: entered incorrect input");
			}
			else {
				scene.printGameField();
				cout << "\n choose the location of the loyal unit placement\n";
				int x, y;
				cin >> x >> y;
				log->makeNewLog("user: entered coordinates of unit");
				if (scene.addUnit(unit, x, y) != -1)
					log->makeNewLog(unit->info() + ": located at the coordinates entered by the user");
				else
					log->makeNewLog("user: entered incorrect input");
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
			log->makeNewLog("user: entered the coordinates of the unit he wants to interact with");
			Warrior* unit = scene.getUnitFromCoord(x, y);
			scene.printGameField();
			if (unit != nullptr) {
				if (com == 1) {
					log->makeNewLog("user: entered the coordinates of the unit he wants to interact with");
					cout << "\n Insert w,a,s, or d to move\n";
					char myStep;
					cin >> myStep;
					scene.step(unit, myStep);
				}
				if (com == 2) {
					log->makeNewLog("user: to be treated the unit");
					cout << "\n Insert coord of hospital\n";
					int hx, hy;
					cin >> hx >> hy;
					Hospital* hospital = scene.getHospitalFromCoord(x, y);
					if (hospital != nullptr) {
						hospital->therapy(unit);
						log->makeNewLog(unit->info() + " : to be treated on hospital " + hospital->info());
					}
				}
				if (com == 3) {
					log->makeNewLog("user: to be attack the unit");
					cout << "\n enter the coordinates of the unit to attack\n";
					int ax, ay;
					cin >> ax >> ay;
					Warrior* enemyUnit = scene.getUnitFromCoord(x, y);
					if (enemyUnit != nullptr) {
						log->makeNewLog(scene.fight(unit, enemyUnit));
					}
				}
				if (com == 4) {
					log->makeNewLog("user: get unit health");
					cout << scene.getUnitHealth(unit) << endl;
				}
				if (com == 5) {
					log->makeNewLog("user: get unit Armour");
					cout << scene.getUnitArmour(unit) << endl;
				}
				if (com == 6) {
					log->makeNewLog("user: get unit Attack");
					cout << scene.getUnitAttack(unit) << endl;
				}
				if (com == 7) {
					log->makeNewLog("user: get unit Info");
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
			log->makeNewLog("user: create new base");
			cout << "\n enter the coordinates for the base\n";
			int x, y;
			cin >> x >> y;
			log->makeNewLog("user: enter the coordinates for the new base");
			//combatBase base = scene.createBase();
			scene.addBase(new combatBase, x, y);
		}
		if (com == 2) {
			log->makeNewLog("user: information for an existing base");
			cout << "\n enter the coordinates of the base\n";
			log->makeNewLog("user: enter the coordinates for the existing base");
			int x, y;
			cin >> x >> y;
			combatBase* base = nullptr;
			base = scene.getBaseFromCoord(x, y);
			if (base != nullptr) {
				cout << "\n how many have already been created = 1\n how many can be created in total = 2\n";
				int func;
				cin >> func;
				if (func == 1) {
					log->makeNewLog("user: how many have already been created");
					cout << scene.countOfUnitsOnBase(base) << endl;
				}
				if (func == 2) {
					log->makeNewLog("user: how many can be created in total");
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
			log->makeNewLog("user: create hospital ");
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
				log->makeNewLog("user: get hospital info");
				scene.getHospitalInfo(hospital);
			}
		}
	}

};