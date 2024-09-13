#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
struct Hydrocarbon{
    vector<string> names;
    int C;
    int H;
};

void openStream(ifstream ifs);
void fillVector(vector<Hydrocarbon> &v, ifstream ifs);
void display(vector<Hydrocarbon> v);
void insertToVector(string name, int h, int c);
int findFormula(vector<Hydrocarbon> v, int h, int c);
void displaySingle(Hydrocarbon hc);

int main(){


    return 0;
}

void openStream(ifstream ifs){
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

void fillVector(vector<Hydrocarbon> &v, ifstream ifs){
    string name;
    string formula;
    int cur_c, cur_h;
    bool flag;
    while (ifs >> name >> formula){
        int cursor = 1;
        string h, c;
        while (formula[cursor] != 'H'){
            c.push_back(formula[cursor]);
        }
        cur_c = stoi(c);
        h = formula.substr(cursor+1);
        cur_h = stoi(h);
        
        if (flag){
            vector<string> new_names{name};
            Hydrocarbon hc{new_names, cur_c, cur_h}; 
            v.push_back(hc);
        }
    }
}

int findFormula(vector<Hydrocarbon> v, int h, int c){
    Hydrocarbon x;
    for (size_t i = 0; i < v.size(); ++i){
        x = v[i];
        if (x.C == c && x.H == h){
            return i;
        }
    }
    return v.size();
}
