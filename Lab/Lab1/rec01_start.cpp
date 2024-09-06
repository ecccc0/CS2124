/*
  rec01_start.cpp
  fall 2024
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//
// main
//
int main() { // Yes, it has to have an int for the return type
    //
    // Output
    //

    // Task 1. Printing hello ...  No use of "using namespace"
    std::cout << "hello CS2124" << std::endl;

    // Task 2  Printing hello ...  Using "using namespace"
    using namespace std;
    cout << "hello CS2124" << std::endl;


    //
    // Types and variables
    //

    // Task 3  Displaying uninitialized variable
    int x;
    cout << x << endl;
    
    // Task 4 Use the sizeof function to see the size in bytes of
    //        different types on your machine.
    int y = 17, z = 2000000017;
    double pie = 3.14159;
    cout << sizeof(x) << " "<< sizeof(y) << " " << sizeof(z) << " " << sizeof(pie) << endl;
  
    
    // Task 5  Attempt to assign the wrong type of thing to a variable
    // x = "felix";


    //
    // Conditions
    //

    // Task 6  Testing for a range
    if (y<=20 && y >= 10){
      cout << "y is between 10 and 20" << endl;
    }else{
      cout << "y is not between 10 and 20" << endl;
    }
    

    //
    // Loops and files
    //

    // Task 7  Looping, printing values 10 to 20 inclusive

    // First with a for loop
    for (int i = 10 ; i <= 20; ++i){
      cout << i << " ";
    }cout << endl;
    // Then with a while loop
    int i = 10;
    while (i <= 20){
      cout << i << " ";
      ++i;
    }cout << endl;
    // Finally with a do-while loop
    i = 10;
    do{
      cout << i << " ";
      ++i;
    }while (i <= 20);
    cout << endl;


    // Task 8  Looping to successfully open a file, asking user for the name
    ifstream ifs;
    string filename;
    do{
      cin >> filename;
      ifs.open(filename);
      if (!ifs){
        cout << "Failed to open file \"" << filename << "\"\n";
      }
    }while(!ifs);

    // Task 9  Looping, reading file word by "word".
    string word;
    while (ifs >> word){
      cout << word << " ";
    }cout << endl;
    ifs.close();

    // Task 10 Open a file of integers, read it in, and display the sum.
    do{
      ifs.open("integers.txt");
    }while(!ifs);
    int sum, n;
    while (ifs >> n){
      sum += n;
    }
    ifs.close();
    cout << sum << endl;

    // Taks 11 Open and read a file of integers and words. Display the sum.
    do{
      ifs.open("mixed.txt");
    }while(!ifs);
    sum = 0;
    while (ifs >> n){
      sum += n;
    }
    ifs.close();
    cout << sum << endl;

    //
    // Vectors
    //

    // Task 12 Filling a vector of ints
    vector<int> v;
    for (int i = 10; i <= 100; i+=2){
      v.push_back(i);
    }
    
    // Task 13 Displaying the vector THREE times
    //         a) using the indices,
    for (size_t i = 0; i < v.size(); ++i){
      cout << v[i] << " ";
    }cout << endl;
    //         b) using a "ranged for"
    for (int x : v){
      cout << x << " ";
    }cout << endl;
    //         c) using indices again but backwards
    for (size_t i = 1; i <= v.size(); ++i){
      cout << v[v.size()-i] << " ";
    }cout << endl;

    // Task 14. Initialize a vector with the primes less than 20. 
    vector<int> prime{2, 3, 5, 7, 11, 13, 17, 19};
    for (int x : prime){
      cout << x << " ";
    }cout << endl;
} // main

