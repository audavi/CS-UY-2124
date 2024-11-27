/*
  Emily Lopez
  rec07.cpp
  CS2124
  Implement the class Rational, so that the following program works.
 */
#include <iostream>
using namespace std;

int greatestCommonDivisor(int x, int y);

// Put your Rational class here.
class Rational {
    friend ostream& operator<<(ostream& os , const Rational& r);
    friend istream& operator>>(istream& is, Rational& r);
    friend bool operator==(const Rational& lhs, const Rational& rhs);
    friend bool operator<(const Rational& lhs, const Rational& rhs);
public:
    // constructor
    Rational(int numerator = 0, int denominator = 1) : numerator(numerator), denominator(denominator) {
        normalize();
    }
    Rational& operator+=(const Rational& rhs) {
        if (denominator == rhs.denominator) {
            numerator += rhs.numerator;
        }
        else {
            numerator = numerator *(rhs.denominator) + (rhs.numerator)*denominator;
            denominator = denominator * (rhs.denominator);
        }
        normalize();
        return *this;
    }
    //pre-increment
    Rational& operator++() {
        numerator += denominator;
        return *this;
    }
    //post-increment
    Rational operator++(int dummy) {
        Rational original = *this;
        numerator += denominator;
        return original;
    }
    explicit operator bool() const {
        return !(numerator == 0);
    }
    // normalize a rational number
    void normalize() {
        if (denominator == 0) {
            cout << "The denominator cannot be 0" << endl;
        }
        // only the numerator may be negative
        if (denominator < 0) {
            denominator = -denominator;
            numerator = -numerator;
        }
        int frac = greatestCommonDivisor(abs(numerator), abs(denominator));
        // if not in simplest form, divide by gcd
        if (frac > 1) {
            numerator /= frac;
            denominator /= frac;
        }

    }
private:
    int numerator;
    int denominator;
};
// Any functions that are not members and not friends should have
// prototypes here and their definitions after main.

Rational operator+(const Rational& lhs, const Rational& rhs);
bool operator==(const Rational& lhs, const Rational& rhs);
bool operator<(const Rational& lhs, const Rational& rhs);
Rational& operator--(Rational& rhs);
Rational operator--(Rational& rhs, int dummy);
bool operator!=(const Rational& lhs, const Rational& rhs);
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

//output operator
ostream& operator<<(ostream& os , const Rational& r) { // output operator
    cout << r.numerator << "/" << r.denominator << endl;
    return os;
}
//input operator
istream& operator>>(istream& is, Rational& r) {
    char slash;
    is >> r.numerator >> slash >> r.denominator;
    r.normalize();
    return is;
}
Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational newRational = lhs;
    newRational += rhs;
    return newRational;
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator;
}
bool operator<(const Rational& lhs, const Rational& rhs) {
    return lhs.numerator*rhs.denominator < rhs.numerator*lhs.denominator;
}

// pre-decrement
Rational& operator--(Rational& rhs) {
    rhs += -1;
    return rhs;
}
// post-decrement
Rational operator--(Rational& rhs, int dummy) {
    Rational original = rhs;
    rhs += -1;
    return original;
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}
bool operator<=(const Rational& lhs, const Rational& rhs) {
    return lhs == rhs || lhs < rhs;
}
bool operator>(const Rational& lhs, const Rational& rhs) {
    return rhs < lhs;
}
bool operator>=(const Rational& lhs, const Rational& rhs) {
    return lhs == rhs || lhs > rhs;
}