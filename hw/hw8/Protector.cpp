#include <vector>
#include <iostream>
#include <string>

#include "Protector.h"
#include "Noble.h"

namespace WarriorCraft {
// Abstract base class Protector

    Protector::Protector(const std::string& name, double strength)
        : name(name), strength(strength), employer(nullptr), alive(true) {}

    Protector::~Protector() {}

    const std::string& Protector::getName() const {
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
            std::cout << name << " flees in terror, abandoning his lord, "
                << employer->getName() << std::endl;
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

    std::ostream& operator<<(std::ostream& os, const Protector& protector) {
        os << protector.name << ": " << protector.strength;
        return os;
    }


    // Derived class Wizard
    Wizard::Wizard(const std::string& name, double strength)
        : Protector(name, strength) {}

    void Wizard::defend() const {
        if (alive)
            std::cout << "POOF" << std::endl;
    }

    // Abstract class Warrior

    Warrior::Warrior(const std::string& name, double strength)
        : Protector(name, strength) {}

    // Derived class Archer

    Archer::Archer(const std::string& name, double strength)
        : Warrior(name, strength) {}

    void Archer::defend() const {
        if (alive && employer != nullptr)
            std::cout << "TWANG! " << name << " says: Take that in the name of my lord, "
                    << employer->getName() << std::endl;
    }

    // Derived class Swordsman

    Swordsman::Swordsman(const std::string& name, double strength)
        : Warrior(name, strength) {}

    void Swordsman::defend() const {
        if (alive && employer != nullptr)
            std::cout << "CLANG! " << name << " says: Take that in the name of my lord, "
                    << employer->getName() << std::endl;
    }


}