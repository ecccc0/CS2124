#include <iostream>
#include <string>
#include <vector>
// include guards
#ifndef NOBLE_H
#define NOBLE_H

// namespace for the WarriorCraft
namespace WarriorCraft {
    // forward declaration of the Warrior class
    class Warrior;

    class Noble {
    public:
        // declared methods, defined in Noble.cpp
        friend std::ostream& operator<<(std::ostream& os, const Noble& noble);
        void updateStrength();
        Noble(const std::string& name);
        void hire(Warrior& warrior);
        void fire(Warrior& warrior);
        void battle(Noble& other);
        void removeWarrior(Warrior* warrior);
        const std::string& getName() const;
    private:
        // private fields
        std::string name;
        std::vector<Warrior*> army;
        bool isAlive;
        int strength;

    };
}

#endif