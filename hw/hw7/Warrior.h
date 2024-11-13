#include <iostream>
#include <string>
#include <vector>

#ifndef WARRIOR_H
#define WARRIOR_H
// include guards
namespace WarriorCraft {
    class Noble;

    class Warrior {
    public:
        // declared methods, defined in Warrior.cpp
        friend std::ostream& operator<<(std::ostream& os, const Warrior& warrior);
        Warrior(const std::string& name, int strength);
        void setStrength(int newStrength);
        int getStrength() const;
        const std::string& getName() const;
        void setEmployer(Noble* noble);
        Noble* getEmployer() const;
        void runaway();
        bool isHired() const;

    private:
        // private fields
        std::string name;
        Noble* employer;
        int strength;
    };
}

#endif