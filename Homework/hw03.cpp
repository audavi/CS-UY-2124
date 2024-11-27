// hw.03.cpp
// Emily Lopez (el4100)
// Purpose: Expand the warrior program using object-oriented programming

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
// class warrior represents a warrior with a name
class Warrior {
    //allow the output operator to have access to warrior private variables
    friend ostream& operator<<(ostream& os, const Warrior& warrior);
public:
    Warrior(const string& warriorName, const string& weaponName, int weaponStrength)
    : warriorName(warriorName), weapon(weaponName, weaponStrength) {}
    // setters & getters
    const string& getName() const { return warriorName; }
    int getStrength() const { return weapon.getWeaponStrength(); }
    void changeStrength(int newStrength) { weapon.changeWeaponStrength(newStrength); }
    //METHODS
    // Description: Displays who is fighting and report results.
    // Parameter: Warrior& warrior2: an enemy warrior object
    // Return type: void
    void battle(Warrior& warrior2){
        cout << getName() << " battles " << warrior2.getName() << endl;

        //Both warriors are dead -> no battle
        if (getStrength() == 0 && warrior2.getStrength() == 0) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        //Warrior 2 is alive but warrior 1 is dead
        else if (getStrength() == 0) {
            cout << "He's dead, " << warrior2.getName() << endl;
        }
        //Warrior 1 is alive but warrior 2 is dead
        else if (warrior2.getStrength() == 0){
            cout << "He's dead, " << getName() << endl;
        }
        //Both are alive but have the same strength
        else if (getStrength() == warrior2.getStrength()) {
            cout << "Mutual Annihilation: " << getName() <<" and "
            << warrior2.getName() << " die at each other's hands" << endl;
            changeStrength(0);
            warrior2.changeStrength(0);
        }
        //Warrior 1 is stronger and wins -> takes damage based on warrior 2 strength
        else if (getStrength() > warrior2.getStrength()) {
            cout << getName() << " defeats " << warrior2.getName() << endl;
            //Store the new strength for warrior 1
            int newStrength = getStrength() - warrior2.getStrength();
            changeStrength(newStrength);
            warrior2.changeStrength(0);
        }
        //Warrior 2 is stronger and wins -> takes damage based on warrior 1 strength
        else {
            cout << warrior2.getName() << " defeats " << getName() << endl;
            //Store the new strength for warrior 2
            int newStrength = warrior2.getStrength() - getStrength();
            changeStrength(0);
            warrior2.changeStrength(newStrength);
        }
    }
private:
    class Weapon {
        friend ostream& operator<<(ostream& os, const Warrior::Weapon& weapon) {
            os << "weapon: " << weapon.weaponName<< ", " << weapon.weaponStrength;
            return os;
        }
    public:
        Weapon(const string& weaponName, int weaponStrength)
        : weaponName(weaponName), weaponStrength(weaponStrength) {}
        // setters & getters
        int getWeaponStrength() const { return weaponStrength; }
        void changeWeaponStrength (int newStrength) { weaponStrength = newStrength; }

    private:
        string weaponName;
        int weaponStrength;
    };
    string warriorName;
    Weapon weapon;
};
//prototypes
void displayWarriors(const vector<Warrior>& warriors);
size_t findWarriorInd(const string& warriorName, const vector<Warrior>& warriors);

int main() {
    //Open warrior.txt file
    ifstream file;
    file.open("warriors.txt");
    if (!file) {
        cerr << "Error opening file" << endl;
        exit(1);
    }
    string command;
    vector<Warrior> warriors;

    //Check to either view status, begin battle, or save warrior info
    while (file >> command) {
        //Save the warrior name and strength
        if (command == "Warrior") {
            string warriorName, weaponName;
            int weaponStrength;

            file >> warriorName >> weaponName >> weaponStrength;
            bool nameTaken = false;
            for (const Warrior& warrior : warriors) {
                //Check if the warrior name has been used.
                if (warrior.getName() == warriorName) {
                    nameTaken = true;
                    break;
                }
            }
            //If the name has not been used yet, add to vector.
            if (!nameTaken) {
                warriors.emplace_back(warriorName, weaponName, weaponStrength);
            //Otherwise, display an error.
            } else {
                cerr << "Error: Name has already been used." << endl;
            }
        }
        //Display all warrior info
        if (command == "Status") {
            displayWarriors(warriors);
        }
        //create a battle between 2 specified warriors
        if (command == "Battle") {
            string warriorName1;
            string warriorName2;
            file >> warriorName1 >> warriorName2;
            //Find the two warriors in our collection
            bool warrior1Found = false;
            bool warrior2Found = false;
            //Check to see if both warriors already exist
            for (const Warrior& currWarrior : warriors) {
                if (currWarrior.getName() == warriorName1) {
                    warrior1Found = true;
                }
                if (currWarrior.getName() == warriorName2) {
                    warrior2Found = true;
                }
                //If both warriors are found, move into battle
                if(warrior1Found && warrior2Found) {
                    break;
                }
            }
            if (warrior1Found && warrior2Found) {
                size_t warriorInd1 = findWarriorInd(warriorName1, warriors);
                size_t warriorInd2 = findWarriorInd(warriorName2, warriors);
                warriors[warriorInd1].battle(warriors[warriorInd2]);
            } else {
                //A warrior was not found
                cerr << "Error: Cannot battle a non-existent warrior" << endl;
            }
        }
    }
    file.close();
}

//Description: Displays the saved warrior information.
// Parameter: const vector<Warrior>& warriors: contains
//            all warrior names and strength
// Return type: void
void displayWarriors(const vector<Warrior>& warriors) {
    cout << "There are: "<< warriors.size() << " warriors" << endl;
    for (const Warrior& warriorInfo : warriors) {
        cout << warriorInfo << endl;
    }
}

// Description: Find the location of a warrior inside the vector
// Parameter: const string& warriorName: Name of a warrior
//            const vector<Warrior>& Warriors: contains all warrior info
// Return type: size_t
size_t findWarriorInd(const string& warriorName, const vector<Warrior>& warriors) {
    for (size_t i = 0; i < warriors.size(); i++) {
        if (warriors[i].getName() == warriorName) {
            return i;
        }
    }
}
// Description: Overloading output overloading to display warrior info
// Parameter: ostream& os: output stream
//            const Warrior& warrior: a warrior
// Return type: size_t
ostream& operator<<(ostream& os, const Warrior& warrior) {
    os << "Warrior: " << warrior.warriorName << ", " << warrior.weapon;
    return os;
}
