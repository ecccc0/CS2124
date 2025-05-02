/*
Eric Cheung
rec14.cpp
lab 14
*/
#include <iostream>
#include <vector>
#include <algorithm>  // max
#include <stdexcept>
using namespace std;

// Node type for the linked list
struct Node {
    int data = 0;
    Node* next = nullptr;
};

// Node type for the ternary tree
struct TNode {
    int data = 0;
    TNode* left = nullptr;
    TNode* mid = nullptr;
    TNode* right = nullptr;
};

/////////////////////////////////////////////////////////////////////////
//
// Provided code for use in testing
//
void listPrint(const Node* headPtr);
void listClear(Node*& headPtr);
Node* listBuild(const vector<int>& vals);

// Task 1 function:
Node* listSum(Node* l1, Node* l2) {
    if (!l1 && !l2) return nullptr;
    int val = 0;
    Node* next1 = nullptr;
    Node* next2 = nullptr;
    if (l1) {
        val += l1->data;
        next1 = l1->next;
    }
    if (l2) {
        val += l2->data;
        next2 = l2->next;
    }
    Node* node = new Node{val, nullptr};
    node->next = listSum(next1, next2);
    return node;
}

// Task 2 function:
int treeMax(TNode* root) {
    if (!root) {
        // throw out_of_range("empty tree");
        throw invalid_argument("empty tree");
    }
    int maxv = root->data;
    if (root->left)  maxv = max(maxv, treeMax(root->left));
    if (root->mid)   maxv = max(maxv, treeMax(root->mid));
    if (root->right) maxv = max(maxv, treeMax(root->right));
    return maxv;
}

// Task 3 function:
bool palindrome(const char* s, int len) {
    if (len <= 1) return true;
    if (s[0] != s[len-1]) return false;
    return palindrome(s+1, len-2);
}

// Task 4 function:
bool parity(int n) {
    if (n == 0) return true;

    bool res = parity(n / 2);

    if (n % 2 == 1) 
        return !res;
    else
        return res;
}

// Task 5 function:
int towers(int n, char from, char aux, char to) {
    if (n <= 0) return 0;
    return towers(n-1, from, to, aux) + 1 + towers(n-1, aux, from, to);
}

void mystery(int n) {
    if (n > 1) {
        cout << 'a';
        mystery(n/2);
        cout << 'b';
        mystery(n/2);
    }
    cout << 'c';
}
/*

0 -> c
1 -> c
2 -> acbcc
3 -> acbcc
4,5,6,7 -> aacbccbacbccc
8-15 -> aaacbccbacbcccbaacbccbacbcccc

*/

int main() {
    // We have provided some test code to save you time. Certainly feel
    // free to write more!

    // Task 1:
    cout << "\n==============\n#1: Testing listSum\n";
    Node* l1 = listBuild({2, 7, 1, 8});
    cout << "List (l1): ";
    listPrint(l1);
    
    Node* l2 = listBuild({9, 1, 4, 1});
    cout << "List (l2): ";
    listPrint(l2);

    Node* l3 = listBuild({3, 1, 4, 1, 5, 9});
    cout << "List (l3): ";
    listPrint(l3);

    cout << "The sum of l1 and l2: ";
    Node* l4 = listSum(l1, l2);
    listPrint(l4);

    cout << "The sum of l1 and l3: ";
    Node* l5 = listSum(l1, l3);
    listPrint(l5);

    cout << "The sum of l3 and l1: ";
    Node* l6 = listSum(l3, l1);
    listPrint(l6);

    listClear(l1);
    listClear(l2);
    listClear(l3);
    listClear(l4);
    listClear(l5);
    listClear(l6);

    
    // Task 2:
    cout << "\n==============\n"
         << "#2) Testing max of Tree.\n";
    TNode a{1}, b{20}, c{4}, d{-8, &a, &b, &c}, e{-16}, f{-32, &d, &e};
    cout << "treeMax(&f): " << treeMax(&f) << endl;

    // How do you keep this from crashing? try/catch! Here in main!
    cout << "treeMax(nullptr): ";
    try {
        cout << treeMax(nullptr) << endl;
    } catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
    }

    // Task 3:
    cout << "\n==============\n"
         << "#3) Testing palindrome\n";
    cout << boolalpha
         << "palindrome(\"racecar\", 7): " << palindrome("racecar", 7) << endl
         << "palindrome(\"noon\", 4): " << palindrome("noon", 4) << endl
         << "palindrome(\"raceXar\", 7): " << palindrome("raceXar", 7) << endl
         << "palindrome(\"noXn\", 4): " << palindrome("noXn", 4) << endl;
    
    // Task 4:
    cout << "\n==============\n"
         << "#4) Are there an even number of 1's in binary representation?\n";
    cout << boolalpha;
    for (int i = 0; i < 10; ++i) {
        cout << i << ": " << parity(i) << endl;
    }

    // Task 5:
    cout << "\n==============\n"
         << "#5) How many moves are required for various sized towers?\n";
    for (int i = 1; i < 30; ++i) {
        cout << "towers(" << i << ", 'a', 'b', 'c'): " 
             << towers(i, 'a', 'b', 'c') << endl;
    }

    // Task 6:
    cout << "\n==============\n#6) Testing mystery function\n";
    for (int i = 0; i <= 10; ++i) {
        cout << i << ": ";
        mystery(i);
        cout << endl;
    }

    return 0;
}

//
// The provided utility functions:
//

// listPrint prints out the data values in the list.
// All the values are printed on a single line with blanks separating them.
void listPrint(const Node* headPtr)
{
    const Node* curr = headPtr;
    while (curr != nullptr) {
        cout << curr->data << ' ';
        curr = curr->next;
    }
    cout << endl;
} // listPrint

// listClear frees up all of the nodes in list setting the the head
// pointer to null.
void listClear(Node*& headPtr)
{
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
} // listClear

// listBuild returns a list with the same values as in the vector.
Node* listBuild(const vector<int>& vals)
{
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
	result = new Node{vals[index-1], result};
    }
    return result;
} // listBuild
