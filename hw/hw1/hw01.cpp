#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

char charConversion(char ch, int distance);
string lineConversion(string line, int distance);

int main(){
    int distance;
    string line;
    vector<string> result;
    ifstream ifs;
    ifs.open("encrypted.txt");
    ifs >> distance;
    distance = distance % 26;
    getline(ifs, line);
    while (getline(ifs, line)){
        result.push_back(lineConversion(line, distance));
    }
    ifs.close();
    for (size_t i = 1; i <= result.size(); ++i){
        cout << result[result.size() - i] << endl;
    }
    return 0;
}

char charConversion(char ch, int distance){
    if (ch <= 'Z' && ch >= 'A'){
        return (ch + distance) % 25 + 'A';
    }
    return ch;
}

string lineConversion(string line, int distance){
    for (size_t i = 0; i < line.size(); ++i){
        line[i] = charConversion(line[i], distance);
    }
    return line;
}