/*
Eric Cheung
Homework 1
hw01.cpp
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

char charConversion(char ch, int distance);
string lineConversion(string& line, int distance);

int main()
{
    int distance;
    string line;
    vector<string> result;
    ifstream ifs;
    ifs.open("encrypted.txt");
    ifs >> distance;
    distance = distance % 26;
    getline(ifs, line);
    while (getline(ifs, line))
    {
        result.push_back(lineConversion(line, distance));
    }
    ifs.close();
    for (size_t i = 1; i <= result.size(); ++i)
    {
        cout << result[result.size() - i] << endl;
    }
    return 0;
}


char charConversion(char ch, int distance)
{
    if (ch >= 'A' && ch <= 'Z')
    {
        ch = ch - distance;
        if (ch > 'Z')
        {
            ch = ch - 26;
        }
        else if (ch < 'A')
        {
            ch = ch + 26;
        }
    }
    return ch;
}

string lineConversion(string& line, int distance)
{
    for (size_t i = 0; i < line.size(); ++i)
    {
        line[i] = charConversion(line[i], distance);
    }
    return line;
}