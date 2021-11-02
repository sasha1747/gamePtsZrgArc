#include <string>
#include "Landscape.cpp"

using namespace std;

class Hospital {
public:
	virtual string info() = 0;
	virtual int therapy(Warrior*) = 0;
	virtual bool CanTreatedHere(Warrior*) = 0;
};

class protossHospital :public Hospital {
private:
	bool CanTreatedHere(Warrior* unit) {
		return(unit->info() == "Archon" || unit->info() == "Dragoon");
	}
public:
	string info()override {
		return "protoss Hospital";
	}
	int therapy(Warrior* unit) {
		if (!CanTreatedHere(unit)) {
			cout << "this unit cannot be treated here\n";
			return -1;
		}
		unit->addHealth(unit->getHealth());
		return unit->getHealth();
	}
};

class zergHospital :public Hospital {
private:
	bool CanTreatedHere(Warrior* unit) {
		return(unit->info() == "Infested Terran" || unit->info() == "Zealot");
	}
public:
	string info()override {
		return "zerg Hospital";
	}
	int therapy(Warrior* unit) {
		if (!CanTreatedHere(unit)) {
			cout << "this unit cannot be treated here\n";
			return -1;
		}
		unit->addHealth(unit->getHealth());
		return unit->getHealth();
	}
};

class terranHospital :public Hospital {
private:
	bool CanTreatedHere(Warrior* unit) {
		return(unit->info() == "Battlecruiser" || unit->info() == "Goliath");
	}
public:
	string info()override {
		return "terran Hospital";
	}
	int therapy(Warrior* unit) {
		if (!CanTreatedHere(unit)) {
			cout << "this unit cannot be treated here\n";
			return -1;
		}
		unit->addHealth(unit->getHealth());
		return unit->getHealth();
	}
};
