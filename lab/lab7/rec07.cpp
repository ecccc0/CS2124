
/*
  rec07.cpp
  Eric Cheung
  Lab 7
 */

#include <iostream>
using namespace std;

int greatestCommonDivisor(int x, int y);

// Put your Rational class here.

class Rational {
    int numerator;
    int denominator;
    public:
    Rational(int numerator = 0, int denominator = 1) : numerator(numerator)
        , denominator(denominator) {
        normalize(*this);
    }
    
    Rational& operator+=(const Rational& rhs) {
        numerator = numerator * rhs.denominator + rhs.numerator * denominator;
        denominator *= rhs.denominator;
        normalize(*this);
        return *this;
    }

    Rational& operator++() {
        numerator += denominator;
        normalize(*this);
        return *this;
    }

    Rational operator++(int dummy) {
        Rational original(*this);
        ++(*this);
        normalize(*this);
        return original;
    }

    explicit operator bool() const {
        return numerator != 0;
    }

    friend ostream& operator<<(ostream& os, const Rational& rhs);
    friend istream& operator>>(istream& is, Rational& rhs);
    friend bool operator==(const Rational& lhs, const Rational& rhs);
    friend bool operator<(const Rational& lhs, const Rational& rhs);
    friend void normalize(Rational& rhs);
};
// Any functions that are not members and not friends should have
// prototypes here and their definitions after main.

ostream& operator<<(ostream& os, const Rational& rhs) {
    os << rhs.numerator << '/' << rhs.denominator;
    return os;
}

istream& operator>>(istream& is, Rational& rhs) {
    is >> rhs.numerator;
    is.ignore(1);
    is >> rhs.denominator;
    normalize(rhs);
    return is;
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator;
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return lhs.numerator * rhs.denominator < rhs.numerator * lhs.denominator;
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return lhs < rhs || lhs == rhs;
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return !(lhs <= rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return !(lhs < rhs);
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational result(lhs);
    result += rhs;
    return result;
}

void normalize(Rational& rhs) {
    int gcd = greatestCommonDivisor(rhs.numerator, rhs.denominator);
    rhs.numerator /= gcd;
    rhs.denominator /= gcd;
    if (rhs.denominator < 0) {
        rhs.denominator *= -1;
        rhs.numerator *= -1;
    }
}

Rational& operator--(Rational& rhs);
Rational operator--(Rational& rhs, int dummy);

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
    cout << "a += b: " << (a += b) << endl;	// Implement as member
    cout << "a = " << a << endl;
    
    // Implement + as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;
    
    // How does this manage to work?
    // It does NOT require writing another == operator. 
    cout << "1 == one: " << boolalpha << (1 == one) << endl;
    
    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

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
    // doing the right thing? Why shouldn't it compile?
    // cout << "a-- -- = " << (a-- --) << endl;
    cout << "-- --a: "<< (-- --a) << endl;
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
}

int greatestCommonDivisor(int x, int y)
{
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

// Any functions that are not members and not friends should have
// their definitions here...
Rational& operator--(Rational& rhs) {
    rhs += -1;
    normalize(rhs);
    return rhs;
}

Rational operator--(Rational& rhs, int dummy) {
    Rational original(rhs);
    --rhs;
    normalize(rhs);
    return original;
}
