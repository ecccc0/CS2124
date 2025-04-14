#include <iostream>
#include <string>
#include <vector>

#ifndef NOBLE_H
#define NOBLE_H

namespace WarriorCraft {

    class Protector; // Forward declaration

    // abstract base class Noble
    class Noble {
    public:
        Noble(const std::string& name);
        virtual ~Noble();
        const std::string& getName() const;
        bool isAlive() const;
        virtual double getStrength() const = 0;
        virtual void reduceStrength(double ratio) = 0;
        virtual void battle(Noble& opponent);
        virtual void defend();
        friend std::ostream& operator<<(std::ostream& os, const Noble& noble);
    protected:
        std::string name;
        bool alive;

    };

    class Lord : public Noble {
    public:
        Lord(const std::string& name);
        bool hires(Protector& protector);
        bool fires(Protector& protector);
        void removeProtector(Protector& protector);
        double getStrength() const override;
        void reduceStrength(double ratio) override;
        void defend() override;
        friend std::ostream& operator<<(std::ostream& os, const Lord& lord);
    private:
        std::vector<Protector*> army;
    };
    
    class PersonWithStrengthToFight : public Noble {
    public:
        PersonWithStrengthToFight(const std::string& name, double strength);
        double getStrength() const override;
        void reduceStrength(double ratio) override;
        void defend() override;
        friend std::ostream& operator<<(std::ostream& os, const PersonWithStrengthToFight& person);

    private:
        double strength;
    };

}

#endif  // NOBLE_H