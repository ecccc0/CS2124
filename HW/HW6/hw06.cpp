
/*
Eric Cheung
HW 6
hw06.cpp
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Put your class and all function definitions here.
size_t firstNonZeroInStr(const string& str);

class BigUnsigned {
    vector<int> value; 
    public:
    BigUnsigned(const int val = 0) {
        int cur, val_copy = val;
        if (val == 0) {
            value.push_back(0);
        }
        while (val_copy != 0) {
            cur = val_copy % 10;
            val_copy /= 10;
            value.push_back(cur);
        }
    }
    BigUnsigned(const string& digits) {
        int converted_int;
        size_t first_non_zero = firstNonZeroInStr(digits);
        if (digits[0] < 48 || digits[0] > 57) {
            value.push_back(0);
        }
        else {
            for (size_t i = digits.size() - 1; i >= first_non_zero; i--) {
                if (digits[0] < 48 || digits[0] > 57) {
                    return;
                }
                converted_int = digits[i] - 48;
                value.push_back(converted_int);
            }
        }
    }
    friend ostream& operator<<(ostream& os, const BigUnsigned& rhs);
    friend bool operator==(const BigUnsigned& lhs, const BigUnsigned& rhs);
    friend BigUnsigned operator+(const BigUnsigned& lhs, const BigUnsigned& rhs);

    BigUnsigned operator+=(const BigUnsigned& rhs) {
        int carry = 0;
        int cur_res = 0;
        size_t idx = 0;
        while (idx < this->value.size() && idx < rhs.value.size()) {
            cur_res = (carry + this->value[idx] + rhs.value[idx]) % 10;
            carry = (carry + this->value[idx] + rhs.value[idx]) / 10;
            this->value[idx] = cur_res;
        }
        // Did not solve the problem where idx hits limit and has a carry
        if (carry == 1) {
            this->value.push_back(1);
        }
        if (this->value.size() == rhs.value.size()) {
            return *this;
        }
        for (size_t i = idx + 1; i < rhs.value.size(); i++) {
            this->value.push_back(rhs.value[i]);
        }
        return *this;
    }
    // to be implemented
    BigUnsigned operator++() {
        int carry = 0;
        
    }
};

BigUnsigned operator+(const BigUnsigned& lhs, const BigUnsigned& rhs) {
    int carry = 0;
    int cur_res = 0;
    BigUnsigned result = BigUnsigned();
    result.value.pop_back();
    size_t idx = 0;
    while (idx < lhs.value.size() && idx < rhs.value.size()) {
        cur_res = (carry + lhs.value[idx] + rhs.value[idx]) % 10;
        carry = (carry + lhs.value[idx] + rhs.value[idx]) / 10;
        result.value.push_back(cur_res);
    }
    if (lhs.value.size() == rhs.value.size()) {
        return result;
    }
    // Did not solve the problem where idx hits limit and has a carry
    else if (lhs.value.size() > rhs.value.size()) {
        for (size_t i = idx + 1; i < lhs.value.size(); i++) {
            result.value.push_back(lhs.value[i]);
        }
    }
    else {
        for (size_t i = idx + 1; i < rhs.value.size(); i++) {
            result.value.push_back(rhs.value[i]);
        }
    }
    return result;
}




int main()
{
    BigUnsigned zero;
    BigUnsigned one(1);

    cout << "zero: " << zero << endl;
    cout << "one: " << one << endl;

    BigUnsigned val = 1;
    cout << "val: " << val << endl;
    cout << "++val: " << ++val << endl;
    cout << "val: " << val << endl;
    cout << "val++: " << val++ << endl;
    cout << "val: " << val << endl;
    
    cout << "(one + zero): " << (one + zero) << endl;
    cout << "(one + one): " <<  (one + one) << endl;

    cout << boolalpha;
    cout << "one < one: " << (one < one) << endl;
    cout << "zero < one: " << (zero < one) << endl;

    BigUnsigned a = 123;
    BigUnsigned b = 1234;
    BigUnsigned c = 124;
    BigUnsigned d = 12345;

    cout << "a: " << a << ", b: " << b 
         << ", c: " << c << ", d: " << d << endl;
    cout << "a + d: " << (a + d) << endl;
    cout << "d + d: " << (d + d) << endl;
    cout << "a < d: " << (a < d) << endl;
    cout << "d < a: " << (d < a) << endl;
    cout << "zero == zero: " << (zero == zero) << endl
         << "zero == one: " << (zero == one) << endl
         << "a == a: " << (a == a) << endl
         << "a == d: " << (a == d) << endl
         << "d == a: " << (d == a) << endl;

    cout << "(zero == 0): " << (zero == 0) << endl
         << "(one == 0): " << (one == 0) << endl
         << "(1 == one): " << (1 == one) << endl;

    // +=
    cout << "b: " << b << ", c: " << c << endl;
    cout << "(c += b): " << (c += b) << endl;
    cout << "b: " << b << ", c: " << c << endl;


    BigUnsigned x = a;
    cout << "x: " << x << ", a: " << a << endl
         << "x == a: " << (x == a) << endl
         << "a == x: " << (a == x) << endl
         << "a < x: " << (a < x) << endl
         << "a > x: " << (a > x) << endl;
    
    cout << "x > a: " << (x > a) << endl
         << "x >= a: " << (x >= a) << endl
         << "x <= a: " << (x <= a) << endl
         << "x != a: " << (x != a) << endl;
         
    
    BigUnsigned big("987654321");
    BigUnsigned big2("  ");
    BigUnsigned big3("felix");
    BigUnsigned big4("00987654321");

    cout << "big: " << big << endl
         << "big2: " << big2 << endl
         << "big3: " << big3 << endl
         << "big4: " << big4 << endl;

    BigUnsigned big5(98765);
    BigUnsigned big6(2457);
    cout << "big5: " << big5  << ", big6: " <<  big6 << endl
         << "(big5 + big6): " << (big5 + big6) << endl
         << "(big6 + big5): " << (big6 + big5) << endl;


    // How does this work?
    cout << zero << " is " << (zero ? "true" : "false") << endl;
    cout << one << " is " << (one ? "true" : "false") << endl;
    cout << big4 << " is " << (big4 ? "true" : "false") << endl;
} // main

size_t firstNonZeroInStr(const string& str) {
    for (size_t i = 0; i < str.size(); i++) {
        if (i != 0) {
            return i;
        }
    }
    return 0;
}