#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
using namespace std;
struct Hydrocarbon{
    vector<string> names;
    int C;
    int H;
};

void openStream(ifstream &ifs);
void fillVector(vector<Hydrocarbon> &v, ifstream &ifs);
void display(const vector<Hydrocarbon> &v);
void insertToVector(vector<Hydrocarbon> &v, const string &name, int c, int h);
size_t findFormula(const vector<Hydrocarbon> &v, int c, int h);
void displaySingle(const Hydrocarbon &hc);
void sort(vector<Hydrocarbon> &v);

int main(){
    ifstream ifs;
    openStream(ifs);
    vector<Hydrocarbon> v;
    fillVector(v, ifs);
    cout << "Unsorted: " << endl;
    display(v);
    cout << endl << "Sorted: "<< endl;
    sort(v);
    display(v);


    return 0;
}

void openStream(ifstream &ifs){
    string filename;
    cout << "Enter file name: ";
    do{
      cin >> filename;
      ifs.open(filename);
      if (!ifs){
        cout << "Failed to open file \"" << filename << "\"\n";
      }
    }while(!ifs);
}

void fillVector(vector<Hydrocarbon> &v, ifstream &ifs){
    string name;
    char c;
    int cur_c, cur_h;
    bool flag;
    while (ifs >> name >> c >> cur_c >> c >> cur_h){
        // int cursor = 1;
        // string h, c;
        // while (formula[cursor] != 'H'){
        //     c.push_back(formula[cursor]);
        //     cursor++;
        // }
        // cur_c = stoi(c);
        // h = formula.substr(cursor+1);
        // cur_h = stoi(h);
        insertToVector(v, name, cur_c, cur_h);
    }
}

void insertToVector(vector<Hydrocarbon> &v, const string &name, int c, int h){
    size_t index = findFormula(v, c, h);
    if (index == v.size()){
        vector<string> new_names{name};
        Hydrocarbon hc{new_names, c, h}; 
        v.push_back(hc);
    } 
    else{
        v[index].names.push_back(name);
    }
}

size_t findFormula(const vector<Hydrocarbon> &v, int c, int h){
    Hydrocarbon x;
    for (size_t i = 0; i < v.size(); ++i){
        x = v[i];
        if (x.C == c && x.H == h){
            return i;
        }
    }
    return v.size();
}

void displaySingle(const Hydrocarbon &hc){
    cout << 'C' << hc.C << 'H' << hc.H << " ";
    for (size_t i = 0; i < hc.names.size(); ++i){
        cout << hc.names[i] << " ";
    }
}

void display(const vector<Hydrocarbon> &v){
    for (size_t i = 0; i < v.size(); ++i){
        displaySingle(v[i]);
        cout << endl;
    }
}

void sort(vector<Hydrocarbon> &v){
    // Bubble sort
    for (size_t i = 0; i < v.size(); ++i){
        for (size_t j = 0; j < v.size() - 1 - i; ++j){
            if (v[j].C > v[j+1].C || (v[j].C == v[j+1].C && v[j].H > v[j+1].H)){
                swap(v[j], v[j+1]);
            }
        }
    }
}