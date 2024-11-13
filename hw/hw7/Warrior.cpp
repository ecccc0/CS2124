#include <iostream>
#include <string>
#include <vector>
#include "Noble.h"
#include "Warrior.h"

namespace WarriorCraft {
    // constructor for the Warrior class
    Warrior::Warrior(const std::string& name, int strength) 
        : name(name), strength(strength), employer(nullptr) {}


    // method to set the strength of a warrior
    void Warrior::setStrength(int newStrength) {
        strength = newStrength;
    }

    //method to get the strength of a warrior
    int Warrior::getStrength() const {
        return strength;
    }

    // method to get the name of a warrior
    const std::string& Warrior::getName() const {
        return name;
    }

    // method to set the employer of a warrior
    void Warrior::setEmployer(Noble* noble) {
        employer = noble;
    }

    // method to get the employer of a warrior
    Noble* Warrior::getEmployer() const {
        return employer;
    }

    // method to check if a warrior is hired
    bool Warrior::isHired() const {
        return employer != nullptr;
    }

    // method to remove a warrior from the army
    void Warrior::runaway() {
        if (strength == 0) {
            std::cout << name << "is dead" << std::endl;
            return;
        }
        if (!isHired()) {
            std::cout << name << " is unemployed" << std::endl;
            return;
        }
        employer->removeWarrior(this);
        employer = nullptr;
    }
    
    // overloaded output operator for the Warrior class
    std::ostream& operator<<(std::ostream& os, const Warrior& warrior) {
        os << warrior.name << ": " << warrior.strength;
        return os;
    }
}