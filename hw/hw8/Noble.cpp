#include <iostream>
#include <string>
#include <vector>
#include "Noble.h"
#include "Protector.h" 


namespace WarriorCraft {

    // Abstract base class Noble
    Noble::Noble(const std::string& name) : name(name), alive(true) {}

    Noble::~Noble() {}

    const std::string& Noble::getName() const {
        return name;
    }

    bool Noble::isAlive() const {
        return alive;
    }

    void Noble::battle(Noble& opponent) {
        std::cout << name << " battles " << opponent.name << std::endl;

        if (!alive && !opponent.alive) {
            std::cout << "Oh, NO! They're both dead! Yuck!" << std::endl;
            return;
        }
        if (!alive) {
            std::cout << "He's dead, " << opponent.name << std::endl;
            return;
        }
        if (!opponent.alive) {
            std::cout << "He's dead, " << name << std::endl;
            return;
        }

        defend();
        opponent.defend();

        double myStrength = getStrength();
        double opponentStrength = opponent.getStrength();

        if (myStrength == opponentStrength) {
            std::cout << "Mutual Annihilation: " << name << " and " << opponent.name
                    << " die at each other's hands" << std::endl;
            reduceStrength(1);
            opponent.reduceStrength(1);
            alive = false;
            opponent.alive = false;
        } else if (myStrength > opponentStrength) {
            std::cout << name << " defeats " << opponent.name << std::endl;
            double ratio = opponentStrength / myStrength;
            reduceStrength(ratio);
            opponent.reduceStrength(1);
            opponent.alive = false;
        } else {
            std::cout << opponent.name << " defeats " << name << std::endl;
            double ratio = myStrength / opponentStrength;
            opponent.reduceStrength(ratio);
            reduceStrength(1);
            alive = false;
        }
    }
    
    void Noble::defend() {
        // Base class does nothing
    }

    std::ostream& operator<<(std::ostream& os, const Noble& noble) {
        os << noble.name;
        return os;
    }

    // Derived class PersonWithStrengthToFight

    PersonWithStrengthToFight::PersonWithStrengthToFight
        (const std::string& name, double strength) : Noble(name), strength(strength) {}

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
            std::cout << "UGH!!!" << std::endl;
    }

    std::ostream& operator<<(std::ostream& os, const PersonWithStrengthToFight& person) {
        os << person.name << " has strength: " << person.strength;
        return os;
    }


        // Derived class Lord

    Lord::Lord(const std::string& name) : Noble(name) {}

    bool Lord::hires(Protector& protector) {
        if (!alive) {
            std::cout << name << " is dead, cannot hire." << std::endl;
            return false;
        }
        if (!protector.isAlive()) {
            std::cout << protector.getName() << " is dead, cannot be hired." << std::endl;
            return false;
        }
        if (protector.isEmployed()) {
            std::cout << protector.getName() << " is already employed." << std::endl;
            return false;
        }
        army.push_back(&protector);
        protector.setEmployer(this);
        return true;
    }

    bool Lord::fires(Protector& protector) {
        if (!alive) {
            std::cout << name << " is dead, cannot fire." << std::endl;
            return false;
        }
        auto it = find(army.begin(), army.end(), &protector);
        if (it != army.end()) {
            army.erase(it);
            protector.setEmployer(nullptr);
            std::cout << "You don't work for me anymore " << protector.getName()
                      << "! -- " << name << "." << std::endl;
            return true;
        } else {
            std::cout << protector.getName() << " is not in the army of " 
                << name << "." << std::endl;
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

    std::ostream& operator<<(std::ostream& os, const Lord& lord) {
        os << lord.name << " has an army of " << lord.army.size() << std::endl;
        for (const Protector* protector : lord.army) {
            os << "\t" << *protector << std::endl;
        }
        return os;
    }
}

