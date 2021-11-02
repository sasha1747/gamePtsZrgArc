#include "neutralObjects.cpp"
#include "Iter.cpp"
#include <Windows.h>

using namespace std;

class Scene {

private:
	map<tuple<int, int>, Warrior*> unitsOnScene;
	map<tuple<int, int>, combatBase*> basesOnScene;
	map<tuple<int, int>, LandScape*> LandscapesOnScene;
	map<tuple<int, int>, Hospital*> hospitalsOnScene;
	bool check(int i, int j) {
		return(i < fieldSize&& j < fieldSize&& i> 0 && j>0);
	}
	map<string, char>namesOfSmtOnScreen;
	void addRandLandscape(int x, int y) {
		//LandScape* landscape = nullptr;// = new Water;
		int random = rand() % 3;
		//cout << random << endl;
		if (random == 0)
			LandscapesOnScene.insert(make_pair(tuple<int, int>(x, y), new Forest));
		if (random == 1)
			LandscapesOnScene.insert(make_pair(tuple<int, int>(x, y), new Water));
		if (random == 2)
			LandscapesOnScene.insert(make_pair(tuple<int, int>(x, y), new Sand));
	}

	tuple<int, int> findTheCoordinatesOfTheUnit(Warrior* unit) {
		for (auto x : unitsOnScene) {
			if (x.second == unit) {
				return(x.first);
			}
		}
		return(tuple<int, int>(-INF, -INF));
	}

	tuple<int, int> findTheCoordinatesOfTheBase(combatBase* base) {
		for (auto x : basesOnScene) {
			if (x.second == base) {
				return(x.first);
			}
		}
		return(tuple<int, int>(-INF, -INF));
	}

	void moveUnit(Warrior* unit, int x, int y) {//если кто-то был в клетке, в которую мы перемещаем, то этот кто-то удаляется//////////////////////////////
		if (!(check(x, y))) {
			cout << "Incorrect coordinates\n";
			return;
		}
		if (!canBeHere(unit, x, y)) {
			cout << "this unit can't come here- the landscape is not suitable\n";
			return;
		}
		tuple<int, int> st(-INF, -INF);
		for (auto x : unitsOnScene) {
			if (x.second == unit) {
				st = x.first;
				//x.second = nullptr;
				unitsOnScene.erase(x.first);
				break;
			}
		}
		if (st == tuple<int, int>(-INF, -INF))
			cout << "Unit not found\n";
		else
			unitsOnScene[tuple<int, int>(x, y)] = unit;
		return;
	}
public:
	Scene() {
		srand(time(NULL));
	}
	int fieldSize;
	//int si, sj;
	friend class Iter;
	combatBase createBase() {
		return(*new combatBase());
	}
	void createGameField() {
		//srand(time(0));
		std::cout << "Insert coin and specify the size of the playing field:";
		std::cin >> fieldSize;
		for (int i = 0; i < fieldSize; i++) {
			/*if (i == 0 or i == fieldSize - 1) {
				for (int j = 0; j < fieldSize; j++) {
					std::cout << "X ";
				}
				std::cout << "\n";
			}*/
			//else {
			for (int j = 0; j < fieldSize; j++) {
				if (j == 0) {
					//std::cout << "X ";
				}
				else if (j == fieldSize - 1) {
					//std::cout << "X\n";
				}
				else {
					addRandLandscape(i, j);
					//std::cout << "* ";
				}
				//	}
			}
		}
	}

	void printGameField() {
		system("cls");
		for (int i = 0; i < fieldSize; i++) {
			if (i == 0 or i == fieldSize - 1) {
				for (int j = 0; j < fieldSize; j++) {
					std::cout << "X ";
				}
				std::cout << "\n";
			}
			else {
				for (int j = 0; j < fieldSize; j++) {

					if (LandscapesOnScene.count(tuple<int, int>(i, j)) != 0) {
						if (LandscapesOnScene[(tuple<int, int>(i, j))]->info() == "Water") {
							HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
						}
						if (LandscapesOnScene[(tuple<int, int>(i, j))]->info() == "Sand") {
							HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
						}
						if (LandscapesOnScene[(tuple<int, int>(i, j))]->info() == "Forest") {
							HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
						}
					}
					else {
						HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | FOREGROUND_RED);
					}

					if (j == 0) {
						std::cout << "X ";
					}
					else if (j == fieldSize - 1) {
						std::cout << "X\n";
					}
					//namesOfSmtOnScreen["Battlecruiser"] = 'B';
					else if (unitsOnScene.count(tuple<int, int>(i, j)) != 0) {
						if (unitsOnScene[tuple<int, int>(i, j)]->info() == "Battlecruiser")
							std::cout << "B ";
						if (unitsOnScene[tuple<int, int>(i, j)]->info() == "Goliath")
							std::cout << "G ";
						if (unitsOnScene[tuple<int, int>(i, j)]->info() == "Archon")
							std::cout << "A ";
						if (unitsOnScene[tuple<int, int>(i, j)]->info() == "Dragoon")
							std::cout << "D ";
						if (unitsOnScene[tuple<int, int>(i, j)]->info() == "Infested Terran")
							std::cout << "I ";
						if (unitsOnScene[tuple<int, int>(i, j)]->info() == "Zealot")
							std::cout << "Z ";
						//std::cout << "!  ";
					}
					else if (basesOnScene.count(tuple<int, int>(i, j)) != 0) {
						std::cout << "& ";
					}
					else if (hospitalsOnScene.count(tuple<int, int>(i, j)) != 0) {
						std::cout << "+ ";
					}
					else
						std::cout << "* ";
				}
			}
		}
	}

	/*Warrior* createUnit(Squad squad, WarriorType warriorType) {
		auto terranFactory = new TerranFactory;
		auto protossFactory = new ProtossFactory;
		auto zergFactory = new ZergFactory;

		Warrior* battleUnit = 0;

		switch (squad) {
		case TerranSquad:
			battleUnit = (terranFactory->createWarrior(squad, warriorType));
			return battleUnit;
		case ProtossSquad:
			battleUnit = (protossFactory->createWarrior(squad, warriorType));
			return battleUnit;

		case ZergSquad:
			battleUnit = (zergFactory->createWarrior(squad, warriorType));
			return battleUnit;
		}
		return battleUnit;
	};*/


	Hospital* createHospital(Squad squad) {
		Hospital* hospital = 0;
		switch (squad) {
		case TerranSquad:
			hospital = new terranHospital;
			return hospital;
		case ProtossSquad:
			hospital = new protossHospital;
			return hospital;

		case ZergSquad:
			hospital = new zergHospital;
			return hospital;
		}
		return hospital;
	};



	bool canBeHere(Warrior* unit, int x, int y) {
		return(LandscapesOnScene[tuple<int, int>(x, y)]->isItPossibleToPass(unit));
	}
	int addUnit(Warrior* unit, int x, int y) {
		if (!(check(x, y))) {
			cout << "Incorrect coordinates\n";
			return -1;
		}
		if (!canBeHere(unit, x, y)) {
			cout << "this unit can't come here- the landscape is not suitable\n";
			return -1;
		}
		unitsOnScene.insert(make_pair(tuple<int, int>(x, y), unit));
		return 0;
	}

	void addHospital(Hospital* hospital, int x, int y) {
		if (!(check(x, y))) {
			cout << "Incorrect coordinates\n";
			return;
		}

		hospitalsOnScene.insert(make_pair(tuple<int, int>(x, y), hospital));
	}

	void addBase(combatBase* base, int x, int y) {
		if (!(check(x, y))) {
			cout << "Incorrect coordinates\n";
			return;
		}
		basesOnScene.insert(make_pair(tuple<int, int>(x, y), base));
	}


	void totalUnitsOnMap() {
		cout << "Total units on a map: " << unitsOnScene.size() << endl;
	}


	void totalBasesOnMap() {
		cout << "Total bases on a map: " << basesOnScene.size() << endl;
	}


	void totalHospitalsOnMap() {
		cout << "Total hospitals on a map: " << hospitalsOnScene.size() << endl;
	}

	//void totalUnitRemaining() {
		//cout << "Total units remaining: " << (fieldSize - 2) * (fieldSize - 2) - unitsOnScene.size() << endl;
	//}


	/*void allUnitInfo() {
		cout << "Here is all game units: " << endl;
		cout << "__________________________________________" << endl;
		for (auto const& [k, v] : unitsOnScene) {
			std::cout << v->info() << " is available at coordinate: (" << std::get<0>(k) << ", " << std::get<1>(k)
				<< ")" << std::endl;
		}
		cout << "__________________________________________" << endl;
	}*/


	tuple<int, int> coordinate(int x, int y) {
		return tuple<int, int>(x, y);
	}

	void getValueUnitFrom(int x, int y) {
		if (unitsOnScene.count(tuple<int, int>(x, y)) != 0)
			cout << unitsOnScene[tuple<int, int>(x, y)]->info() << endl;
		else
			cout << "There is nothing in this cell\n";
	}


	//void remove() {

		//       for (auto const & [k, v] : unitsOnScene)
		//       {
		//           std::cout << "Coordinate: " << std::get<0>(k) << std::get<1>(k) << " Value: " << v->info() << std::endl;
		//       }
		//
		//      unitsOnScene[changeCoordinateValue(3, 5)] = 0;
	//};

	//coordinate


	int getUnitAttack(Warrior* unit) {
		return unit->getAttack();
	};

	int getUnitArmour(Warrior* unit) {
		return unit->getArmour();
	};

	string getUnitInfo(Warrior* unit) {
		return unit->info();
	};
	int getUnitHealth(Warrior* unit) {
		return(unit->getHealth());
	};
	void removeUnitHealth(int ammount, Warrior* unit) {
		unit->removeHealth(ammount);
		if (getUnitHealth(unit) <= 0) {
			unit->makeMessage("Unit " + getUnitInfo(unit) + " has died\n");
			auto thisUnit = findTheCoordinatesOfTheUnit(unit);
			unitsOnScene.erase(thisUnit);
		}
	};
	int getBaseHealth(combatBase* base) {
		return(base->getHealth());
	};

	void removeBaseHealth(int ammount, combatBase* base) {
		base->removeHealth(ammount);
		if (getBaseHealth(base) <= 0) {
			auto thisBase = findTheCoordinatesOfTheBase(base);
			basesOnScene.erase(thisBase);
			base->eraseObserverInfo();
		}
	}

	void removeBase(combatBase* base) {
		auto thisBase = findTheCoordinatesOfTheBase(base);
		basesOnScene.erase(thisBase);
		base->eraseObserverInfo();
	}

	void removeBaseFromCoord(int i, int j) {
		if (!(check(i, j))) {
			cout << "Incorrect coordinates\n";
			return;
		}
		basesOnScene.erase(tuple<int, int>(i, j));
		basesOnScene[tuple<int, int>(i, j)]->eraseObserverInfo();
	}


	//Iter* createIterator(int Csize) const;
	Iter* createIterator(int cSize)const {
		return new Iter(0, cSize);
	}

	void removeUnit(Warrior* unit) {
		unit->makeMessage("Unit " + getUnitInfo(unit) + "has died\n");
		auto thisUnit = findTheCoordinatesOfTheUnit(unit);
		unitsOnScene.erase(thisUnit);
	};

	void removeUnitFromCoord(int i, int j) {
		if (!(check(i, j))) {
			cout << "Incorrect coordinates\n";
			return;
		}
		unitsOnScene.erase(tuple<int, int>(i, j));
	}

	void fight(Warrior* unitA, Warrior* unitB) {
		Warrior* winner = *unitA % unitB;
		if (winner == nullptr) {
			cout << "draw\n";
			return;
		}
		cout << winner->info() << ' ' << "has win\n";
		if (winner != unitA) {
			//unitB->addHealth(unitA->getHealth());
			removeUnit(unitA);
		}
		else {
			//unitA->addHealth(unitB->getHealth());
			removeUnit(unitB);
		}
	}
	void getTherapy(Warrior* unit, Hospital* hospital) {
		hospital->therapy(unit);
	}
	void step(Warrior* unit, char command) {
		tuple<int, int>coord = findTheCoordinatesOfTheUnit(unit);
		int x, y;
		tie(x, y) = coord;
		if (command == 'w') {
			moveUnit(unit, x - 1, y);
		}
		if (command == 's') {
			moveUnit(unit, x + 1, y);
		}
		if (command == 'd') {
			moveUnit(unit, x, y + 1);
		}
		if (command == 'a') {
			moveUnit(unit, x, y - 1);
		}
	}
	combatBase* getBaseFromCoord(int x, int y) {
		if (!check(x, y)) {
			cout << "Incorrect cord\n";
			return nullptr;
		}
		if (basesOnScene.count(tuple<int, int>(x, y)) == 0) {
			cout << "There's no one here\n";
			return nullptr;
		}
		return(basesOnScene[tuple<int, int>(x, y)]);
	}
	Warrior* getUnitFromCoord(int x, int y) {
		if (!check(x, y)) {
			cout << "Incorrect cord\n";
			return nullptr;
		}
		if (unitsOnScene.count(tuple<int, int>(x, y)) == 0) {
			cout << "There's no one here\n";
			return nullptr;
		}
		return(unitsOnScene[tuple<int, int>(x, y)]);
	}
	Hospital* getHospitalFromCoord(int x, int y) {
		if (!check(x, y)) {
			cout << "Incorrect cord\n";
			return nullptr;
		}
		if (hospitalsOnScene.count(tuple<int, int>(x, y)) == 0) {
			cout << "There's no one here\n";
			return nullptr;
		}
		return(hospitalsOnScene[tuple<int, int>(x, y)]);
	}
	int countOfUnitsOnBase(combatBase* base) {
		return base->getCntOfUnits();
	}
	int maximumCountOfUnitsOnBase(combatBase* base) {
		return base->getMaximumCntOfUnits();
	}
	void getHospitalInfo(Hospital* hospital) {
		cout << hospital->info() << endl;
	}
	/*void allUnitsInfo() {
		for (auto q : unitsOnScene) {
			int x, y;
			tie(x, y) = q.first;
			cout << q.second->info() << "on" << x << ' ' << y << endl;
		}
	}
	void allBasesInfo() {
		for (auto q : basesOnScene) {
			int x, y;
			tie(x, y) = q.first;
			cout << q.second->info() << "on" << x << ' ' << y << endl;
		}
	}*/

	//void getIsUnitDied(Warrior* unit) {
		//if (unit->hasDied()) {
			//tuple<int, int>coord = findTheCoordinatesOfTheUnit(unit);
		//	remove(get<0>(coord), get<1>(coord));
		//}
	//}
};