#include <tuple>
#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <list>

#include "warrior1.h"

using namespace std;



class LandScape {
public:
	virtual string info() = 0;
	virtual bool isItPossibleToPass(Warrior*) = 0;
};

class Forest :public LandScape {
private:
	set<WarriorType>whoCanNotBeHere;
public:
	Forest() {
		whoCanNotBeHere.insert(Battlecruiser_TRN);
		whoCanNotBeHere.insert(Archon_PTS);
	}
	bool isItPossibleToPass(Warrior* unit)override {
		return(!(whoCanNotBeHere.count(unit->type())));
	}
	string info()override {
		return"Forest";
	}
};

class Sand :public LandScape {
private:
	set<WarriorType>whoCanNotBeHere;
public:
	Sand() {
		whoCanNotBeHere.insert(Goliath_TRN);
		whoCanNotBeHere.insert(Zealot_ZRG);
	}
	bool isItPossibleToPass(Warrior* unit)override {
		return(!(whoCanNotBeHere.count(unit->type())));
	}
	string info()override {
		return"Sand";
	}
};

class Water :public LandScape {
private:
	set<WarriorType>whoCanNotBeHere;
public:
	Water() {
		whoCanNotBeHere.insert(InfestedTerran_ZRG);
		whoCanNotBeHere.insert(Dragoon_PTS);
	}
	bool isItPossibleToPass(Warrior* unit)override {
		return(!(whoCanNotBeHere.count(unit->type())));
	}
	string info()override {
		return"Water";
	}
};