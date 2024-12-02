/*
 Emily Lopez
 Noble.cpp
*/
#include "Noble.h"
#include "Protector.h"
using namespace std;

namespace WarriorCraft {
    // noble implementation
    // constructor
    Noble::Noble(const string &name)
    : name(name), alive(true) {}
    // name getter
    const string Noble::getName() const { return name;}
    // status setter
    void Noble::setStatus(){ alive= !alive; }
    // status getter
    bool Noble::getStatus() const { return alive; }
    // update to dead status
    void Noble::death() {
        alive = false;
        updateStrength(1, 1);
    }
    // display a battle
    void Noble::battle(Noble& rhs) {
        cout << name << " battles " << rhs.name << endl;
        if (!alive && !rhs.alive) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else if (!alive && rhs.alive) {
            rhs.defend();
            cout << "He's dead, " << rhs.name << endl;
        } else if (alive && !rhs.alive) {
            defend();
            cout << "He's dead, " << name << endl;
        } else {  // both nobles are alive
            int noble1 = getStrength();
            int noble2 = rhs.getStrength();
            defend();
            rhs.defend();
            // nolbes have same strength
            if (noble1 == noble2) {
                death();
                rhs.death();
                cout << "Mutual Annihilation: " << name << " and " <<
                    rhs.name << " die at each other's hands" << endl;
            } else if (noble1 > noble2) {
                updateStrength(noble1, noble2);
                rhs.death();
                cout << name << " defeats " << rhs.name << endl;
            } else {  // noble1 < noble2 strength
                rhs.updateStrength(noble2, noble1);
                death();
                cout << rhs.name << " defeats " << name << endl;
            }
        }
    }
    //output operator
    ostream& operator<<(ostream& os, const Noble& theNoble) {
        os << theNoble.getName();
        theNoble.displayNoble(os);
        return os;
    }


    // lord implementation
    Lord::Lord(const string& name) : Noble(name) {}
    // hire
    bool Lord::hires(Protector& aProtector) {
        if (!getStatus()) { // status = dead
            cout << getName() << " failed to hire "
            << aProtector.getName() << "." << endl;
            return false;
        }
        if (aProtector.getLord()) { //protector already hired
            cout << getName() << " failed to hire "
            << aProtector.getName() << "." << endl;
            return false;
        }
        aProtector.setLord(this);
        army.push_back(&aProtector);
        return true;
    }
    // fire
    bool Lord::fires(Protector& aProtector) {
        if (!getStatus()) { // lord is dead
            return false;
        }
        if (remove(aProtector)) {
            cout << aProtector.getName() <<
                ", you don't work for me anymore! -- "
                 << getName() << "." << endl;
            return true;
        }
        return false; // protector not fired
    }
    // strength getter
    double Lord::getStrength() const {
        double total = 0;
        for (const Protector *const &ptr: army) {
            total += ptr->getStrength();
        }
        return total;
    }
    // strength setter
    void Lord::updateStrength(double winner, double loser) {
        double newArmyStrength = 0;
        for (Protector* currPtr : army) {
            //update every warrior's strength equal
            //to ratio of enemy's strength
            double newStrength = currPtr->getStrength() * (winner - loser)/winner;
            currPtr->setStrength(newStrength);
        }
    }
    // remove a protector from army
    bool Lord::remove(Protector& aProtector) {
        for (size_t i = 0; i < army.size(); ++i) {
            if (army[i] == &aProtector) {
                aProtector.setLord(nullptr); // remove lord
                break;
            }
        }
        if (size_t i = 0 < army.size()) {
            for (size_t i =0; i < army.size() - 1; ++i) {
                army[i] = army[i + 1];
            }
            army.pop_back(); // removed from army
            return true;
        }
        cout << aProtector.getName() << " is not hired by "
        << getName() << "!" << endl;
        return false;
    }
    // defend
    void Lord::defend() const {
        for (Protector* currPtr : army) {
            currPtr->defend();
        }
    }
    // display a Noble using output operator (with army)
    void Lord::displayNoble(ostream& os) const {
        os << " has an army of size: " << army.size();
        for (int i{}; i < army.size(); i++){
            os << "\n\t" << *army[i];
        }
    }


    // PersonWithStrengthToFight implementation
    // constructor
    PersonWithStrengthToFight::PersonWithStrengthToFight(const string& name,
        double hisStrength) : Noble(name), hisStrength(hisStrength) {}
    // strength getter
    double PersonWithStrengthToFight::getStrength() const
    { return hisStrength; }
    // change strength
    void PersonWithStrengthToFight::updateStrength
    (double winner, double loser) { hisStrength = winner - loser; }
    // defend
    void PersonWithStrengthToFight::defend() const {
        cout << "Ugh!" << endl;
    }
    // display a Noble using output operator (no army)
    void PersonWithStrengthToFight::displayNoble(ostream& os) const {
        os << " has strength: " << getStrength();
    }
}