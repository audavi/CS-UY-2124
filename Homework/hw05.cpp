/*
Emily Lopez (el4100)
  hw05.cpp
  Purpose: Reading and modeling a battle game
  of medieval times with warriors and nobles.
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// class warrior represents a warrior with a name and strength
// Requires a name of type `string`, strength of type `double`.
// Status is of type 'bool' and can be hired by nobles.
class Warrior {
    friend ostream& operator<<(ostream& os, const Warrior& theWarrior);
public:
    //Constructor
    Warrior(const string& name, double strength)
    : warriorName(name), warriorStrength(strength), hired(false) {}
    //Check if employed or not
    bool jobStatus() const { return hired; }
    // setters & getters
	const string& getWarriorName() const { return warriorName; }
    double getStrength() const { return warriorStrength; }
    void changeStrength(double newStrength)
		{ warriorStrength = newStrength; }
    const void getHired(){
        if (!hired) { hired = true; }
    }
    const void getFired() {
        if (hired) { hired = false; }
    }
private:
    string warriorName;
    double warriorStrength;
    bool hired;
};
// Class noble represents a noble with a name
// Requires a name of type `string`
// Status is of type 'bool' and has 0 strength of type 'double'
// Can hire and fire warriors to battle with other nobles
class Noble {
	friend ostream& operator<<(ostream& os, const Noble& theNoble);
public:
	// Constructor
	Noble(const string& name)
	: nobleName(name), nobleStatus(true), nobleStrength(0) {}

	// setters & getters
	//this should be marked const
	bool getNobleStatus() const { return nobleStatus; }
	string getName() const { return nobleName;}

	//check if a warrior is in the noble's army
	bool warriorChecker(const string& warriorName){
		for (size_t i = 0; i < warriorArmy.size(); i++) {
			if (warriorName == warriorArmy[i]->getWarriorName()){
				return true;
			}
		}
		return false;
	}

	//returns the total amount of warriors
	int armyCount(){ return warriorArmy.size();}

	// Description: Hires a warrior for a noble's army.
	// Parameter: Warrior& theWarrior: a warrior
	// Return type: bool
	bool hire(Warrior& theWarrior) {
		//Create a pointer to the address of the warrior
		Warrior* warriorPointer = &theWarrior;
		//noble must be alive and warrior must be 'unemployed' to be hired
		if (nobleStatus && !theWarrior.jobStatus())  {
			warriorArmy.push_back(warriorPointer);
			nobleStrength += theWarrior.getStrength();
			warriorPointer->getHired();
			return true;
		} else { //unable to hire specified warrior
			cerr << nobleName << " failed to hire " <<
				theWarrior.getWarriorName() << endl;
			return false;
		}
	}
	// Description: Fires a warrior from a noble's army
	// Parameter: Warrior& theWarrior: a warrior
	// Return type: bool
	bool fire(Warrior& theWarrior) {
		// if noble is dead, he cannot fire
		if(!nobleStatus) {
			cerr << nobleName << " failed to fire " <<
				theWarrior.getWarriorName() << endl;
			return false;
		}
		// search through vector of pointers to find warrior
		bool warriorFound = false;
		for (size_t i = 0; i < warriorArmy.size(); i++) {
			if (&theWarrior == warriorArmy[i]) {
				warriorFound = true;
			}
		}
		//if the warrior works for noble, fire them
		if (warriorFound) {
			bool fired = false;
			for (size_t i = 0; i < warriorArmy.size(); i++) {
				//if warrior was found and must be fired, reset status
				if (!fired) {
					if (warriorArmy[i] == &theWarrior) {continue;}
						cout <<  theWarrior.getWarriorName() <<", you don't work for me "
											 "any more! -- " << nobleName << endl;
						theWarrior.getFired();
						fired = true;

				} else { // move over warrior
					warriorArmy[i-1] = warriorArmy[i];
				}
				nobleStrength -= theWarrior.getStrength();
				warriorArmy.pop_back();
			}
			return fired;
		} else { //if warrior does not work for noble, we cannot fire
			cerr << nobleName << " failed to fire " <<
				theWarrior.getWarriorName() << endl;
			return false;
		}
	}
	// Description: updates strength after a battle
	// Return type: void
	void updateStrength(double winner, double loser) {
		int newArmyStrength = 0;
		for (Warrior*& warrior : warriorArmy) {
			//update every warrior's strength equal to ratio of enemy's strength
			int newStrength = warrior->getStrength() * (winner - loser)/winner;
			warrior->changeStrength(newStrength);
			newArmyStrength += newStrength;
		}
		nobleStrength = newArmyStrength;
	}
	// Description: updates status to dead for  a warrior
	// Return type: void
	void death() {
		nobleStatus = false;
		// set strength of all warriors in army to 0
		updateStrength(1, 1);
	}
	// Description: displays a battle between two nobles and their army
	// Return type: void
	void battle(Noble& rhs) {
		cout << nobleName << " battles " << rhs.nobleName << endl;
		//check if both nobles are dead
		if (!nobleStatus && !rhs.nobleStatus) {
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
		}
		//noble 1 is dead but noble 2 is alive
		else if(nobleStatus && !rhs.nobleStatus) {
			cout << "He's dead, " << nobleName << endl;
		}
		//noble 1 is alive but noble 2 is dead
		else if(!nobleStatus && rhs.nobleStatus) {
			cout << "He's dead, " << rhs.nobleName << endl;
		}
		//if both are alive
		else {
			// noble 1 has a greater army strength than noble 2
			if (nobleStrength > rhs.nobleStrength){
				updateStrength(nobleStrength, rhs.nobleStrength);
				rhs.death();
				cout << nobleName << " defeats " << rhs.nobleName << endl;
			}
			else if(nobleStrength < rhs.nobleStrength) {
				updateStrength(rhs.nobleStrength, nobleStrength);
				death();
				cout << rhs.nobleName << " defeats " << nobleName << endl;
			}
			//noble 1 and noble 2 have the same army strength
			else if(nobleStrength == rhs.nobleStrength) {
				death();
				rhs.death();
				cout << "Mutual Annihilation: " << nobleName << " and "
				<< rhs.nobleName << " die at each other's hands" << endl;
			}
		}
	}
private:
	string nobleName;
	vector<Warrior*> warriorArmy;
	bool nobleStatus; // army strength is the noble's strength
	double nobleStrength;
};

Noble* findNoble(const string& nobleName,
	const vector<Noble*>& allNobles);
Warrior* findWarrior(const string& warriorName,
	const vector<Warrior*>& allWarriors);
void clearNobles(vector<Noble*>& nobleVector);
void clearWarriors(vector<Warrior*>& warriorVector);

int main() {
	// open nobleWarriors.txt file
	ifstream file;
	file.open("nobleWarriors.txt");
	if (!file) {
		cerr << "Error opening file." << endl;
		exit(1);
	}
	string command;
	// track nobles in a vector of pointers to nobles
	vector<Noble*> allNobles;
	// track warriors in a vector of pointers to warriors
	vector<Warrior*> allWarriors;
	// check the command
	while (file >> command) {
		if (command == "Noble") { // create a noble on the heap
			string nobleName;
			file >> nobleName;
			// if noble with same name does not exist
			if (!findNoble(nobleName, allNobles)) {
				Noble* newNoble = new Noble(nobleName);
				allNobles.push_back(newNoble);
			}
			else { // if noble already exists
				cerr << nobleName << " already exists!" << endl;
			}
		}
		else if (command == "Warrior") { // create a warrior on the heap
			string warriorName;
			double warriorStrength;
			file >> warriorName >> warriorStrength;
			// if warrior with same name does not exist
			if (!findNoble(warriorName, allNobles)) {
				Warrior* newWarrior = new Warrior(warriorName, warriorStrength);
				allWarriors.push_back(newWarrior);
			}
			else { // if warrior already exists
				cerr << warriorName << " already exists!" << endl;
			}
		}
		else if (command == "Hire") {
			// call the Noble's hire method
			string nobleName, warriorName;
			file >> nobleName >> warriorName;
			// check if both the noble and warrior exist
			if (findNoble(nobleName, allNobles) &&
				findWarrior(warriorName, allWarriors)) {
				Noble *newNoble = findNoble(nobleName, allNobles);
				Warrior *newWarrior = findWarrior(warriorName, allWarriors);
				newNoble->hire(*newWarrior);
			} else if (!findNoble(nobleName, allNobles)){ // noble does not exist
				cout << "Attempting to hire using unknown noble: "
				<< nobleName << endl;
			} else { // warrior does not exist
				cout << "Attempting to hire using unknown warrior: "
				<< warriorName << endl;
			}

		}
		else if (command == "Fire") { // call the Noble's fire method
			string nobleName, warriorName;
			file >> nobleName >> warriorName;
			// do both exist?
			if (findNoble(nobleName, allNobles)
				&& findWarrior(warriorName, allWarriors)) {
				Noble* newNoble = findNoble(nobleName, allNobles);
				Warrior* newWarrior = findWarrior(warriorName, allWarriors);
				// check if the warrior belongs to the noble's army
				if (newNoble->warriorChecker(warriorName)) {
					newNoble->fire(*newWarrior);
				} else { // does not beling in the army
					cerr << nobleName << " does not have the warrior "
					<< warriorName << " in his army!" << endl;
				}
			} else if (!findNoble(nobleName, allNobles)) { // noble doesnt exist
				cerr << "This noble does not exist and cannot "
				"fire anyone." << endl;
			} else { // warrior doesnt exist
				cerr << "This warrior does not exist and "
				"cannot be fired." << endl;
			}

		} // call the Noble's battle method
		else if (command == "Battle") {
			string firstNobleName, secondNobleName;
			file >> firstNobleName >> secondNobleName;
			// if both nobles exist
			if (findNoble(firstNobleName, allNobles)
				&& findNoble(secondNobleName, allNobles)) {
				Noble* firstNoble = findNoble(firstNobleName, allNobles);
				Noble* secondNoble = findNoble(secondNobleName, allNobles);
				firstNoble->battle(*secondNoble);
			} else if (!findNoble(firstNobleName, allNobles)) {
				// first noble does not exist
				cerr << firstNobleName << " doesn't exist! "
							  "He cannot battle." << endl;
			} else {
				// second noble does not exist
				cerr << secondNobleName << " doesn't exist! "
							   "He cannot battle." << endl;
			}
		} // status: shows the nobles, together with their armies
		else if (command == "Status") {
			cout << "Status\n" << "======\n" << "Nobles:\n";
			// count the employed warriors
			int totalWarrior = 0;
			// if there are nobles, display them
			if (!allNobles.empty()) {
				for (size_t i = 0; i < allNobles.size(); i++) {
					cout << *allNobles[i];
					totalWarrior += allNobles[i]->armyCount();
				}
			} else { // if theres no nobles
				cout << "NONE" << endl;
			}
			cout << "\nUnemployed Warriors:" << endl;
			// if there are warriors who were not hired by a noble, display them
			if (allWarriors.size() - totalWarrior > 0) {
				for (size_t i = 0; i < allWarriors.size(); i++) {
					if (allWarriors[i]->jobStatus() == false) {
						cout << "\t" << *allWarriors[i] << endl;
					}
				}
			} else {
				cout << "NONE" << endl;
			}
		}
		else { // clear out all the nobles and warriors created
			//delete and clear noble vector
			clearNobles(allNobles);
			//delete and clear warrior vector
			clearWarriors(allWarriors);
		}
	}
	file.close();
	//clear noble vector
	clearNobles(allNobles);
	//clear warrior vector
	clearWarriors(allWarriors);
}
// Description: Overloading output overloading to display warrior info
// Parameter: ostream& os: output stream
//            const Warrior& theWarrior: a warrior
// Return type: ostream
ostream& operator<<(ostream& os, const Warrior& theWarrior) {
    os << theWarrior.warriorName <<
    	": " << theWarrior.warriorStrength;
    return os;
}
// Description: Overloading output overloading to display noble info
// Parameter: ostream& os: output stream
//            const Noble& theNoble: a noble
// Return type: ostream
ostream& operator<<(ostream& os, const Noble& theNoble) {
	os << theNoble.nobleName << " has an army of "
		<< theNoble.warriorArmy.size() << "\n";
	for(size_t i = 0; i < theNoble.warriorArmy.size(); i++) {
		os << "\t" << *theNoble.warriorArmy[i] << endl;
	}
	return os;
}
// Description: Finds a noble's name in a vector of nobles
// Parameter: const string& nobleName: noble's name
//            const vector<Noble*>& allNobles: all nobles
// Return type: pointer
Noble* findNoble(const string& nobleName, const vector<Noble*>& allNobles) {
	for (size_t i = 0; i < allNobles.size(); i++) {
		if (nobleName == allNobles[i]->getName()) {
			return allNobles[i];
		}
	}
	return nullptr;
}
// Description: Finds a warrior's name in a vector of warriors
// Parameter: const string& nobleName: warrior's name
//            const vector<Noble*>& allNobles: all warriors
// Return type: pointer
Warrior* findWarrior(const string& warriorName,
	const vector<Warrior*>& allWarriors){
	for (size_t i = 0; i < allWarriors.size(); i++) {
		if (warriorName == allWarriors[i]->getWarriorName()){
			return allWarriors[i];
		}
	}
	return nullptr;
}
// Description: Deletes and clears a noble vector
// Parameter: vector<Noble*>& nobleVector: vector of nobles
// Return type: void
void clearNobles(vector<Noble*>& nobleVector) {
	for (size_t i = 0; i < nobleVector.size(); i++) {
		delete nobleVector[i];
	}
	nobleVector.clear();
}
// Description: Deletes and clears a warrior vector
// Parameter: vector<Noble*>& warriorVector: warrior of nobles
// Return type: void
void clearWarriors(vector<Warrior*>& warriorVector) {
	for (size_t i = 0; i < warriorVector.size(); i++) {
		delete warriorVector[i];
	}
	warriorVector.clear();
}
