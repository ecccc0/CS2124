/*
 hw07_single.cpp
 Eric Cheung
 Homework 7 single file
 */

// Comment out these two includes for the single file solution
//#include "Noble.h"
//#include "Warrior.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Comment out this "using namespace" for the single file solution
//using namespace WarriorCraft;

// Forward declarations
class Noble;
class Warrior {
    // Private members
    string name;
    double strength;
    bool hired;
    Noble* employer;
public: 

    Warrior(const string& name, double strength);
    // getters & setters
    const string& getName() const;
    double getStrength() const;
    bool isHired() const;
    void setHired(bool hired);
    void setEmployer(Noble* employer);
    // methods
    void runaway();
    friend ostream& operator<<(ostream& os, const Warrior& warrior);
};

class Noble {
    // Private members
    string name;
    double strength;
    vector<Warrior*> warriors;
    bool isAlive;
public: 
    Noble(const string& name);
    const string& getName() const;
    double getStrength() const;
    void hire(Warrior& warrior);
    void fire(Warrior& warrior);
    void battle(Noble& opponent);
    friend ostream& operator<<(ostream& os, const Noble& noble);
};

int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 4);
    Warrior sky("Leia", 6);
    Warrior wizard("Merlin", 9);
    Warrior jaffa("Teal'c", 9);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(jaffa);
    art.hire(cheetah);
    art.hire(wizard);
    art.hire(sky);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(nimoy);

    cout << "================ Initial Status ===============" << endl;
    cout << art << endl
	 << lance << endl
	 << jim << endl
	 << linus << endl
	 << billie << endl;
    cout << "===============================================\n\n";

    art.fire(cheetah);
    wizard.runaway();
    cout << endl << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "\n================ Final Status ===============" << endl;
    cout << art << endl
	 << lance << endl
	 << jim << endl
	 << linus << endl
	 << billie << endl;

    // Tarzan and Merlin should be unemployed
    cout << "Tarzan's Hire Status: " << boolalpha 
	 << cheetah.isHired() << endl;
    cout << "Merlin's Hire Status: " << boolalpha 
	 << wizard.isHired() << endl;
    cout << "===============================================\n\n";
}


// helper function to find the index of a warrior in a vector of warriors
int findWarriorIndex(const vector<Warrior*>& warriors, const Warrior& warrior) {
    for (size_t i = 0; i < warriors.size(); ++i) {
        if (warriors[i] == &warrior) {
            return i;
        }
    }
    return -1; // Not found
}

// gelper function to find a warrior in a vector of warriors
Warrior* findWarrior(vector<Warrior*>& warriors, const Warrior& warrior) {
    if (findWarriorIndex(warriors, warrior) != -1) {
        return warriors[findWarriorIndex(warriors, warrior)];
    }
    return nullptr; // Not found
}

// Warrior class implementation
Warrior::Warrior(const string& name, double strength)
    : name(name), strength(strength), hired(false), employer(nullptr) {}

const string& Warrior::getName() const {
    return name;
}

double Warrior::getStrength() const {
    return strength;
}

bool Warrior::isHired() const {
    return hired;
}

void Warrior::setHired(bool hiredStatus) {
    hired = hiredStatus;
}

void Warrior::setEmployer(Noble* noble) {
    employer = noble;
}

void Warrior::runaway() {
    if (employer) {
        cout << name << " flees in terror, abandoning his lord, " 
             << employer->getName() << endl;
        employer->fire(*this); // Noble handles removing the warrior
        employer = nullptr;
        hired = false;
    }
}

ostream& operator<<(ostream& os, const Warrior& warrior) {
    os << warrior.name << ": " << warrior.strength;
    return os;
}

// Noble class implementation

Noble::Noble(const string& name) : name(name), strength(0) {}

const string& Noble::getName() const {
    return name;
}

double Noble::getStrength() const {
    return strength;
}

void Noble::hire(Warrior& warrior) {
    if (!warrior.isHired()) {
        warriors.push_back(&warrior);
        warrior.setHired(true);
        warrior.setEmployer(this);
        strength += warrior.getStrength();
    }
}

void Noble::fire(Warrior& warrior) {
    // check if noble is alive
    if (isAlive) {
        siez
    }
}

void Noble::battle(Noble& opponent) {
    cout << name << " battles " << opponent.name << endl;

    if (strength == 0 && opponent.strength == 0) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    } else if (strength == 0) {
        cout << "He's dead, " << opponent.name << endl;
    } else if (opponent.strength == 0) {
        cout << "He's dead, " << name << endl;
    } else if (strength > opponent.strength) {
        cout << name << " defeats " << opponent.name << endl;
        double ratio = opponent.strength / strength;
        for (Warrior* warrior : warriors) {
            warrior->setHired(false);
            warrior->setEmployer(nullptr);
        }
        for (Warrior* warrior : opponent.warriors) {
            warrior->setHired(false);
            warrior->setEmployer(nullptr);
        }
    }
}

ostream& operator<<(ostream& os, const Noble& noble) {
    os << noble.name << " has an army of " << noble.warriors.size() << endl;
    for (const Warrior* warrior : noble.warriors) {
        os << "    " << *warrior << endl;
    }
    return os;
}

