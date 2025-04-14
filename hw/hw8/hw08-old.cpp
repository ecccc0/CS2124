#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
// Forward declaration
class Lord;

// Abstract base class Noble
class Noble {
public:
    Noble(const string& name);
    virtual ~Noble() = default;
    const string& getName() const;
    bool isAlive() const;
    virtual double getStrength() const = 0;
    virtual void reduceStrength(double ratio) = 0;
    virtual void battle(Noble& opponent);
    virtual void defend();
    friend ostream& operator<<(ostream& os, const Noble& noble);
protected:
    string name;
    bool alive;
};

// Abstract base class Protector
class Protector {
public:
    Protector(const string& name, double strength);
    virtual ~Protector() = default;
    const string& getName() const;
    double getStrength() const;
    bool isAlive() const;
    bool isEmployed() const;
    void setEmployer(Lord* newEmployer);
    virtual void defend() const = 0;
    void runaway();
    void reduceStrength(double ratio);
    friend ostream& operator<<(ostream& os, const Protector& protector);
protected:
    string name;
    double strength;
    Lord* employer;
    bool alive;
};

// Derived class Lord
class Lord : public Noble {
public:
    Lord(const string& name);
    bool hires(Protector& protector);
    bool fires(Protector& protector);
    void removeProtector(Protector& protector);
    double getStrength() const override;
    void reduceStrength(double ratio) override;
    void defend() override;
    friend ostream& operator<<(ostream& os, const Lord& lord);
private:
    vector<Protector*> army;
};


// Derived class PersonWithStrengthToFight
class PersonWithStrengthToFight : public Noble {
public:
    PersonWithStrengthToFight(const string& name, double strength);
    double getStrength() const override;
    void reduceStrength(double ratio) override;
    void defend() override;
    friend ostream& operator<< 
        (ostream& os, const PersonWithStrengthToFight& person);

private:
    double strength;
};

Noble::Noble(const string& name) : name(name), alive(true) {}

const string& Noble::getName() const {
    return name;
}

bool Noble::isAlive() const {
    return alive;
}


void Noble::battle(Noble& opponent) {
    cout << name << " battles " << opponent.name << endl;

    if (!alive && !opponent.alive) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
        return;
    }
    if (!alive) {
        cout << "He's dead, " << opponent.name << endl;
        return;
    }
    if (!opponent.alive) {
        cout << "He's dead, " << name << endl;
        return;
    }

    defend();
    opponent.defend();

    double myStrength = getStrength();
    double opponentStrength = opponent.getStrength();

    if (myStrength == opponentStrength) {
        cout << "Mutual Annihilation: " << name << " and " << opponent.name
                  << " die at each other's hands" << endl;
        reduceStrength(1);
        opponent.reduceStrength(1);
        alive = false;
        opponent.alive = false;
    } else if (myStrength > opponentStrength) {
        cout << name << " defeats " << opponent.name << endl;
        double ratio = opponentStrength / myStrength;
        reduceStrength(ratio);
        opponent.reduceStrength(1);
        opponent.alive = false;
    } else {
        cout << opponent.name << " defeats " << name << endl;
        double ratio = myStrength / opponentStrength;
        opponent.reduceStrength(ratio);
        reduceStrength(1);
        alive = false;
    }
}

void Noble::defend() {
    // Base class does nothing
}

ostream& operator<<(ostream& os, const Noble& noble) {
    os << noble.name;
    return os;
}


Protector::Protector(const string& name, double strength)
    : name(name), strength(strength), employer(nullptr), alive(true) {}

const string& Protector::getName() const {
    return name;
}

double Protector::getStrength() const {
    return strength;
}

bool Protector::isAlive() const {
    return alive;
}

bool Protector::isEmployed() const {
    return employer != nullptr;
}

void Protector::setEmployer(Lord* newEmployer) {
    employer = newEmployer;
}

void Protector::runaway() {
    if (employer != nullptr) {
        cout << name << " flees in terror, abandoning his lord, "
            << employer->getName() << endl;
        employer->removeProtector(*this);
        employer = nullptr;
    }
}

void Protector::reduceStrength(double ratio) {
    strength *= (1 - ratio);
    if (strength <= 0) {
        strength = 0;
        alive = false;
    }
}

ostream& operator<<(ostream& os, const Protector& protector) {
    os << protector.name << ": " << protector.strength;
    return os;
}


Lord::Lord(const string& name) : Noble(name) {}

bool Lord::hires(Protector& protector) {
    if (!alive) {
        cout << name << " is dead, cannot hire." << endl;
        return false;
    }
    if (!protector.isAlive()) {
        cout << protector.getName() << " is dead, cannot be hired." << endl;
        return false;
    }
    if (protector.isEmployed()) {
        cout << protector.getName() << " is already employed." << endl;
        return false;
    }
    army.push_back(&protector);
    protector.setEmployer(this);
    return true;
}

bool Lord::fires(Protector& protector) {
    if (!alive) {
        cout << name << " is dead, cannot fire." << endl;
        return false;
    }
    auto it = find(army.begin(), army.end(), &protector);
    if (it != army.end()) {
        army.erase(it);
        protector.setEmployer(nullptr);
        cout << "You don't work for me anymore " << protector.getName()
                  << "! -- " << name << "." << endl;
        return true;
    } else {
        cout << protector.getName() << " is not in the army of " 
            << name << "." << endl;
        return false;
    }
}

void Lord::removeProtector(Protector& protector) {
    auto it = find(army.begin(), army.end(), &protector);
    if (it != army.end()) {
        army.erase(it);
        protector.setEmployer(nullptr);
    }
}

double Lord::getStrength() const {
    double totalStrength = 0;
    for (const Protector* protector : army) {
        if (protector->isAlive())
            totalStrength += protector->getStrength();
    }
    return totalStrength;
}

void Lord::reduceStrength(double ratio) {
    for (Protector* protector : army) {
        if (protector->isAlive())
            protector->reduceStrength(ratio);
    }
}

void Lord::defend() {
    for (Protector* protector : army) {
        if (protector->isAlive())
            protector->defend();
    }
}

ostream& operator<<(ostream& os, const Lord& lord) {
    os << lord.name << " has an army of " << lord.army.size() << endl;
    for (const Protector* protector : lord.army) {
        os << "\t" << *protector << endl;
    }
    return os;
}

// Derived class PersonWithStrengthToFight

PersonWithStrengthToFight::PersonWithStrengthToFight
    (const string& name, double strength) : Noble(name), strength(strength) {}

double PersonWithStrengthToFight::getStrength() const {
    return strength;
}

void PersonWithStrengthToFight::reduceStrength(double ratio) {
    strength *= (1 - ratio);
    if (strength <= 0) {
        strength = 0;
        alive = false;
    }
}

void PersonWithStrengthToFight::defend() {
    if (alive)
        cout << "UGH!!!" << endl;
}

ostream& operator<<(ostream& os, const PersonWithStrengthToFight& person) {
    os << person.name << " has strength: " << person.strength;
    return os;
}

// Derived class Wizard
class Wizard : public Protector {
public:
    Wizard(const string& name, double strength);
    void defend() const override;
};

Wizard::Wizard(const string& name, double strength)
    : Protector(name, strength) {}

void Wizard::defend() const {
    if (alive)
        cout << "POOF" << endl;
}

// Abstract class Warrior
class Warrior : public Protector {
public:
    Warrior(const string& name, double strength);
};

Warrior::Warrior(const string& name, double strength)
    : Protector(name, strength) {}

// Derived class Archer
class Archer : public Warrior {
public:
    Archer(const string& name, double strength);
    void defend() const override;
};

Archer::Archer(const string& name, double strength)
    : Warrior(name, strength) {}

void Archer::defend() const {
    if (alive && employer != nullptr)
        cout << "TWANG! " << name << " says: Take that in the name of my lord, "
                  << employer->getName() << endl;
}

// Derived class Swordsman
class Swordsman : public Warrior {
public:
    Swordsman(const string& name, double strength);
    void defend() const override;
};

Swordsman::Swordsman(const string& name, double strength)
    : Warrior(name, strength) {}

void Swordsman::defend() const {
    if (alive && employer != nullptr)
        cout << "CLANG! " << name << " says: Take that in the name of my lord, "
                  << employer->getName() << endl;
}