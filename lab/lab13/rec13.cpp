/*
Eric Cheung
rec13.cpp
Lab 13
*/
#include <iostream>
#include <fstream>
#include <vector> 
#include <list>
#include <algorithm> 
#include <string> 
#include <set>
#include <map>
using namespace std;

// Task 9: print list using const_iterator
void printList(const list<int>& lst) {
    cout << "[";
    for (list<int>::const_iterator it = lst.begin(); it != lst.end(); ++it) {
        cout << *it;
        if (next(it) != lst.end()) cout << ", ";
    }
    cout << "]" << endl;
}

// Task 10: print list using ranged-for
void printListRanged(const list<int>& lst) {
    cout << "[";
    bool first = true;
    for (int x : lst) {
        if (!first) cout << ", ";
        cout << x;
        first = false;
    }
    cout << "]" << endl;
}

// Task 11: print every other item in list using auto
void printAlternateAuto(const list<int>& lst) {
    cout << "[";
    bool first = true;
    for (auto it = lst.begin(); it != lst.end(); ) {
        if (!first) cout << ", ";
        cout << *it;
        first = false;
        ++it;
        if (it == lst.end()) break;
        ++it;
    }
    cout << "]" << endl;
}

// Task 12: find in list (no auto)
list<int>::const_iterator findInList(const list<int>& lst, int value) {
    for (list<int>::const_iterator it = lst.begin(); it != lst.end(); ++it) {
        if (*it == value) return it;
    }
    return lst.end();
}

// Task 13: find in list using auto return type (C++14)
auto findInListAutoReturn(const list<int>& lst, int value) -> list<int>::const_iterator {
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        if (*it == value) return it;
    }
    return lst.end();
}

// Task 16: demo lambdas
void demoLambdas() {
    // no-capture lambda printing
    [] { cout << "Hello Lambda!" << endl; }();
    // lambda sum
    [] (int a, int b) { cout << (a + b) << endl; } (4, 5);
    int result = [] (int a, int b) { return a + b; } (4, 5);
    cout << "the result is: " << result << endl;
    // explicit return type
    int result2 = [] (int a, int b) -> int { return a + b; } (4, 5);
    cout << "the result is: " << result2 << endl;
}

// Task 17: lambda capture example
void demoLambdaCapture(int divisor) {
    vector<int> tmp = {10, 15, 20, 25, 30};
    auto it = find_if(tmp.begin(), tmp.end(), [divisor](int x) { return x % divisor == 0; });
    if (it != tmp.end())
        cout << "First multiple of " << divisor << " is " << *it << endl;
    else
        cout << "No multiples of " << divisor << " found" << endl;
}

// Task 19: ourFind for list of ints
list<int>::iterator ourFind(list<int>::iterator begin, list<int>::iterator end, int value) {
    cout << "Using ourFind for list" << endl;
    for (list<int>::iterator it = begin; it != end; ++it) {
        if (*it == value) return it;
    }
    return end;
}

// Task 20: templated ourFind
template <typename Iterator, typename T>
Iterator ourFindTemplate(Iterator begin, Iterator end, const T& value) {
    cout << "Using ourFindTemplate" << endl;
    for (Iterator it = begin; it != end; ++it) {
        if (*it == value) return it;
    }
    return end;
}

int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:" << endl;
    vector<int> v = {5, 3, 8, 1, 4, 6, 2, 7};
    cout << "Vector v: ";
    for (int x : v) cout << x << " ";
    cout << endl << "=======" << endl;

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:" << endl;
    list<int> lst(v.begin(), v.end());
    cout << "List lst: ";
    for (int x : lst) cout << x << " ";
    cout << endl << "=======" << endl;

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:" << endl;
    sort(v.begin(), v.end());
    cout << "Sorted v: "; for (int x : v) cout << x << " "; cout << endl;
    cout << "Unsorted list remains: "; for (int x : lst) cout << x << " "; cout << endl;
    cout << "=======" << endl;

    // 4. print every other element of the vector.
    cout << "Task 4:" << endl;
    cout << "Every other in v: ";
    for (size_t i = 0; i < v.size(); i += 2) cout << v[i] << " ";
    cout << endl << "=======" << endl;

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5: (Deleted)" << endl;
    // for (size_t i = 0; i < lst.size(); i += 2) cout << lst[i] << " ";
    cout << "=======" << endl;

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:" << endl;
    cout << "Every other in v: ";
    for (vector<int>::iterator it = v.begin(); it < v.end(); it += 2) cout << *it << " ";
    cout << endl << "=======" << endl;

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:" << endl;
    cout << "Every other in lst: ";
    for (list<int>::iterator it = lst.begin(); it != lst.end(); ) {
        cout << *it << " ";
        ++it;
        if (it == lst.end()) break;
        ++it;
    }
    cout << endl << "=======" << endl;

    // 8. Sorting a list
    cout << "Task 8:" << endl;
    lst.sort();
    cout << "Sorted list: "; 
    for (int x : lst) cout << x << " ";
    cout << endl;
    cout << "=======" << endl;

    // 9. Calling the function to print the list
    cout << "Task 9:" << endl;
    printList(lst);
    cout << "=======" << endl;

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:" << endl;
    printListRanged(lst);
    cout << "=======" << endl;

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:" << endl;
    printAlternateAuto(lst);
    cout << "=======" << endl;

    cout << "Task 12:" << endl;
    list<int>::const_iterator it12 = findInList(lst, 4);
    if (it12 != lst.end()) {
        cout << *it12 << endl;
    } else {
        cout << "not found" << endl;
    }
    cout << "=======" << endl;

    cout << "Task 13:" << endl;
    auto it13 = findInListAutoReturn(lst, 9);
    if (it13 != lst.end()) {
        cout << *it13 << endl;
    } else {
        cout << "not found" << endl;
    }
    cout << "=======" << endl;

    cout << "Task 14:" << endl;
    auto it14 = find(v.begin(), v.end(), 6);
    if (it14 != v.end()) {
        cout << *it14 << endl;
    } else {
        cout << "not found" << endl;
    }
    cout << "=======" << endl;

    cout << "Task 15:" << endl;
    auto isEven = [](int x){ return x % 2 == 0; };
    auto it15v = find_if(v.begin(), v.end(), isEven);
    if (it15v != v.end()) {
        cout << "First even in v: " << *it15v << endl;
    } else {
        cout << "First even in v: none" << endl;
    }
    auto it15l = find_if(lst.begin(), lst.end(), isEven);
    if (it15l != lst.end()) {
        cout << "First even in lst: " << *it15l << endl;
    } else {
        cout << "First even in lst: none" << endl;
    }
    cout << "=======" << endl;

    cout << "Task 16:" << endl;
    demoLambdas();
    cout << "=======" << endl;

    cout << "Task 17:" << endl;
    demoLambdaCapture(3);
    cout << "=======" << endl;

    cout << "Task 18:" << endl;
    int* arr = new int[v.size()];
    copy(v.begin(), v.end(), arr);
    cout << "Array: "; 
    for (size_t i = 0; i < v.size(); ++i) { 
        cout << arr[i] << " "; 
    }
    cout << endl;
    auto it18 = find(arr, arr + v.size(), 4);
    if (it18 != arr + v.size()) {
        cout << *it18 << endl;
    } else {
        cout << "not found" << endl;
    }
    delete[] arr;
    cout << "=======" << endl;

    cout << "Task 19:" << endl;
    list<int> lst19 = lst;
    auto it19 = ourFind(lst19.begin(), lst19.end(), 2);
    if (it19 != lst19.end()) {
        cout << *it19 << endl;
    } else {
        cout << "not found" << endl;
    }
    cout << "=======" << endl;

    // Task 20: templated ourFind
    cout << "Task 20:" << endl;
    auto it20v = ourFindTemplate(v.begin(), v.end(), 5);
    if (it20v != v.end()) {
        cout << *it20v << endl;
    } else {
        cout << "not found" << endl;
    }
    auto it20l = ourFindTemplate(lst.begin(), lst.end(), 5);
    if (it20l != lst.end()) {
        cout << *it20l << endl;
    } else {
        cout << "not found" << endl;
    }
    cout << "=======" << endl;

    // Read tokens
    ifstream fin("pooh-nopunc.txt");
    vector<string> tokens;
    string tok;
    while (fin >> tok) tokens.push_back(tok);
    fin.close();

    // Task 21: distinct with vector
    cout << "Task 21:" << endl;
    vector<string> distinct;
    for (const auto& w : tokens) {
        if (find(distinct.begin(), distinct.end(), w) == distinct.end())
            distinct.push_back(w);
    }
    cout << distinct.size() << " distinct words:\n";
    for (const auto& w : distinct) cout << w << " ";
    cout << endl << "=======" << endl;

    // Task 22: distinct with set
    cout << "Task 22:" << endl;
    set<string> tokenSet(tokens.begin(), tokens.end());
    cout << tokenSet.size() << " distinct words:\n";
    for (const auto& w : tokenSet) cout << w << " ";
    cout << endl << "=======" << endl;

    // Task 23: map word -> positions
    cout << "Task 23:" << endl;
    map<string, vector<int>> wordMap;
    for (size_t i = 0; i < tokens.size(); ++i) {
        wordMap[tokens[i]].push_back(i + 1);
    }
    for (const auto& p : wordMap) {
        cout << p.first << ": ";
        for (int pos : p.second) cout << pos << " ";
        cout << endl;
    }

    return 0;
}