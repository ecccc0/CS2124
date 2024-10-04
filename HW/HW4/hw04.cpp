/*
Eric Cheung
hw04.cpp
HW4
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Warrior {
public:
    Warrior(const string& name, double strength)
        : name(name), strength(strength) {}

    friend ostream& operator<<(ostream& os, const Warrior& warrior);

    const string& getName() const { return name; }
    double getStrength() const { return strength; }

    void setStrength(double newStrength) { strength = newStrength; }
    bool isHired() const { return hiered; }
    void setHired(bool status) { hiered = status; }

private:
    string name;
    double strength;
    bool hiered = false;
};

class Noble {
public:
    Noble(const string& name) : name(name) {}
    friend ostream& operator<<(ostream& os, const Noble& noble);

    const string& getName() const { return name; }
    const vector<Warrior*>& getWarriors() const { return warriors; }

    bool hire(Warrior& warrior) {
        if (dead) {
            cout << name << " is dead and cannot hire" << endl;
            return false;
        }
        if (warrior.isHired()) {
            cout << name << " failed to hire " << warrior.getName() << endl;
            return false;
        }
        cout << "You're hired, " << warrior.getName() << "! -- " << name << endl;
        warrior.setHired(true);
        warriors.push_back(&warrior);   
        return true;
    }

    bool fire(Warrior& warrior) {
        if (dead) {
            cout << name << " is dead and cannot fire" << endl;
            return false;
        }
        for (size_t i = 0; i < warriors.size(); ++i) {
            if (warriors[i] == &warrior) {
                cout << "You don't work for me anymore " << warrior.getName() << "! -- " << name << endl;
                warrior.setHired(false);
                for (size_t j = i; j < warriors.size() - 1; ++j) {
                    warriors[j] = warriors[j + 1];
                }
                warriors.pop_back();
                return true;
            }
        }
        cout << name << " failed to fire " << warrior.getName() << endl;
        return false;
    }

    void battle(Noble& opponent) {
        cout << name << " battles " << opponent.getName() << endl;

        double strength1 = 0;
        double ratio;
        for (Warrior* warrior : warriors) {
            strength1 += warrior->getStrength();
        }

        double strength2 = 0;
        for (Warrior* warrior : opponent.getWarriors()) {
            strength2 += warrior->getStrength();
        }

        if (dead && opponent.dead) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else if (dead) {
            cout << "He's dead, " << opponent.getName() << endl;
        } else if (opponent.dead) {
            cout << "He's dead, " << name << endl;
        } else if (strength1 > strength2) {
            cout << name << " defeats " << opponent.getName() << endl;
            opponent.dead = true;
            ratio = strength2 / strength1;
            for (Warrior* warrior : warriors) {
                warrior->setStrength(warrior->getStrength() * (1 - ratio));
            }
            for (Warrior* warrior : opponent.getWarriors()) {
                warrior->setStrength(0);
            }
        } else if (strength1 < strength2) {
            cout << opponent.getName() << " defeats " << name << endl;
            dead = true;
            ratio = strength1 / strength2;
            for (Warrior* warrior : opponent.getWarriors()) {
                warrior->setStrength(warrior->getStrength() * (1 - ratio));
            }
            for (Warrior* warrior : warriors) {
                warrior->setStrength(0);
            }
        } else {
            cout << "Mutual Annihilation: " << name << " and " << opponent.getName() << " die at each other's hands" << endl;
            dead = true;
            opponent.dead = true;
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
    bool dead = false;
};

ostream& operator<<(ostream& os, const Warrior& warrior) {
    os << warrior.getName() << ": " << warrior.getStrength();
    return os;
}

ostream& operator<<(ostream& os, const Noble& noble) {
    os << noble.getName() << " has an army of " << noble.getWarriors().size();
    for (Warrior* warrior : noble.getWarriors()) {
        os << endl << "    " << *warrior;
    }
    return os;
}

void status(const vector<Noble>& nobles);

int main(){
    vector<Noble> nobles;
    Noble arthur("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble bill("Bill Gates");

    nobles.push_back(arthur);
    nobles.push_back(lance);
    nobles.push_back(jim);
    nobles.push_back(linus);
    nobles.push_back(bill);
    

    Warrior tarzan("Tarzan", 10);
    Warrior merlin("Merlin", 15);
    Warrior conan("Conan", 12);
    Warrior spock("Spock", 15);
    Warrior xena("Xena", 20);
    Warrior hulk("Hulk", 8);
    Warrior hercules("Hercules", 3);

    jim.hire(spock);
    arthur.hire(spock);
    lance.hire(conan);
    lance.hire(hercules);
    arthur.hire(merlin);
    arthur.hire(tarzan);
    linus.hire(xena);
    bill.hire(hulk);

    cout << "==========" << endl;

    cout << endl << "Status before all battles, etc." << endl;
    status(nobles);

    cout << "==========" << endl;
    
    arthur.fire(tarzan);
    cout << arthur << endl;
    lance.fire(spock);
    cout << lance << endl;
    cout << "==========" << endl << endl;

    arthur.battle(lance);
    jim.battle(lance);
    linus.battle(bill);
    bill.battle(lance);
    cout << "==========" << endl << endl;

    cout << "Status after all battles, etc." << endl;
    status(nobles);
    return 0;
}

void status(const vector<Noble>& nobles) {
    for (const Noble& noble : nobles) {
        cout << noble << endl;
        for (const Warrior* warrior : noble.getWarriors()) {
            cout << *warrior << endl;
        }
    }    
}