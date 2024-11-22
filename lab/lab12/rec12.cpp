// Doubly linked list
//  Test code

#include <cstdlib>
#include <iostream>
using namespace std;

class List {
    struct Node {
        int data;
        Node* prev;
        Node* next;
    };
public:
    List(): head(new Node{-1, nullptr, nullptr}), 
        tail(new Node{-1, head, nullptr}), len(0) {
            head->next = tail;
        }

    List(const List& other): head(new Node{-1, nullptr, nullptr}),
        tail(new Node{-1, head, nullptr}), len(0) {
        head->next = tail;
        for (Node* curr = other.head->next; curr != other.tail; curr = curr->next) {
            push_back(curr->data);
        }
    }

    ~List() {
        clear();
        delete head;
        delete tail;
    }

    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            for (Node* curr = other.head->next; curr != other.tail; curr = curr->next) {
                push_back(curr->data);
            }
        }
        return *this;
    }

    void push_back(int data) {
        Node* newNode = new Node{data, tail->prev, tail};
        tail->prev->next = newNode;
        tail->prev = newNode;
        len++;
    }

    void pop_back() {
        if (tail->prev == head) return;
        Node* toDelete = tail->prev;
        tail->prev = toDelete->prev;
        toDelete->prev->next = tail;
        delete toDelete;
        len--;
    }

    const int front() const {
        return head->next->data;
    }

    int& front() {
        return head->next->data;
    }

    const int back() const {
        return tail->prev->data;
    }

    int& back() {
        return tail->prev->data;
    }

    size_t size() const {
        return len;
    }

    friend ostream& operator<<(ostream& os, const List& list) {
        Node* curr = list.head->next;
        while (curr != list.tail) {
            os << curr->data;
            if (curr->next != list.tail) os << " ";
            curr = curr->next;
        }
        return os;
    }

    void push_front(int data) {
        Node* newNode = new Node{data, head, head->next};
        head->next->prev = newNode;
        head->next = newNode;
        len++;
    }

    void pop_front() {
        if (head->next == tail) return;
        Node* toDelete = head->next;
        head->next = toDelete->next;
        toDelete->next->prev = head;
        delete toDelete;
        len--;
    }

    void clear() {
        while (head->next != tail) {
            pop_front();
        }
    }

    const int operator[](size_t index) const {
        Node* curr = head->next;
        for (size_t i = 0; i < index; ++i) {
            curr = curr->next;
        }
        return curr->data;
    }

    int& operator[](size_t index) {
        Node* curr = head->next;
        for (size_t i = 0; i < index; ++i) {
            curr = curr->next;
        }
        return curr->data;
    }

    class Iterator {
        friend class List;
    public:
        Iterator(Node* node): curr(node) {}
        Iterator& operator++() {
            if (curr != nullptr) {
                curr = curr->next;
            }
            return *this;
        }

        Iterator& operator--() {
            if (curr != nullptr) {
                curr = curr->prev;
            }
            return *this;
        }
        
        friend bool operator==(const Iterator& lhs, const Iterator& rhs);
        friend bool operator!=(const Iterator& lhs, const Iterator& rhs);

        int& operator*() {
            return curr->data;
        }

    private:
        Node* curr;
        
    };

    Iterator begin() {
        return Iterator(head->next);
    }

    Iterator end() {
        return Iterator(tail);
    }

    Iterator insert(Iterator iter, int data) {
        Node* newNode = new Node{data, iter.curr->prev, iter.curr};
        iter.curr->prev->next = newNode;
        iter.curr->prev = newNode;
        len++;
        return Iterator(newNode);
    }

    Iterator erase(Iterator iter) {
        Node* toDelete = iter.curr;
        iter.curr->prev->next = iter.curr->next;
        iter.curr->next->prev = iter.curr->prev;
        iter.curr = iter.curr->next;
        delete toDelete;
        len--;
        return iter;
    }

private:
    Node* head;
    Node* tail;
    size_t len;
};

// Task 1
void printListInfo(const List& myList) {
        cout << "size: " << myList.size()
             << ", front: " << myList.front()
             << ", back(): " << myList.back()
             << ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
/*
void changeFrontAndBackConst(const List& theList) {
    theList.front() = 17;
    theList.back() = 42;
}
*/

void changeFrontAndBack(List& theList) {
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

// Task 8
void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
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
        cout << "myList2.push_front(" << i*i << ");\n";
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

    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task 4
    cout << "\n------Task Four------\n";
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
    
    // Task 5
    cout << "\n------Task Five------\n";
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
    for (List::Iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";
    // Task 6
    cout << "\n------Task Six------\n";
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
    
    // Task 7
    cout << "\n------Task Seven------\n";
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
    
    // Task 8
    cout << "\n------Task Eight------\n";
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
    for (int i = 0; i < 10; ++i) {
        listTwo.insert(listTwo.begin(), i*i);
    }
    
    printListInfo(listTwo);
    
    cout << "listTwo = myList\n";
    listTwo = myList;
    cout << "myList: ";
    printListInfo(myList);
    cout << "listTwo: ";
    printListInfo(listTwo);
    cout << "===================\n";
    
}

bool operator==(const List::Iterator& lhs, const List::Iterator& rhs) {
    return lhs.curr == rhs.curr;
}

bool operator!=(const List::Iterator& lhs, const List::Iterator& rhs) {
    return ! (lhs == rhs);
}