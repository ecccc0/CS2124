#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Forward declaration
class Warrior;

class Noble {
public:
    // declared methods, defined later
    void updateStrength();

    friend ostream& operator<<(ostream& os, const Noble& noble);

    Noble(const string& name);

    void display() const;

    void hire(Warrior& warrior);

    void fire(Warrior& warrior);

    void removeWarrior(Warrior* warrior);
    
    const string& getName() const;

    void battle(Noble& other);
private:
    // private fields
    string name;
    vector<Warrior*> army;
    bool isAlive;
    int strength;
};

class Warrior {
public:
    // declared methods, defined later
    friend ostream& operator<<(ostream& os, const Warrior& warrior);

    Warrior(const string& name, int strength); 

    void display() const;

    void setStrength(int newStrength);

    int getStrength() const;

    const string& getName() const;

    void setEmployer(Noble* noble);

    void runaway();

    Noble* getEmployer() const;

    bool isHired() const;
private:
    // private fields
    Noble* employer;
    string name;
    int strength;
};

// helper function to find the index of a warrior in a vector of warriors
size_t findWarriorIndex(const vector<Warrior*>& warriors, const string& name) {
    for (size_t i = 0; i < warriors.size(); i++) {
        if (warriors[i]->getName() == name) {
            return i;
        }
    }
    return -1;
}
// helper function to find a warrior in a vector of warriors
Warrior* findWarrior(const vector<Warrior*>& warriors, const string& name) {
    if (findWarriorIndex(warriors, name) != -1) {
        return warriors[findWarriorIndex(warriors, name)];
    }
    return nullptr;
}
// output operator for Warrior
ostream& operator<<(ostream& os, const Warrior& warrior) {
    os << warrior.getName() << ": " << warrior.getStrength();
    return os;
}
// output operator for Noble
ostream& operator<<(ostream& os, const Noble& noble) {
    os << noble.getName() << " has an army of " << noble.army.size() << endl;
    for (Warrior* warrior : noble.army) {
        os << *warrior << endl;
    }
    return os;
}
// method to update the strength of a noble, called in battle
void Noble::updateStrength() {
    double newStrength = 0;
    for (Warrior* warrior : army) {
        newStrength += warrior->getStrength(); 
    }
    strength = newStrength;
} 


// noble constructor
Noble::Noble(const string& name) : name(name), isAlive(true), strength(0) {}

// noble hire method
void Noble::hire(Warrior& warrior) {
    // check if noble is alive
    if (isAlive) {
        // check if warrior is already hired
        if (!warrior.isHired()) {
            army.push_back(&warrior);
            warrior.setEmployer(this);
            strength += warrior.getStrength();
            // update strength
        } else {
            cout << "Warrior already has an employer." << endl;
        }
    } else {
        cout << name << " is dead." << endl;
    }
}

// noble fire method
void Noble::fire(Warrior& warrior) {
    // check if noble is alive
    if (isAlive) {
        // find the warrior in the army
        size_t index = findWarriorIndex(army, warrior.getName());
        army[index] = army[army.size() - 1];
        army.pop_back();
        warrior.setEmployer(nullptr);
        // swap the warrior with the last warrior in the army
        // , then pop the last warrior
        strength -= warrior.getStrength();
        // update strength
    } else {
        cout << name << " is dead." << endl;
    }
}
// noble remove warrior method
void Noble::removeWarrior(Warrior* warrior) {
    // find the warrior in the army
    size_t index = findWarriorIndex(army, warrior->getName());
    army[index] = army[army.size() - 1];
    army.pop_back();
    warrior->setEmployer(nullptr);
    // swap the warrior with the last warrior in the army
    // , then pop the last warrior
    strength -= warrior->getStrength();
    // update strength
}

// noble getName method
const string& Noble::getName() const {
    return name;
}

// noble battle method
void Noble::battle(Noble& other) {
    cout << name << " battles " << other.name << endl;
    // check if both nobles are dead
    if (!isAlive && !other.isAlive) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    } else if (!isAlive) {
        cout << "He's dead, " << other.name << endl;
    } else if (!other.isAlive) {
        cout << "He's dead, " << name << endl;
    } else if (strength == other.strength) {
        cout << "Mutual Annihilation: " << name << " and "
            << other.name << " die at each other's hands" << endl;
        isAlive = false;
        other.isAlive = false;
        strength = 0;
        other.strength = 0;
        for (Warrior* warrior : army) {
            warrior->setStrength(0);
        }
        for (Warrior* warrior : other.army) {
            warrior->setStrength(0);
        }
        // set all warriors' strength to 0
    } else if (strength > other.strength) {
        cout << name << " defeats " << other.name << endl;
        double ratio = (double) (other.strength) / strength;
        for (Warrior* warrior : other.army) {
            warrior->setStrength(0);
        }
        other.strength = 0;
        for (Warrior* warrior : army) {
            warrior->setStrength(warrior->getStrength() * (1 - ratio));
        }
        updateStrength();
        // update strength of the winning noble
        other.isAlive = false;
    } else {
        cout << other.name << " defeats " << name << endl;
        double ratio = (double) (strength) / other.strength;
        for (Warrior* warrior : army) {
            warrior->setStrength(0);
        }
        strength = 0;
        for (Warrior* warrior : other.army) {
            warrior->setStrength(warrior->getStrength() * (1 - ratio));
        }
        other.updateStrength();
        isAlive = false;
    }
}

// warrior constructor
Warrior::Warrior(const string& name, int strength)
    : name(name), strength(strength), employer(nullptr) {}

// warrior display method
void Warrior::setStrength(int newStrength) {
    strength = newStrength;
}
// warrior getStrength method
int Warrior::getStrength() const {
    return strength;
}
// warrior getName method
const string& Warrior::getName() const {
    return name;
}
// warrior setEmployer method
void Warrior::setEmployer(Noble* noble) {
    employer = noble;
}
// warrior runaway method
void Warrior::runaway() {
    if (strength == 0) {
        // check if warrior is dead
        cout << name << "is dead" << endl;
        return;
    }
    if (!isHired()) {
        // check if warrior is unemployed
        cout << name << " is unemployed" << endl;
        return;
    }
    employer->removeWarrior(this);
    employer = nullptr;
    // remove warrior from employer's army, set employer to nullptr
}
// warrior getEmployer method
Noble* Warrior::getEmployer() const {
    return employer;
}
// warrior isHired method
bool Warrior::isHired() const {
    return employer != nullptr;
}
