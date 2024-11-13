#include <iostream>
#include <string>
#include <vector>
#include "Noble.h"
#include "Warrior.h"


namespace WarriorCraft {
    // helper function to update the strength of a noble, called in battle
    void Noble::updateStrength() {
        double newStrength = 0;
        for (Warrior* warrior : army) {
            newStrength += warrior->getStrength(); 
        }
        strength = newStrength;
    }

    // helper function to find the index of a warrior in a vector of warriors
    size_t findWarriorIndex(const std::vector<Warrior*>& warriors,
        const std::string& name) {
        for (size_t i = 0; i < warriors.size(); i++) {
            if (warriors[i]->getName() == name) {
                return i;
            }
        }
        return -1;
    }

    // constructor for the Noble class
    Noble::Noble(const std::string& name) 
        : name(name), isAlive(true), strength(0) {}
    // method to hire a warrior 
    void Noble::hire(Warrior& warrior) {
        if (isAlive) {
            if (warrior.getEmployer() == nullptr) {
                army.push_back(&warrior);
                warrior.setEmployer(this);
                strength += warrior.getStrength();
            } else {
                std::cout << "Warrior already has an employer." << std::endl;
            }
        } else {
            std::cout << name << " is dead." << std::endl;
        }
    }   
    // method to fire a warrior 
    void Noble::fire(Warrior& warrior) {
        if (isAlive) {
            size_t index = findWarriorIndex(army, warrior.getName());
            army[index] = army[army.size() - 1];
            army.pop_back();
            warrior.setEmployer(nullptr);
            strength -= warrior.getStrength();
        } else {
            std::cout << name << " is dead." << std::endl;
        }
    }
    // method to battle another noble
    void Noble::battle(Noble& other) {
        std::cout << name << " battles " << other.getName() << std::endl;
        if (!isAlive && !other.isAlive) {
            std::cout << "Oh, NO! They're both dead! Yuck!" << std::endl;
        } else if (!isAlive) {
            std::cout << "He's dead, " << other.getName() << std::endl;
        } else if (!other.isAlive) {
            std::cout << "He's dead, " << name << std::endl;
        } else if (strength == other.strength) {
            std::cout << "Mutual Annihilation: " << name << " and " << 
                other.getName() << " die at each other's hands" << std::endl;
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
        } else if (strength > other.strength) {
            std::cout << name << " defeats " << other.getName() << std::endl;
            double ratio = static_cast<double>(other.strength) / strength;
            for (Warrior* warrior : army) {
                warrior->setStrength(warrior->getStrength() * (1 - ratio));
            }
            updateStrength();
            for (Warrior* warrior : other.army) {
                warrior->setStrength(0);
            }
            other.isAlive = false;
            other.strength = 0;
        } else {
            std::cout << other.getName() << " defeats " << name << std::endl;
            double ratio = static_cast<double>(strength) / other.strength;
            for (Warrior* warrior : other.army) {
                warrior->setStrength(warrior->getStrength() * (1 - ratio));
            }
            other.updateStrength();
            for (Warrior* warrior : army) {
                warrior->setStrength(0);
            }
            isAlive = false;
            strength = 0;
        }
    }
    // method to remove a warrior from the army
    void Noble::removeWarrior(Warrior* warrior) {
        size_t index = findWarriorIndex(army, warrior->getName());
        army[index] = army[army.size() - 1];
        army.pop_back();
        warrior->setEmployer(nullptr);
        strength -= warrior->getStrength();
    }

    // method to get the name of the noble
    const std::string& Noble::getName() const {
        return name;
    }

    // overloaded output operator for the Noble class
    std::ostream& operator<<(std::ostream& os, const Noble& noble) {
        os << noble.name << " has an army of " 
            << noble.army.size() << std::endl;
        for (Warrior* warrior : noble.army) {
            os << *warrior << std::endl;
        }
        return os;
    }

}