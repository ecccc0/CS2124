
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
size_t max(size_t a, size_t b);

class BigUnsigned
{
    public:
    BigUnsigned(const int val = 0)
    {
        int cur, val_copy = val;
        if (val == 0)
        {
            // default value
            value.push_back(0);
        }
        while (val_copy != 0)
        {
            cur = val_copy % 10;
            val_copy /= 10;
            value.push_back(cur);
            // append the current digit to the vector,
            // starting from the least significant digit
        }
    }
    BigUnsigned(const string& digits)
    {
        size_t first_non_zero = firstNonZeroInStr(digits);
        if (digits[0] < 48 || digits[0] > 57)
        {
            // if the first character is not a digit
            value.push_back(0);
        }
        else
        {
            for (size_t i = 0; i < digits.size() - first_non_zero - 1; i++)
            {
                if (digits[digits.size() - i - 1] < 48 ||
                    digits[digits.size() - i - 1] > 57)
                {
                    // the first non-ditig character encountered
                    break;
                }
                value.push_back(digits[digits.size() - i - 1] - 48);
                // append the current digit to the vector, converting it to an int
            }
        }
    }
    // friend functions
    friend ostream& operator<<(ostream& os, const BigUnsigned& rhs);
    friend bool operator==(const BigUnsigned& lhs, const BigUnsigned& rhs);
    friend BigUnsigned operator+(const BigUnsigned& lhs, const BigUnsigned& rhs);
    friend bool operator!=(const BigUnsigned& lhs, const BigUnsigned& rhs);
    friend bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs);
    friend bool operator>(const BigUnsigned& lhs, const BigUnsigned& rhs);
    friend bool operator<=(const BigUnsigned& lhs, const BigUnsigned& rhs);
    friend bool operator>=(const BigUnsigned& lhs, const BigUnsigned& rhs);

    BigUnsigned operator+=(const BigUnsigned& rhs)
    {
        size_t max_size = max(value.size(), rhs.value.size());
        int carry = 0;

        // Make sure both vectors are the same size
        if (value.size() < max_size) {
            value.resize(max_size, 0);
        }

        // Perform the addition in-place
        for (size_t i = 0; i < max_size; ++i) {
            int digitA = value[i];
            int digitB = (i < rhs.value.size()) ? rhs.value[i] : 0;

            int sum = digitA + digitB + carry;
            value[i] = sum % 10; // Update the current digit
            carry = sum / 10;     // Calculate the carry
        }

        // If there's a leftover carry, append it as a new digit
        if (carry > 0) {
            value.push_back(carry);
        }

        return *this;
    }

    BigUnsigned operator++()
    {
        this->operator+=(BigUnsigned(1));
        // just call the += operator with 1
        return *this;
    }

    BigUnsigned operator++(int dummy)
    {
        BigUnsigned original(*this);
        ++(*this);
        return original;
        // support for postfix increment
    }

    explicit operator bool() const
    {
        return (*this != BigUnsigned(0));
        // returns true if the value is not zero
    }
    private:
    vector<int> value; 
};

BigUnsigned operator+(const BigUnsigned& lhs, const BigUnsigned& rhs)
{
    // store the result in a new BigUnsigned object
    BigUnsigned result;
    result.value.pop_back();
    int carry = 0;
    size_t max_size = max(lhs.value.size(), rhs.value.size());

    for (size_t i = 0; i < max_size; ++i) {
        int digitA = (i < lhs.value.size()) ? lhs.value[i] : 0;
        int digitB = (i < rhs.value.size()) ? rhs.value[i] : 0;
        int sum = digitA + digitB + carry;
        // add the two digits and the carry
        result.value.push_back(sum % 10);
        // append the current one's digit to the result
        carry = sum / 10;
        // compute the carry
    }

    if (carry > 0) {
        result.value.push_back(carry);
        // if there is a carry left, append it to the result
    }

    return result;
}

ostream& operator<<(ostream& os, const BigUnsigned& rhs)
{
    for (size_t i = 0; i < rhs.value.size(); i++)
    {
        // backwards iteration to print the number in the correct order
        cout << rhs.value[rhs.value.size() - i - 1];
    }
    return os;
}


bool operator==(const BigUnsigned& lhs, const BigUnsigned& rhs)
{
    if (lhs.value.size() != rhs.value.size())
    {
        // if the sizes are different, the numbers are different
        return false;
    }
    for (size_t i = 0; i < lhs.value.size(); i++)
    {
        if (lhs.value[i] != rhs.value[i])
        {
            // if any of the digits are different, the numbers are different
            return false;
        }

    }
    return true;
}

bool operator!=(const BigUnsigned& lhs, const BigUnsigned& rhs)
{
    return !(lhs == rhs);
    // the negation of the equality operator
}

bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs)
{
    if (lhs.value.size() > rhs.value.size())
    {
        // if the size of the lhs is greater than the rhs, it is greater
        return false;
    }
    else if (lhs.value.size() < rhs.value.size())
    {
        return true;
        // if the size of the lhs is less than the rhs, it is less
    }
    for (size_t i = 0; i < lhs.value.size(); i--)
    {
        // if the sizes are the same, iterate through the digits
        // from the most significant digit
        // if the lhs digit is less than the rhs digit, the lhs is less
        if (lhs.value[i] < rhs.value[i])
        {
            return true;
        }
    }
    return false;
}

bool operator>(const BigUnsigned& lhs, const BigUnsigned& rhs)
{
    // similar logic to the less than operator
    if (lhs.value.size() < rhs.value.size())
    {
        return false;
    }
    else if (lhs.value.size() > rhs.value.size())
    {
        return true;
    }
    for (size_t i = 0; i < lhs.value.size(); i++)
    {
        if (lhs.value[i] > rhs.value[i])
        {
            return true;
        }
    }
    return false;
}

bool operator<=(const BigUnsigned& lhs, const BigUnsigned& rhs)
{
    // negation of the greater than operator
    return !(lhs > rhs);
}

bool operator>=(const BigUnsigned& lhs, const BigUnsigned& rhs)
{
    // negation of the less than operator
    return !(lhs < rhs);
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

// returns the index of the first non-zero character in the string
// used in the string constructor to skip leading zeros
size_t firstNonZeroInStr(const string& str) {
    for (size_t i = 0; i < str.size(); i++) {
        if (i != 0) {
            return i;
        }
    }
    return 0;
}

// returns the larger of the two values
// used in the addition operator to determine the size of the result
size_t max(size_t a, size_t b) {
    return (a > b) ? a : b;
}