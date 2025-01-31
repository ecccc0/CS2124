#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
using namespace std;

struct Hydrocarbon
{
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

int main()
{
    ifstream ifs;
    openStream(ifs);
    vector<Hydrocarbon> v;
    fillVector(v, ifs);
    cout << "Unsorted: " << endl;
    display(v);
    cout << endl << "Sorted: " << endl;
    sort(v);
    display(v);

}

void openStream(ifstream &ifs)
{
    string filename;
    cout << "File name? ";
    do {
        cin >> filename;
        ifs.open(filename);
        if (!ifs)
        {
            cerr << "faile to open file " << filename << endl;
        }
    } while (!ifs);
}


void fillVector(vector<Hydrocarbon> &v, ifstream &ifs)
{
    string name;
    char skip;
    int c, h;
    while (ifs >> name >> skip >> c >> skip >> h)
    {
        insertToVector(v, name, c, h);
    }

}

void insertToVector(vector<Hydrocarbon> &v, const string &name, int c, int h)
{
    size_t index = findFormula(v, c, h);
    if (index == v.size())
    {
        vector<string> new_names{name};
        Hydrocarbon hc{new_names, c, h}; 
        v.push_back(hc);
    }
    else
    {
        v[index].names.push_back(name);
    }

}

size_t findFormula(const vector<Hydrocarbon> &v, int c, int h)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        if (v[i].C == c && v[i].H == h)
        {
            return i;
        }
    }
    return v.size();
}

void display(const vector<Hydrocarbon> &v)
{
    for (const Hydrocarbon& hc : v)
    {
        displaySingle(hc);
        cout << endl;
    }
}

void displaySingle(const Hydrocarbon &hc)
{
    cout << 'C' << hc.C << 'H' << hc.H << " ";
    for (const string& name : hc.names)
    {
        cout << name << " ";
    }

}

void sort(vector<Hydrocarbon> &v)
{
    // bubble
    for (size_t i = 0; i < v.size(); i++)
    {
        for (size_t j = 0; j < v.size() - 1 - i; j++)
        {
            if (v[j].C > v[j+1].C || (v[j].C==v[j+1].C && v[j].H > v[j+1].H)) 
            {
                swap(v[j], v[j+1]);
            }
        }
    }
}