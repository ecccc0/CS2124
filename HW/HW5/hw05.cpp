/*
Eric Cheung
hw05.cpp
HW5
*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
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
                cout << warrior.getName() 
                    << ", you don't work for me anymore! -- " << name << endl;
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

        for (Warrior* warrior : opponent.warriors) {
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
            for (Warrior* warrior : opponent.warriors) {
                warrior->setStrength(0);
            }
        } 
        // noble 2 wins
        else if (strength1 < strength2) {
            cout << opponent.getName() << " defeats " << name << endl;
            dead = true;
            ratio = strength1 / strength2;
            for (Warrior* warrior : opponent.warriors) {
                warrior->setStrength(warrior->getStrength() * (1 - ratio));
            }
            for (Warrior* warrior : warriors) {
                warrior->setStrength(0);
            }
        } 
        // mutual annihilation
        else {
            cout << "Mutual Annihilation: " << name << " and " 
                << opponent.getName() << " die at each other's hands" << endl;
            dead = true;
            opponent.dead = true;
            for (Warrior* warrior : warriors) {
                warrior->setStrength(0);
            }
            for (Warrior* warrior : opponent.warriors) {
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
    os << noble.getName() << " has an army of " << noble.warriors.size();
    for (Warrior* warrior : noble.warriors) {
        os << endl << "    " << *warrior;
    }
    return os;
}

// function prototypes for commands
void status(const vector<Noble*>& nobles, const vector<Warrior*>& warriors);
Noble* noble(const string& name);
Warrior* warrior(const string& name, double strength);
bool hire(const string& nobleName, const string& warriorName
    , vector<Noble*>& nobles, vector<Warrior*>& warriors);
bool fire(const string& nobleName, const string& warriorName
    , vector<Noble*>& nobles, vector<Warrior*>& warriors);
void battle(const string& nobleName1
    , const string& nobleName2, vector<Noble*>& nobles);
void clear(vector<Noble*>& nobles, vector<Warrior*>& warriors);

int main(){
    vector<Noble*> nobles;
    vector<Warrior*> warriors;
    string command, name, nobleName, warriorName, nobleName1, nobleName2;
    double strength;
    ifstream fin;
    bool duplicateNoble, duplicateWarrior;
    fin.open("nobleWarriors.txt");
    // read commands from file
    while (fin >> command) {
        duplicateNoble = false;
        duplicateWarrior = false;
        if (command == "Noble") {
            fin >> name;
            for (Noble* noble : nobles) {
                if (noble->getName() == name) {
                    cout << "Attempting to create duplicate noble: " 
                        << name << endl;
                    duplicateNoble = true;
                    break;
                } // check for duplicate noble
            }
            if (!duplicateNoble){
                nobles.push_back(noble(name));
            }

        } else if (command == "Warrior") {
            fin  >> name >> strength;
            for (Warrior* warrior : warriors) {
                if (warrior->getName() == name) {
                    cout << "Attempting to create duplicate warrior: " 
                        << name << endl;
                    duplicateWarrior = true;
                    break;
                }
            } // check for duplicate warrior
            if (!duplicateWarrior) {
                warriors.push_back(warrior(name, strength));
            }
        } else if (command == "Hire") {
            fin >> nobleName >> warriorName;
            hire(nobleName, warriorName, nobles, warriors); 
            // call hire function that calls noble hire method
        } else if (command == "Fire") {
            fin >> nobleName >> warriorName;
            fire(nobleName, warriorName, nobles, warriors); 
            // call fire function that calls noble fire method
        } else if (command == "Battle") {
            fin >> nobleName1 >> nobleName2;
            battle(nobleName1, nobleName2, nobles); 
            // call battle function that calls noble battle method
        } else if (command == "Status") {
            status(nobles, warriors);
        } else if (command == "Clear") {
            clear(nobles, warriors);
        }
    }
    return 0;
}

void status(const vector<Noble*>& nobles, const vector<Warrior*>& warriors) {
    cout << "Status" << endl << "======" << endl << "Nobles:" << endl;
    if (nobles.size() == 0) {
        cout << "NONE" << endl;
    } else {
        for (Noble* noble : nobles) {
            cout << *noble << endl;
        }
    }
    cout << endl;
    bool allHired = true;
    cout << "Unemployed Warriors:" << endl;
    for (Warrior* warrior : warriors) {
        if (!warrior->isHired()) {
            allHired = false;
            cout << "    " << *warrior << endl;
        }
    } // check if all warriors are hired
    if (allHired) {
        cout << "NONE" << endl;
    }
}

Noble* noble(const string& name) {
    Noble* noble = new Noble(name);
    return noble;
    // errors handled in main
}

Warrior* warrior(const string& name, double strength) {
    Warrior* warrior = new Warrior(name, strength);
    return warrior;
    // errors handled in main
}

bool hire(const string& nobleName, const string& warriorName
    , vector<Noble*>& nobles, vector<Warrior*>& warriors) {
    for (Noble* noble : nobles) {
        if (noble->getName() == nobleName) {
            for (Warrior* warrior : warriors) {
                if (warrior->getName() == warriorName) {
                    return noble->hire(*warrior);
                }
            }
            cout << "Attempting to hire using unknown warrior: " << warriorName << endl;
        }
    }
    cout << "Attempting to hire using unknown noble: " << nobleName << endl;
    // only check for unknown warrior, noble. Other errors handled in Noble hire method
    return false;
}

bool fire(const string& nobleName, const string& warriorName
    , vector<Noble*>& nobles, vector<Warrior*>& warriors) {
    for (Noble* noble : nobles) {
        if (noble->getName() == nobleName) {
            for (Warrior* warrior : warriors) {
                if (warrior->getName() == warriorName) {
                    return noble->fire(*warrior);
                }
            }
            cout << "Attempting to fire unknown warrior: " 
                << warriorName << endl;
        }
    }
    cout << "Attempting to fire using unknown noble: " << nobleName << endl;
    // Only check for unknown warrior, noble. 
    // Other errors handled in Noble fire method
    return false;
}

void battle(const string& nobleName1, const string& nobleName2
    , vector<Noble*>& nobles) {
    for (Noble* noble1 : nobles) {
        if (noble1->getName() == nobleName1) {
            for (Noble* noble2 : nobles) {
                if (noble2->getName() == nobleName2) {
                    noble1->battle(*noble2);
                    return;
                }
            }
            cout << "Attempting to battle using unknown noble: " 
                << nobleName2 << endl;
        }
    }
    cout << "Attempting to battle using unknown noble: " 
        << nobleName1 << endl;
    // only check for unknown noble. Other errors handled in Noble battle method
    return;
}

void clear(vector<Noble*>& nobles, vector<Warrior*>& warriors) {
    // delete all used memory on heap
    for (Noble* noble : nobles) {
        delete noble;
    }
    for (Warrior* warrior : warriors) {
        delete warrior;
    }
    nobles.clear();
    warriors.clear();
}