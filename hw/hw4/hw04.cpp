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
    // output operator 
    friend ostream& operator<<(ostream& os, const Warrior& warrior);
    // getters
    const string& getName() const { return name; }
    double getStrength() const { return strength; }
    bool isHired() const { return hiered; }

    // setters
    void setStrength(double newStrength) { strength = newStrength; }
    void setHired(bool status) { hiered = status; }

private:
    // fields for warrior
    string name;
    double strength;
    bool hiered = false;
    // boolean to check if warrior is hired
};

class Noble {
public:
    Noble(const string& name) : name(name) {}
    // output operator
    friend ostream& operator<<(ostream& os, const Noble& noble);
    // getters
    const string& getName() const { return name; }
    const vector<Warrior*>& getWarriors() const { return warriors; }
    // hire and fire methods
    
    bool hire(Warrior& warrior) {
        if (dead) {
            cout << name << " is dead and cannot hire" << endl;
            return false;
        } // check if noble is dead
        if (warrior.isHired()) {
            cout << name << " failed to hire " << warrior.getName() << endl;
            return false;
        } // check if warrior is hired
        warrior.setHired(true);
        warriors.push_back(&warrior);   
        return true;
        // successfully hired warrior
    }

    bool fire(Warrior& warrior) {
        if (dead) {
            cout << name << " is dead and cannot fire" << endl;
            return false;
        } // check if noble is dead
        for (size_t i = 0; i < warriors.size(); ++i) {
            // loop through warriors to find warrior to fire
            if (warriors[i] == &warrior) {
                cout << warrior.getName() << ", you don't work for me anymore! -- " << name << endl;
                warrior.setHired(false);
                for (size_t j = i; j < warriors.size() - 1; ++j) {
                    warriors[j] = warriors[j + 1];
                } // shift warriors to the left, removing the fired warrior
                warriors.pop_back();
                return true;
            }
        }
        // if warrior is not found
        cout << name << " failed to fire " << warrior.getName() << endl;
        return false;
    }

    // battle method
    void battle(Noble& opponent) {
        cout << name << " battles " << opponent.getName() << endl;

        double strength1 = 0, strength2 = 0, ratio;
        // calculate strength of both nobles's armies
        for (Warrior* warrior : warriors) {
            strength1 += warrior->getStrength();
        }

        for (Warrior* warrior : opponent.getWarriors()) {
            strength2 += warrior->getStrength();
        }
        // dead nobles leads to unccessful battle
        if (dead && opponent.dead) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else if (dead) {
            cout << "He's dead, " << opponent.getName() << endl;
        } else if (opponent.dead) {
            cout << "He's dead, " << name << endl;
        } 

        // successful battles
        // update warrior strengths & noble death status

        // noble 1 wins
        else if (strength1 > strength2) {
            cout << name << " defeats " << opponent.getName() << endl;
            opponent.dead = true;
            ratio = strength2 / strength1;
            for (Warrior* warrior : warriors) {
                warrior->setStrength(warrior->getStrength() * (1 - ratio));
            }
            for (Warrior* warrior : opponent.getWarriors()) {
                warrior->setStrength(0);
            }
        } 
        // noble 2 wins
        else if (strength1 < strength2) {
            cout << opponent.getName() << " defeats " << name << endl;
            dead = true;
            ratio = strength1 / strength2;
            for (Warrior* warrior : opponent.getWarriors()) {
                warrior->setStrength(warrior->getStrength() * (1 - ratio));
            }
            for (Warrior* warrior : warriors) {
                warrior->setStrength(0);
            }
        } 
        // mutual annihilation
        else {
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
    // fields for noble
    string name;
    vector<Warrior*> warriors;
    bool dead = false;
    // boolean to check if noble is dead
};

// output operator for warrior
ostream& operator<<(ostream& os, const Warrior& warrior) {
    os << warrior.getName() << ": " << warrior.getStrength();
    return os;
}
// output operator for noble, using output operator for warrior
ostream& operator<<(ostream& os, const Noble& noble) {
    os << noble.getName() << " has an army of " << noble.getWarriors().size();
    for (Warrior* warrior : noble.getWarriors()) {
        os << endl << "    " << *warrior;
    }
    return os;
}

void status(const vector<Noble*>& nobles);

int main(){
    vector<Noble*> nobles;
    Noble arthur("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble bill("Bill Gates");

    nobles.push_back(&jim);
    nobles.push_back(&lance);
    nobles.push_back(&arthur);
    nobles.push_back(&linus);
    nobles.push_back(&bill);
    

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

// function to print status of all nobles from vector
void status(const vector<Noble*>& nobles) {
    for (const Noble* noble : nobles) {
        cout << *noble << endl;
    }    
}