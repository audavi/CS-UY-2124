/*
 Emily Lopez
 Protector.cpp
*/
#include "Noble.h"
#include "Protector.h"
using namespace std;

namespace WarriorCraft {
    // protector implementation
    // constructor
    Protector::Protector(const string& name, double hisStrength)
      : name(name), hisStrength(hisStrength), lord(nullptr) {}
    // strength getter
    double Protector::getStrength() const { return hisStrength; }
    // modify strength to a new strength
    void Protector::setStrength(double newStrength)
    { hisStrength = newStrength; }
    // strength setter
    void Protector::setStatus(double strength)
    { hisStrength = strength; }
    // lord setter
    void Protector::setLord(Lord* lordPtr){ lord = lordPtr;}
    // strength getter
    Lord* Protector::getLord() const { return lord; }
    // lord name getter
    const string& Protector::getName() const { return name; }
    // allows a warrior to runaway from their Noble
    bool Protector::runaway() {
        if (hisStrength == 0) {
            cout << name << " is already dead!" << endl;
            return false;
        }
        if (!lord) {
            cout << name << " doesn't have a lord!";
            return false;
        }
        string lordName = lord->getName();
        if (lord->remove(*this)) {
            cout << name << " flees in terror, abandoning his lord, "
                 << lordName << endl;
            return true;
        }
        return false;
    }
    // output operator
    ostream& operator<<(ostream& os, const Protector& theProtector) {
          os << theProtector.name <<
              " has a strength " << theProtector.hisStrength;
          return os;
      }
    // wizard implementation
    void Wizard::defend() const {
        cout << "POOF!" << endl;
    }
    // warrior implementation
    void Warrior::defend() const {
        cout << getName() << " says: Take that in the name of my lord, "
             << getLord()->getName() << endl;
    }
    // archer implementation
    void Archer::defend() const {
        cout << "TWANG! ";
        Warrior::defend();
    }
    // swordsman implementation
    void Swordsman::defend() const {
        cout << "CLANG! ";
        Warrior::defend();
    }
}