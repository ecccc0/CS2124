/*
Eric Cheung
Lab 12
rec12.cpp
*/
#include <cstdlib>
#include <iostream>
using namespace std;

class List {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int d = 0) : data(d), prev(nullptr), next(nullptr) {}
    };
    Node* header;
    Node* trailer;
    size_t sz;

public:
    List() : header(new Node()), trailer(new Node()), sz(0) {
        header->next = trailer;
        trailer->prev = header;
    }

    ~List() {
        cout << "~List()\n";
        clear();
        delete header;
        delete trailer;
    }

    List(const List& other) : List() {
        cout << "List(List)\n";
        for (Node* p = other.header->next; p != other.trailer; p = p->next) {
            push_back(p->data);
        }
    }

    List& operator=(const List& other) {
        cout << "List::op=(List)\n";
        if (this != &other) {
            clear();
            for (Node* p = other.header->next; p != other.trailer; p = p->next) {
                push_back(p->data);
            }
        }
        return *this;
    }
    
    void push_back(int data) {
        Node* pred = trailer->prev;
        Node* newNode = new Node(data);
        newNode->next = trailer;
        newNode->prev = pred;
        pred->next = newNode;
        trailer->prev = newNode;
        ++sz;
    }

    void pop_back() {
        if (sz > 0) {
            Node* toDelete = trailer->prev;
            Node* pred = toDelete->prev;
            pred->next = trailer;
            trailer->prev = pred;
            delete toDelete;
            --sz;
        }
    }

    void push_front(int data) {
        Node* succ = header->next;
        Node* newNode = new Node(data);
        newNode->prev = header;
        newNode->next = succ;
        header->next = newNode;
        succ->prev = newNode;
        ++sz;
    }

    void pop_front() {
        if (sz > 0) {
            Node* toDelete = header->next;
            Node* succ = toDelete->next;
            header->next = succ;
            succ->prev = header;
            delete toDelete;
            --sz;
        }
    }

    int& front() {
        return header->next->data;
    }
    const int& front() const {
        return header->next->data;
    }
    int& back() {
        return trailer->prev->data;
    }
    const int& back() const {
        return trailer->prev->data;
    }

    size_t size() const {
        return sz;
    }

    void clear() {
        while (sz > 0) pop_front();
    }

    int& operator[](size_t i) {
        Node* p = header->next;
        for (size_t k = 0; k < i; ++k) p = p->next;
        return p->data;
    }
    const int& operator[](size_t i) const {
        Node* p = header->next;
        for (size_t k = 0; k < i; ++k) p = p->next;
        return p->data;
    }

    class iterator {
        friend class List;
        Node* curr;
    public:
        iterator(Node* p = nullptr) : curr(p) {}
        iterator& operator++() { curr = curr->next; return *this; }
        iterator& operator--() { curr = curr->prev; return *this; }
        int& operator*() const { return curr->data; }
        friend bool operator==(const iterator& lhs, const iterator& rhs) {
            return lhs.curr == rhs.curr;
        }
        friend bool operator!=(const iterator& lhs, const iterator& rhs) {
            return !(lhs == rhs);
        }
    };

    iterator begin() { return iterator(header->next); }
    iterator end()   { return iterator(trailer); }

    iterator insert(iterator pos, int data) {
        Node* succ = pos.curr;
        Node* pred = succ->prev;
        Node* newNode = new Node(data);
        newNode->next = succ;
        newNode->prev = pred;
        pred->next = newNode;
        succ->prev = newNode;
        ++sz;
        return iterator(newNode);
    }

    iterator erase(iterator pos) {
        Node* node = pos.curr;
        Node* pred = node->prev;
        Node* succ = node->next;
        pred->next = succ;
        succ->prev = pred;
        iterator ret(succ);
        delete node;
        --sz;
        return ret;
    }

    friend ostream& operator<<(ostream& os, const List& l) {
        for (Node* p = l.header->next; p != l.trailer; p = p->next) {
            os << p->data;
            if (p->next != l.trailer) os << ' ';
        }
        return os;
    }
};


void printListInfo(const List& myList) {
    cout << "size: " << myList.size()
         << ", front: " << myList.front()
         << ", back(): " << myList.back()
         << ", list: " << myList << endl;
}

void changeFrontAndBackConst(List& theList) {
    theList.front() = 17;
    theList.back() = 42;
}

void changeFrontAndBack(List& theList) {
    theList.front() = 17;
    theList.back() = 42;
}

void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << endl;
    cout << "Leaving doNothing\n";
}
int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    
    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    printListInfo(myList);
    cout << "===================\n";

    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);
    

    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";
    
    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Copy control\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Calling doNothing(myList)\n";
    doNothing(myList);
    cout << "Back from doNothing(myList)\n";
    printListInfo(myList);

    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    List listTwo;
    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    printListInfo(listTwo);
    cout << "listTwo = myList\n";
    listTwo = myList;
    cout << "myList: ";
    printListInfo(myList);
    cout << "listTwo: ";
    printListInfo(listTwo);
    cout << "===================\n";
}
