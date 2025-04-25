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
list<int>::iterator ourFind(list<int>& lst, int value) {
    cout << "Using ourFind for list" << endl;
    for (list<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
        if (*it == value) return it;
    }
    return lst.end();
}

// Task 20: templated ourFind
template <typename Container>
auto ourFindTemplate(const Container& c, const typename Container::value_type& value) -> decltype(c.begin()) {
    cout << "Using ourFindTemplate" << endl;
    for (auto it = c.begin(); it != c.end(); ++it) {
        if (*it == value) return it;
    }
    return c.end();
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
    cout << "Task 5: (won't compile: no operator[] for list)" << endl;
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
    cout << "Sorted list: "; for (int x : lst) cout << x << " "; cout << endl;
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

    // Task 12: find in list (no auto)
    cout << "Task 12:" << endl;
    auto it12 = findInList(lst, 4);
    cout << (it12 != lst.end() ? to_string(*it12) : string("not found")) << endl;
    cout << "=======" << endl;

    // Task 13: find in list (auto return)
    cout << "Task 13:" << endl;
    auto it13 = findInListAutoReturn(lst, 9);
    cout << (it13 != lst.end() ? to_string(*it13) : string("not found")) << endl;
    cout << "=======" << endl;

    // Task 14: generic find
    cout << "Task 14:" << endl;
    auto it14 = find(v.begin(), v.end(), 6);
    cout << (it14 != v.end() ? to_string(*it14) : string("not found")) << endl;
    cout << "=======" << endl;

    // Task 15: find_if
    cout << "Task 15:" << endl;
    auto isEven = [](int x){ return x % 2 == 0; };
    auto it15v = find_if(v.begin(), v.end(), isEven);
    cout << "First even in v: " << (it15v != v.end() ? to_string(*it15v) : string("none")) << endl;
    auto it15l = find_if(lst.begin(), lst.end(), isEven);
    cout << "First even in lst: " << (it15l != lst.end() ? to_string(*it15l) : string("none")) << endl;
    cout << "=======" << endl;

    // Task 16: lambdas demo
    cout << "Task 16:" << endl;
    demoLambdas();
    cout << "=======" << endl;

    // Task 17: lambda capture
    cout << "Task 17:" << endl;
    demoLambdaCapture(3);
    cout << "=======" << endl;

    // Task 18: copy to dynamic array
    cout << "Task 18:" << endl;
    int* arr = new int[v.size()];
    copy(v.begin(), v.end(), arr);
    cout << "Array: "; for (size_t i = 0; i < v.size(); ++i) cout << arr[i] << " "; cout << endl;
    auto it18 = find(arr, arr + v.size(), 4);
    cout << (it18 != arr + v.size() ? to_string(*it18) : string("not found")) << endl;
    delete[] arr;
    cout << "=======" << endl;

    // Task 19: ourFind
    cout << "Task 19:" << endl;
    list<int> lst19 = lst;
    auto it19 = ourFind(lst19, 2);
    cout << (it19 != lst19.end() ? to_string(*it19) : string("not found")) << endl;
    cout << "=======" << endl;

    // Task 20: templated ourFind
    cout << "Task 20:" << endl;
    auto it20v = ourFindTemplate(v, 5);
    cout << (it20v != v.end() ? to_string(*it20v) : string("not found")) << endl;
    auto it20l = ourFindTemplate(lst, 5);
    cout << (it20l != lst.end() ? to_string(*it20l) : string("not found")) << endl;
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
    cout << tokenSet.size() << " distinct words (sorted):\n";
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