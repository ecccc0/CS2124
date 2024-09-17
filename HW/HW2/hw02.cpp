#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Warrior{
    const string name;
    int strength;
};

void battle(Warrior &first, Warrior &second);

void status(const vector<Warrior> &list_of_warriors);

void addWarrior(const string &name, int strengh, vector<Warrior> &list_of_warriors);

bool warriorInList(const string &name, const vector<Warrior> &list_of_warriors);

size_t getWarriorIndex(const string &name, const vector<Warrior> &list_of_warriors);

int main(){
    vector<Warrior> list_of_warriors;
    string command, name_of_new, name_1, name_2;
    int strength_of_new;
    ifstream ifs;

    ifs.open("warriors.txt");
    while (ifs >> command){
        if (command == "Warrior"){
            ifs >> name_of_new >> strength_of_new;
            addWarrior(name_of_new, strength_of_new, list_of_warriors);
        }
        if (command == "Status"){
            status(list_of_warriors);
        }
        if (command == "Battle"){
            ifs >> name_1 >> name_2;
            if (!warriorInList(name_1, list_of_warriors)){
                cout << "Error: warrior of name " << name_1 << " does not exist" << endl;
            }
            if (!warriorInList(name_2, list_of_warriors)){
                cout << "Error: warrior of name " << name_2 << " does not exist" << endl;
            }
            battle(list_of_warriors[getWarriorIndex(name_1, list_of_warriors)], list_of_warriors[getWarriorIndex(name_2, list_of_warriors)]);
        }
    }
}

void battle(Warrior &first, Warrior &second){
    cout << first.name << " battles " << second.name << endl;
    if (first.strength == 0 && second.strength == 0){
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
        return;
    }
    if (first.strength == 0){
        cout << "He's dead, " << second.name << endl;
        return;
    }
    if (second.strength == 0){
        cout << "He's dead, " << first.name << endl;
        return;
    }
    if (first.strength == second.strength){
        first.strength = 0;
        second.strength = 0;
        cout << "Mutual Annihilation: " <<  first.name << " and " << second.name << " die at each other's hands" << endl;
        return;
    }
    if (first.strength > second.strength){
        first.strength -= second.strength;
        second.strength = 0;
        cout << first.name << " defeats " << second.name << endl;
        return;
    }
    if (second.strength > first.strength){
        second.strength -= first.strength;
        first.strength = 0;
        cout << second.name << " defeats " << first.name << endl;
        return;
    }
}

void status(const vector<Warrior> &list_of_warriors){
    cout << "There are: " << list_of_warriors.size() 
    << " warriors" << endl;
    for (size_t i = 0; i < list_of_warriors.size(); i++){
        cout << "Warrior: " << list_of_warriors[i].name << ", strength: " << list_of_warriors[i].strength << endl;
    }
}

void addWarrior(const string &name, int strength, vector<Warrior> &list_of_warriors){
    if (warriorInList(name, list_of_warriors)){
        cout << "Error, warrior of name " << name << "already exists" << endl;
    }
    Warrior new_warrior{name, strength};
    list_of_warriors.push_back(new_warrior);
}

bool warriorInList(const string &name, const vector<Warrior> &list_of_warriors){
    for (size_t i = 0; i < list_of_warriors.size(); i++){
        if (list_of_warriors[i].name == name){
            return true;
        }
    }
    return false;
}

size_t getWarriorIndex(const string &name, const vector<Warrior> &list_of_warriors){
    for (size_t i = 0; i < list_of_warriors.size(); i++){
        if (list_of_warriors[i].name == name){
            return i;
        }
    }
    return 99999; // to get it to compile
}