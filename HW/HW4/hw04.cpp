#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Noble; // Forward declaration

class Warrior {
public:
    Warrior(const string& name, double strength)
        : name(name), strength(strength), employer(nullptr) {}

    const std::string& getName() const { return name; }
    double getStrength() const { return strength; }
    Noble* getEmployer() const { return employer; }

    void setStrength(double newStrength) { strength = newStrength; }
    void setEmployer(Noble* newEmployer) { employer = newEmployer; }

private:
    string name;
    double strength;
    Noble* employer;
};

class Noble {
public:
    Noble(const string& name) : name(name) {}

    const std::string& getName() const { return name; }
    const vector<Warrior*>& getWarriors() const { return warriors; }

    void hire(Warrior& warrior) {
        if (!warrior.getEmployer()) {
            warriors.push_back(&warrior);
            warrior.setEmployer(this);
        }
    }

    void fire(Warrior& warrior) {
        for (size_t i = 0; i < warriors.size(); ++i) {
            if (warriors[i] == &warrior) {
                warrior.setEmployer(nullptr);
                for (size_t j = i; j < warriors.size() - 1; ++j) {
                    warriors[j] = warriors[j + 1];
                }
                break;
            }
        }
    }

    void battle(Noble& opponent) {
        cout << name << " battles " << opponent.getName() << endl;

        double strength1 = 0;
        for (Warrior* warrior : warriors) {
            strength1 += warrior->getStrength();
        }

        double strength2 = 0;
        for (Warrior* warrior : opponent.getWarriors()) {
            strength2 += warrior->getStrength();
        }

        if (strength1 == 0 && strength2 == 0) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else if (strength1 == 0) {
            cout << "He's dead, " << opponent.getName() << endl;
        } else if (strength2 == 0) {
            cout << "He's dead, " << name << endl;
        } else if (strength1 > strength2) {
            cout << name << " defeats " << opponent.getName() << endl;
            double ratio = strength2 / strength1;
            for (Warrior* warrior : warriors) {
                warrior->setStrength(warrior->getStrength() * (1 - ratio));
            }
            for (Warrior* warrior : opponent.getWarriors()) {
                warrior->setStrength(0);
            }
        } else if (strength1 < strength2) {
            cout << opponent.getName() << " defeats " << name << endl;
            double ratio = strength1 / strength2;
            for (Warrior* warrior : opponent.getWarriors()) {
                warrior->setStrength(warrior->getStrength() * (1 - ratio));
            }
            for (Warrior* warrior : warriors) {
                warrior->setStrength(0);
            }
        } else {
            cout << "Mutual Annihilation: " << name << " and " << opponent.getName() << " die at each other's hands" << endl;
            for (Warrior* warrior : warriors) {
                warrior->setStrength(0);
            }
            for (Warrior* warrior : opponent.getWarriors()) {
                warrior->setStrength(0);
            }
        }
    }
private:
    string name;
    vector<Warrior*> warriors;
};