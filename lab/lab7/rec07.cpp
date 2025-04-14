
/*
Eric Cheung
rec07.cpp
Lab 7
*/

#include <iostream>
using namespace std;

int greatestCommonDivisor(int x, int y);

// Put your Rational class here.
class Rational {
public:
    Rational(int numerator = 0, int denominator = 1) : numerator(numerator)
    , denominator(denominator) 
    {
        normalize();
    }

    friend ostream& operator<<(ostream& os, const Rational& rhs);
    friend istream& operator>>(istream& is, Rational& rhs);
    // friend void normalize(Rational& rhs);
    friend bool operator==(const Rational& lhs, const Rational& rhs);
    friend bool operator<(const Rational& lhs, const Rational& rhs);

    // int getNumerator()
    // {
    //     return numerator;
    // }

    // int getDenominator()
    // {
    //     return denominator;
    // }
    
    // void setNumerator(int val)
    // {
    //     numerator = val;
    // }

    // void setDenominator(int val)
    // {
    //     denominator = val;
    // }

    Rational& operator+=(const Rational& rhs)
    {
        numerator = numerator * rhs.denominator + rhs.numerator * denominator;
        denominator *= rhs.denominator;
        normalize();
        return *this;
    }


    Rational& operator++()
    {
        numerator += denominator;
        // normalize();
        return *this;
    }

    Rational operator++(int dummy)
    {
        Rational original(*this);
        // operator++();
        numerator += denominator;
        // normalize();
        return original;
    }

    explicit operator bool() const
    {
        return numerator != 0;
    }



private:
    int denominator;
    int numerator;

    void normalize() 
    {
        int gcd = greatestCommonDivisor(abs(numerator), abs(denominator));
        numerator /= gcd;
        denominator /= gcd;
        if (denominator < 0)
        {
            numerator *= -1;
            denominator *= -1;
        }
    }
};

// Any functions that are not members and not friends should have
// prototypes here and their definitions after main.
Rational operator+(const Rational& lhs, const Rational& rhs);
bool operator!=(const Rational& lhs, const Rational& rhs);
Rational& operator--(Rational& rhs);
Rational operator--(Rational& rhs, int dummy);
bool operator<=(const Rational& lhs, const Rational& rhs);

bool operator>(const Rational& lhs, const Rational& rhs);

bool operator>=(const Rational& lhs, const Rational& rhs);


int main()
{
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;	// Implement += as a member
    cout << "a = " << a << endl;
    
    // Implement + as non-member, but NOT as a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;
    
    // How does this manage to work?
    // It does NOT require writing another == operator. 
    cout << "1 == one: " << boolalpha << (1 == one) << endl;
    
    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    //
    // PLEASE CHECK OUT NOW
    //
    
    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing? Why SHOULDN'T it compile?
    //cout << "a-- -- = " << (a-- --) << endl;
    cout << "a = " << a << endl;


    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    } 

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    } 

    cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalves(3, 2);
    Rational minusFive(-5);
    cout << twoFifths << " < " << threeHalves << " : " 
         << (twoFifths < threeHalves) << endl;
    cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
    cout << threeHalves << " < " << twoFifths << " : "
         << (threeHalves < twoFifths) << endl;
    cout << threeHalves << " > " << threeHalves << " : "
         << (threeHalves > threeHalves) << endl;
    cout << threeHalves << " >= " << threeHalves << " : "
         << (threeHalves >= threeHalves) << endl;
    cout << minusFive << " >= " << threeHalves << " : "
         << (minusFive >= threeHalves) << endl;
} // main

int greatestCommonDivisor(int x, int y)
{
    while (y != 0) 
    {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
} // greatestCommonDivisor

// Any functions that are not members and not friends should have
// their definitions here...




ostream& operator<<(ostream& os, const Rational& rhs)
{
    os << rhs.numerator << '/' << rhs.denominator;
    return os;
}

istream& operator>>(istream& is, Rational& rhs)
{
    char slash;
    is >> rhs.numerator >> slash >> rhs.denominator;
    rhs.normalize();
    return is;
}

Rational operator+(const Rational& lhs, const Rational& rhs)
{
    Rational newRational;
    newRational += lhs;
    newRational += rhs;
    return newRational;
}

bool operator==(const Rational& lhs, const Rational& rhs)
{
    return lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator;
}

bool operator!=(const Rational& lhs, const Rational& rhs)
{
    return !(lhs == rhs);
}

bool operator<(const Rational& lhs, const Rational& rhs)
{
    return lhs.numerator * rhs.denominator < lhs.denominator * rhs.numerator;
}

Rational& operator--(Rational& rhs)
{
    rhs += Rational(-1);
    // rhs.normalize();
    return rhs;
}

Rational operator--(Rational& rhs, int dummy)
{
    Rational original(rhs);
    rhs += Rational(-1);
    // rhs.normalize();
    return original;
}

bool operator<=(const Rational& lhs, const Rational& rhs)
{
    return lhs == rhs || lhs < rhs;
}

bool operator>=(const Rational& lhs, const Rational& rhs)
{
    return !(lhs < rhs);
}

bool operator>(const Rational& lhs, const Rational& rhs)
{
    return !(lhs <= rhs);
}