/*
  rec03_start.cpp
 */

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Task 1
// Define an Account struct


// Task 2
// Define an Account class (use a different name than in Task 1)


// Task 3
// Define another Account class (use a different name than in Task
// 1&2) and a Transaction class. The Transaction class is to be
// defined outside of the Account class, i.e. it is not "nested".


// Task 4
// Define yet another Account class, this time with a nested public
// Transaction class. Again use a different name for the Account class
// than in the previous Tasks. Note that it is NOT necessary to rename
// the Transaction class, since it is nested.


// Task 5
// Same as Task 4, but make the Transaction nested class private.
// Yes, the Account class needs a new name but, again, the Transaction
// class does not.


int main()
{

    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n"
         << "Filling vector of struct objects, define a local struct instance\n"
         << "and set fields explicitly:\n";

    //      1b
    cout << "Task1b:\n"
         << "Filling vector of struct objects, using {} initialization:\n";


    //==================================
    // Task 2: account as class

    //      2a
    cout << "==============\n";
    cout << "\nTask2a:"
         << "\nFilling vector of class objects, using local class object:\n";


    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";
    

    cout << "\nTask2c:\n"
         << "output using output operator as friend without getters\n";


    cout << "\nTask2d:\n"
         << "Filling vector of class objects, using temporary class object:\n";

    
    cout << "\nTask2e:\n"
         << "Filling vector of class objects, using emplace_back:\n";

    
    cout << "==============\n"
         << "\nTask 3:\nAccounts and Transaction:\n";


    cout << "==============\n"
         << "\nTask 4:\nTransaction nested in public section of Account:\n";

    
    cout << "==============\n"
         << "\nTask 5:\nTransaction nested in private section of Account:\n";

    
} // main
