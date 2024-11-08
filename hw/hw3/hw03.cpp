#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


class Warrior{
    private:
    // nested class Weapon declared as private
    class Weapon{
        private:

        string name;
        int strength;

        public:
        
        Weapon(const string &name, int strength) :
        name(name), strength(strength){}

        // output operator declared as friend
        friend ostream& operator<<(ostream& os, const Weapon& weapon);

        int getStrength() const {return strength;}

        string getName() const {return name;}

        void setStrength(int new_strength){
            strength = new_strength;
        }
    }; 
    // fields for Warrior class
    string name;
    Weapon weapon;

    public:
    Warrior(const string &name, const string &weapon_name, int weapon_strength)
    : name(name), weapon(weapon_name, weapon_strength){}
    // output operators declared as friend
    friend ostream& operator<<(ostream& os, const Weapon& weapon);
    friend ostream& operator<<(ostream& os, const Warrior& warrior);

    string getName() const {
        return name;
    }

    // getters that call the nested class getters
    int getWeaponStrength(){
        return weapon.getStrength();
    }

    string getWeaponName(){
        return weapon.getName();
    }

    // setter that calls the nested class setter
    void setWeaponStrength(int new_strength){
        weapon.setStrength(new_strength);
    }

    // simulate battle process using a method
    // assuming both warriors exist
    void battle(Warrior &other){
        cout << getName() << " battles " << other.getName() << endl;
        if (other.getWeaponStrength() == 0 && getWeaponStrength() == 0){
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else if (other.getWeaponStrength() == 0){
            cout << "He's dead, " << getName() << endl;
        }
        else if (getWeaponStrength() == 0){
            cout << "He's dead, " << other.getName() << endl;
        }
        else if (getWeaponStrength() > other.getWeaponStrength()){
            cout << getName() << " defeats " << other.getName() << endl;
            setWeaponStrength(getWeaponStrength() - other.getWeaponStrength());
            other.setWeaponStrength(0);
        }
        else if (getWeaponStrength() < other.getWeaponStrength()){
            cout << other.getName() << " defeats " << getName() << endl;
            other.setWeaponStrength(
                other.getWeaponStrength() - getWeaponStrength());
            setWeaponStrength(0);
        }
        else{
            cout << "Mutual Annihalation: " << getName() << " and " 
                << other.getName() << " die at each other's hands" << endl;
            setWeaponStrength(0);
            other.setWeaponStrength(0);
        }
    }
};

// implementation of output operators
ostream& operator<<(ostream& os, const Warrior::Weapon& weapon){
    os << "weapon: " << weapon.name << ", " << weapon.strength;
    return os;
}

ostream& operator<<(ostream& os, const Warrior& warrior){
    os << "Warrior: " << warrior.name << ", " << warrior.weapon;
    return os;
}

// prototypes for 2 used functions
void status(const vector<Warrior> &warriors);

size_t getWarriorIndex(const string &name, const vector<Warrior> &warriors);

int main(){
    vector<Warrior> warriors;
    ifstream ifs("warriors.txt");
    string name, weapon_name, command, name_1, name_2;
    int weapon_strength;
    bool dne = false;
    while(ifs >> command){
        if (command == "Warrior"){
            ifs >> name >> weapon_name >> weapon_strength;
            if (getWarriorIndex(name, warriors) != warriors.size()){
                cout << "Error: warrior of name " << name 
                    << " already exists" << endl;
            }
            // add only if warrior does not exist
            else{
                warriors.emplace_back(name, weapon_name, weapon_strength);
            }
        }
        if (command == "Battle"){
            ifs >> name_1 >> name_2;
            dne = false;

            if (getWarriorIndex(name_1, warriors) == warriors.size()){
                cout << "Error: warrior of name " << name_1 
                    << " does not exist" << endl;
                dne = true;
            }
            if (getWarriorIndex(name_2, warriors) == warriors.size()){
                cout << "Error: warrior of name " << name_2 
                    << " does not exist" << endl;
                dne = true;
            }
            // only battle if both warriors exist
            if (!dne){
                warriors[getWarriorIndex(name_1, warriors)].battle(
                    warriors[getWarriorIndex(name_2, warriors)]);
            }
        }
        if (command == "Status"){
            status(warriors);
        }
    }
    ifs.close();
}

size_t getWarriorIndex(const string &name, const vector<Warrior> &warriors){
    for (size_t i = 0; i < warriors.size(); i++){
        if (warriors[i].getName() == name){
            return i; // return index if found
        }
    }
    return warriors.size(); // return size if not found
}

void status(const vector<Warrior> &warriors){
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for (size_t i = 0; i < warriors.size(); i++){
        cout << warriors[i] << endl;
    }
}  
