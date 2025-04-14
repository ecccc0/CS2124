#include <iostream>
#include <string>
#include <vector>

#ifndef PROTECTOR_H
#define PROTECTOR_H
namespace WarriorCraft {
    // abstact base class protector
    class Protector {
    public:
        Protector(const std::string& name, double strength);
        virtual ~Protector();
        const std::string& getName() const;
        double getStrength() const;
        bool isAlive() const;
        bool isEmployed() const;
        void setEmployer(class Lord* newEmployer);
        virtual void defend() const = 0;
        void runaway();
        void reduceStrength(double ratio);
        friend std::ostream& operator<<(std::ostream& os, const Protector& protector);

    protected:
        std::string name;
        double strength;
        class Lord* employer;
        bool alive;
    };

    // Derived class Wizard
    class Wizard : public Protector {
    public:
        Wizard(const std::string& name, double strength);
        void defend() const;
    };

    // Abstract class warrior
    class Warrior : public Protector {
    public: 
        Warrior(const std::string& name, double strength);
        virtual ~Warrior() = default;
        double getStrength() const;
        void reduceStrength(double ratio);
        void defend();
        friend std::ostream& operator<<(std::ostream& os, const Warrior& warrior);
    protected:
        double strength;
        
    };
    // Derived class Archer
    class Archer : public Warrior {
    public:
        Archer(const std::string& name, double strength);
        void defend() const;
    };

    // Derived class Swordsman
    class Swordsman : public Warrior {
    public:
        Swordsman(const std::string& name, double strength);
        void defend() const;
    };


}

#endif  // PROTECTOR_H