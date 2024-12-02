/*
  Emily Lopez
  hw06.cpp
  Purpose: Representing unsigned integers in
  a BigUnsigned class.
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// class BigUnsigned represents an unsigned integer
// that can take in a string parameter or int parameter.
class BigUnsigned {
     friend ostream& operator<<(ostream& os, const BigUnsigned&
                                             unsignedNumber);
     friend bool operator==(const BigUnsigned& lhs, const BigUnsigned& rhs);
     friend bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs);
     friend BigUnsigned operator+(const BigUnsigned& lhs, const BigUnsigned& rhs);
public:
     BigUnsigned() {
          digits.push_back(0);
     }
     BigUnsigned(int num) {
          if (num == 0) {
               digits.push_back(0);
          } else {
               while (num > 0) {
                    digits.push_back(num % 10);
                    num /= 10;
               }
          }
     }
     BigUnsigned(const string& str) {
          digits.clear();
          bool digitFound = false;
          for (int i = str.size() - 1; i >= 0; --i) {
               char character = str[i];
               if (isdigit(character)) {
                    int digit = character - '0'; // character to integer

                    if (digit != 0 || digitFound) {
                         digits.push_back(digit);
                         digitFound = true;
                    }
               }
          }
          //check for leading zeros
          while (digits.size() > 1 && digits.back() == 0) {
               digits.pop_back();
          }
          if (!digitFound) {
               digits.push_back(0);
          }
     }
     // Description: Overloading the pre ++ operator
     BigUnsigned& operator++() {
          int carry = 1;
          for (size_t i = 0; i < digits.size(); ++i){
               digits[i] += carry;
               carry = digits[i] / 10;
               digits[i] %= 10;
          }
          if (carry > 0){
               digits.push_back(carry);
          }
          return *this;
     }
     // Description: Overloading the post ++ operator
     // Parameter: int dummy: unused value
     BigUnsigned operator++(int dummy) {
          BigUnsigned original = *this;
          original.digits = digits;
          ++(*this);
          return original;
     }
     // Description: Overloading the += operator
     // Parameter: const BigUnsigned& other: another unsigned number
     BigUnsigned& operator+=(const BigUnsigned& rhs) {
          *this = *this + rhs;
          return *this;
     }
     // Description: Overloading the bool operator
     explicit operator bool() const {
          // vector cannot be empty and first digit cannot be 0
          return digits.size() > 0 && digits[digits.size() - 1] != 0;
     }
private:
     vector<int> digits;
};
// Description: Overloading the + operator
// Parameter: const BigUnsigned& other: another unsigned number
BigUnsigned operator+(const BigUnsigned& lhs, const BigUnsigned& rhs) {
     BigUnsigned result;
     result.digits.clear();
     int carry = 0;
     size_t maxSize;
     if (lhs.digits.size() > rhs.digits.size()) {
          maxSize = lhs.digits.size();
     } else {
          maxSize = rhs.digits.size();
     }
     for (size_t i = 0; i < maxSize || carry; ++i) {
          int sum = carry;

          if (i < lhs.digits.size()) {
               sum += lhs.digits[i];
          }
          if (i < rhs.digits.size()) {
               sum += rhs.digits[i];
          }
          result.digits.push_back(sum % 10);
          carry = sum / 10;
     }
     while (result.digits.size() > 1 &&
          result.digits.back() == 0) {
          result.digits.pop_back();
          }
     return result;
}
// Description: Overloading output operator to
//              display an unsigned number
// Parameter: ostream& os: output stream
//            const BigUnsigned& unsignedNumber: an unsigned integer
ostream& operator<<(ostream& os, const BigUnsigned& unsignedNumber) {
     for (size_t i = unsignedNumber.digits.size(); i > 0 ; i--) {
          os << unsignedNumber.digits[i-1];
     }
     return os;
}
// Description: Overloading the == operator
// Parameter: const BigUnsigned& lhs: left unsigned number
//            const BigUnsigned& rhs: right unsigned number
bool operator==(const BigUnsigned& lhs, const BigUnsigned& rhs) {
     return lhs.digits == rhs.digits;
}
// Description: Overloading the != operator
// Parameter: const BigUnsigned& lhs: left unsigned number
//            const BigUnsigned& rhs: right unsigned number
bool operator!=(const BigUnsigned& lhs, const BigUnsigned& rhs) {
     return !(lhs == rhs);
}
// Description: Overloading the < operator
// Parameter: const BigUnsigned& lhs: left unsigned number
//            const BigUnsigned& rhs: right unsigned number
bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs) {
     if (lhs.digits.size() != rhs.digits.size()){
          return lhs.digits.size() < rhs.digits.size();
     }
     for (int i=0; i<lhs.digits.size(); i++) {
          if (lhs.digits[i] != rhs.digits[i]){
               return lhs.digits[i] < rhs.digits[i];
          }
     }
     return false;
}
// Description: Overloading the <= operator
// Parameter: const BigUnsigned& lhs: left unsigned number
//            const BigUnsigned& rhs: right unsigned number
bool operator<=(const BigUnsigned& lhs, const BigUnsigned& rhs) {
     return (lhs < rhs) || (lhs == rhs);
}
// Description: Overloading the > operator
// Parameter: const BigUnsigned& lhs: left unsigned number
//            const BigUnsigned& rhs: right unsigned number
bool operator>(const BigUnsigned& lhs, const BigUnsigned& rhs) {
     return !(lhs <= rhs);
}
// Description: Overloading the >= operator
// Parameter: const BigUnsigned& lhs: left unsigned number
//            const BigUnsigned& rhs: right unsigned number
bool operator>=(const BigUnsigned& lhs, const BigUnsigned& rhs) {
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