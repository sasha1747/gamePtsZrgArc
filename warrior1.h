#include <tuple>
#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <list>



using namespace std;
const long long INF = 1e8;

class Observer {
public:
	virtual ~Observer() {};
	virtual void upd(const std::string& message_from_subject) = 0;
	virtual void unitHasDie() = 0;
};

class Subject {
public:
	virtual ~Subject() {};
	virtual void add(Observer* observer) = 0;
	virtual void erase(Observer* observer) = 0;
	virtual void notification() = 0;
};

enum WarriorType {
	Battlecruiser_TRN = 0,
	Goliath_TRN,
	Archon_PTS,
	Dragoon_PTS,
	InfestedTerran_ZRG,
	Zealot_ZRG,
};
enum Squad {
	TerranSquad = 0,
	ProtossSquad,
	ZergSquad,
};


class Warrior :Subject {//1

private:
	std::list<Observer*> observers;
	std::string message;

public:
	void add(Observer* _observer)override {
		observers.push_back(_observer);
	}
	void erase(Observer* _observer)override {
		observers.remove(_observer);
	}
	void notification()override {
		for (auto x : observers) {
			x->unitHasDie();
			x->upd(message);
		}
	}
	string makeMessage(string _message) {
		message = _message;
		notification();
		return message;
	}

	virtual int getHealth() = 0;

	virtual int getArmour() = 0;

	virtual int getAttack() = 0;

	virtual int removeHealth(int) = 0;

	virtual int addHealth(int) = 0;
	virtual string info() = 0;

	virtual WarriorType type() = 0;

	virtual Warrior* operator % (Warrior* unit) = 0;


	virtual ~Warrior() = default;
};//1


class Terran : public Warrior {//2
public:
	Warrior* operator % (Warrior* unit)override {
		if ((unit->getHealth() + unit->getArmour() - this->getAttack()) > (this->getHealth() + this->getArmour() - unit->getAttack())) {
			return unit;
		}
		else if ((unit->getHealth() + unit->getArmour() - this->getAttack()) < (this->getHealth() + this->getArmour() - unit->getAttack())) {
			return this;
		}
		else
			return nullptr;
	}
	Terran() {
		health = 150;
		attack = 150;
		armour = 150;
	}
private:
	int health;
	int attack;
	int armour;

	int getHealth() {
		return health;
	}

	int getAttack() {
		return attack;
	}

	int getArmour() {
		return armour;
	}

	int addHealth(int amount) {
		health += amount;
		return health;
	}

	int removeHealth(int amount) {
		health -= amount;
		return health;
	}


	string info() {
		return "Terran";
	};

};//2

class Battlecruiser : public Terran {//3
public:
	string info() {
		return "Battlecruiser";
	};
	WarriorType type() {
		return Battlecruiser_TRN;
	}
};

class Goliath : public Terran {//3
public:
	string info() {
		return "Goliath";
	};
	WarriorType type() {
		return Goliath_TRN;
	}
};

class Protoss : public Warrior {//2
public:
	Warrior* operator % (Warrior* unit)override {
		if ((unit->getHealth() + unit->getArmour() - this->getAttack()) > (this->getHealth() + this->getArmour() - unit->getAttack())) {
			return unit;
		}
		else if ((unit->getHealth() + unit->getArmour() - this->getAttack()) < (this->getHealth() + this->getArmour() - unit->getAttack())) {
			return this;
		}
		else
			return nullptr;
	}
	Protoss() {
		health = 50;
		attack = 50;
		armour = 50;
	}
private:
	int health;
	int attack;
	int armour;


	int getHealth() {
		return health;
	}

	int getAttack() {
		return attack;
	}

	int getArmour() {
		return armour;
	}

	int addHealth(int amount) {
		health += amount;
		return health;
	}

	int removeHealth(int amount) {
		health -= amount;
		return health;
	}

	string info() {
		return "Protoss";
	};
};

class Archon : public Protoss {//3
public:
	string info() {
		return "Archon";
	};
	WarriorType type() {
		return Archon_PTS;
	}
};

class Dragoon : public Protoss {//3
public:
	string info() {
		return "Dragoon";
	};
	WarriorType type() {
		return Dragoon_PTS;
	}
};

class Zerg : public Warrior {//2
public:
	Zerg() {
		health = 100;
		attack = 100;
		armour = 100;
	}
	Warrior* operator % (Warrior* unit)override {
		if ((unit->getHealth() + unit->getArmour() - this->getAttack()) > (this->getHealth() + this->getArmour() - unit->getAttack())) {
			return unit;
		}
		else if ((unit->getHealth() + unit->getArmour() - this->getAttack()) < (this->getHealth() + this->getArmour() - unit->getAttack())) {
			return this;
		}
		else
			return nullptr;
	}
private:
	int health;
	int attack;
	int armour;

	int getHealth() {
		return health;
	}

	int getAttack() {
		return attack;
	}

	int getArmour() {
		return armour;
	}

	int addHealth(int amount) {
		health += amount;
		return health;
	}

	int removeHealth(int amount) {
		health -= amount;
		return health;
	}

	string info() {
		return "Zerg";
	};
};

class InfestedTerran : public Zerg {//3
public:
	string info() {
		return "Infested Terran";
	};
	WarriorType type() {
		return InfestedTerran_ZRG;
	}
};

class Zealot : public Zerg {//3

public:
	string info() {
		return "Zealot";
	};
	WarriorType type() {
		return Zealot_ZRG;
	}
};





class Factory {
public:
	virtual Warrior* createWarrior(Squad, WarriorType) = 0;

	virtual ~Factory() = default;
};

class TerranFactory : public Factory {
public:
	Warrior* createWarrior(Squad squad, WarriorType type) override {
		switch (squad, type) {
		case (TerranSquad, Battlecruiser_TRN):
			return new Battlecruiser;
		case (TerranSquad, Goliath_TRN):
			return new Goliath;
		}
	}
};

class ProtossFactory : public Factory {
public:
	Warrior* createWarrior(Squad squad, WarriorType type) override {
		switch (squad, type) {
		case (ProtossSquad, Archon_PTS):
			return new Archon;
		case (ProtossSquad, Dragoon_PTS):
			return new Dragoon;
		}
	}
};

class ZergFactory : public Factory {
public:
	Warrior* createWarrior(Squad squad, WarriorType type) override {
		switch (squad, type) {
		case (ZergSquad, InfestedTerran_ZRG):
			return new InfestedTerran;
		case (ZergSquad, Zealot_ZRG):
			return new Zealot;
		}
	}
};



class combatBase :public Observer {

public:
	combatBase(/*Warrior& _subject*/) /*: subject(_subject)*/ {
		//this->subject.add(this);
		health = 100;
		maximumNumberOfUnits = 5;///////
		cntOfUnits = 0;
	}
	void unitHasDie()override {
		cntOfUnits--;
	}
	void upd(const std::string& message_from_subject) override {
		message_from_subject_ = message_from_subject;
		PrintInfo();
	}
	//void RemoveMeFromTheList() {
		//subject.erase(this);
	//}
	void PrintInfo() {
		cout << this->message_from_subject_ << "\n";
	}

	Warrior* createUnit(Squad squad, WarriorType warriorType) {
		if (cntOfUnits >= maximumNumberOfUnits) {
			cout << "the maximum number of units has been created\n";
			return nullptr;
		}
		cntOfUnits++;
		auto terranFactory = new TerranFactory;
		auto protossFactory = new ProtossFactory;
		auto zergFactory = new ZergFactory;

		Warrior* battleUnit = nullptr;

		switch (squad) {
		case TerranSquad:
			battleUnit = (terranFactory->createWarrior(squad, warriorType));
			battleUnit->add(this);
			subjects.insert(battleUnit);
			return battleUnit;
		case ProtossSquad:
			battleUnit = (protossFactory->createWarrior(squad, warriorType));
			battleUnit->add(this);
			subjects.insert(battleUnit);
			return battleUnit;

		case ZergSquad:
			battleUnit = (zergFactory->createWarrior(squad, warriorType));
			battleUnit->add(this);
			subjects.insert(battleUnit);
			return battleUnit;
		}
		cout << "incorrect input\n";
		return battleUnit;
	}
	void eraseObserverInfo() {
		for (auto x : subjects)
			x->erase(this);
	}
	int getHealth() {
		return health;
	}
	int getCntOfUnits() {
		return cntOfUnits;
	}
	int getMaximumCntOfUnits() {
		return maximumNumberOfUnits;
	}
	int removeHealth(int amount) {
		health -= amount;
		return health;
	}
private:
	int health, maximumNumberOfUnits, cntOfUnits;
	string message_from_subject_;
	set<Warrior*> subjects;
};


