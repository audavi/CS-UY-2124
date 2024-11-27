// /*
//   Emily Lopez (el4100)
//   hw04.cpp
//   Purpose: Modeling a game of medieval times
// 		   with warriors and nobles.
//  */
// #include <iostream>
// #include <ostream>
// #include <vector>
// #include <string>
// using namespace std;
//
// // class warrior represents a warrior with a name and strength
// // Requires a name of type `string`, strength of type `double`.
// // Status is of type 'bool' and can be hired by nobles.
//
// class Warrior {
// 	friend ostream& operator<<(ostream& os, const Warrior& theWarrior);
// public:
// 	//Constructor
// 	Warrior(const string& name, double strength)
// 	: warriorName(name), warriorStrength(strength), hired(false) {}
// 	//Check if employed or not
// 	bool jobStatus() const { return hired; }
//
// 	// setters & getters
// 	double getStrength() const { return warriorStrength; }
// 	void changeStrength(double newStrength) { warriorStrength = newStrength; }
// 	const string& getWarriorName() { return warriorName; }
// 	const void getHired(){
// 		if (!hired) { hired = true; }
// 	}
// 	const void getFired() {
// 		if (hired) { hired = false; }
// 	}
// private:
// 	string warriorName;
// 	double warriorStrength;
// 	bool hired;
// };
//
// // Class noble represents a noble with a name
// // Requires a name of type `string`
// // Status is of type 'bool' and has 0 strength of type 'double'
// // Can hire and fire warriors to battle with other nobles
// class Noble {
// 	friend ostream& operator<<(ostream& os, const Noble& theNoble);
// public:
// 	// Constructor
// 	Noble(const string& name)
// 	: nobleName(name), nobleStatus(true), nobleStrength(0) {}
//
// 	// setters & getters
// 	//this should be marked const
// 	bool getNobleStatus() const { return nobleStatus; }
//
// 	// Description: Hires a warrior for a noble's army.
// 	// Parameter: Warrior& theWarrior: a warrior
// 	// Return type: bool
// 	bool hire(Warrior& theWarrior) {
// 		//Create a pointer to the address of the warrior
// 		Warrior* warriorPointer = &theWarrior;
// 		//noble must be alive and warrior must be 'unemployed' to be hired
// 		if (nobleStatus && !theWarrior.jobStatus())  {
// 			warriorArmy.push_back(warriorPointer);
// 			nobleStrength += theWarrior.getStrength();
// 			warriorPointer->getHired();
// 			return true;
// 		} else { //unable to hire specified warrior
// 			cerr << nobleName << " failed to hire " << theWarrior.getWarriorName() << endl;
// 			return false;
// 		}
// 	}
// 	// Description: Fires a warrior from a noble's army
// 	// Parameter: Warrior& theWarrior: a warrior
// 	// Return type: bool
// 	bool fire(Warrior& theWarrior) {
// 		// if noble is dead, he cannot fire
// 		if(!nobleStatus) {
// 			cerr << nobleName << " failed to fire " <<
// 				theWarrior.getWarriorName() << endl;
// 			return false;
// 		}
// 		// search through vector of pointers to find warrior
// 		bool warriorFound = false;
// 		for (size_t i = 0; i < warriorArmy.size(); i++) {
// 			if (&theWarrior == warriorArmy[i]) {
// 				warriorFound = true;
// 			}
// 		}
// 		//if the warrior works for noble, fire them
// 		if (warriorFound) {
// 			bool fired = false;
// 			for (size_t i = 0; i < warriorArmy.size(); i++) {
// 				//if warrior was found and must be fired, reset status
// 				if (!fired) {
// 					if (warriorArmy[i] == &theWarrior) {continue;}
// 						cout <<  theWarrior.getWarriorName() <<", you don't work for me "
// 											 "any more! -- " << nobleName << endl;
// 						theWarrior.getFired();
// 						fired = true;
//
// 				} else { // move over warrior
// 					warriorArmy[i-1] = warriorArmy[i];
// 				}
// 				nobleStrength -= theWarrior.getStrength();
// 				warriorArmy.pop_back();
// 			}
// 			return fired;
// 		} else { //if warrior does not work for noble, we cannot fire
// 			cerr << nobleName << " failed to fire " <<
// 				theWarrior.getWarriorName() << endl;
// 			return false;
// 		}
// 	}
// 	// Description: updates strength after a battle
// 	// Return type: void
// 	void updateStrength(double winner, double loser) {
// 		int newArmyStrength = 0;
// 		for (Warrior*& warrior : warriorArmy) {
// 			//update every warrior's strength equal to ratio of enemy's strength
// 			int newStrength = warrior->getStrength() * (winner - loser)/winner;
// 			warrior->changeStrength(newStrength);
// 			newArmyStrength += newStrength;
// 		}
// 		nobleStrength = newArmyStrength;
// 	}
// 	// Description: updates status to dead for  a warrior
// 	// Return type: void
// 	void death() {
// 		nobleStatus = false;
// 		// set strength of all warriors in army to 0
// 		updateStrength(1, 1);
// 	}
// 	// Description: displays a battle between two nobles and their army
// 	// Return type: void
// 	void battle(Noble& rhs) {
// 		cout << nobleName << " battles " << rhs.nobleName << endl;
// 		//check if both nobles are dead
// 		if (!nobleStatus && !rhs.nobleStatus) {
// 			cout << "Oh, NO! They're both dead! Yuck!" << endl;
// 		}
// 		//noble 1 is dead but noble 2 is alive
// 		else if(nobleStatus && !rhs.nobleStatus) {
// 			cout << "He's dead, " << nobleName << endl;
// 		}
// 		//noble 1 is alive but noble 2 is dead
// 		else if(!nobleStatus && rhs.nobleStatus) {
// 			cout << "He's dead, " << rhs.nobleName << endl;
// 		}
// 		//if both are alive
// 		else {
// 			// noble 1 has a greater army strength than noble 2
// 			if (nobleStrength > rhs.nobleStrength){
// 				updateStrength(nobleStrength, rhs.nobleStrength);
// 				rhs.death();
// 				cout << nobleName << " defeats " << rhs.nobleName << endl;
// 			}
// 			else if(nobleStrength < rhs.nobleStrength) {
// 				updateStrength(rhs.nobleStrength, nobleStrength);
// 				death();
// 				cout << rhs.nobleName << " defeats " << nobleName << endl;
// 			}
// 			//noble 1 and noble 2 have the same army strength
// 			else if(nobleStrength == rhs.nobleStrength) {
// 				death();
// 				rhs.death();
// 				cout << "Mutual Annihilation: " << nobleName << " and "
// 				<< rhs.nobleName << " die at each other's hands" << endl;
// 			}
// 		}
// 	}
// private:
// 	string nobleName;
// 	vector<Warrior*> warriorArmy;
// 	bool nobleStatus; // army strength is the noble's strength
// 	double nobleStrength;
// };
//
// int main()
// {
//
//     Noble art("King Arthur");
//     Noble lance("Lancelot du Lac");
//     Noble jim("Jim");
//     Noble linus("Linus Torvalds");
//     Noble billie("Bill Gates");
//
//     Warrior cheetah("Tarzan", 10);
//     Warrior wizard("Merlin", 15);
//     Warrior theGovernator("Conan", 12);
//     Warrior nimoy("Spock", 15);
//     Warrior lawless("Xena", 20);
//     Warrior mrGreen("Hulk", 8);
//     Warrior dylan("Hercules", 3);
//
//     jim.hire(nimoy);
//     lance.hire(theGovernator);
//     art.hire(wizard);
//     lance.hire(dylan);
//     linus.hire(lawless);
//     billie.hire(mrGreen);
//     art.hire(cheetah);
//     art.hire(nimoy);
//
//     cout << "==========\n\n"
//          << "Status before all battles, etc.\n";
//     cout << jim << endl;
//     cout << lance << endl;
//     cout << art << endl;
//     cout << linus << endl;
//     cout << billie << endl;
//     cout << "==========\n\n";
//
//     art.fire(cheetah);
//     cout << art << endl;
//
//     lance.fire(nimoy);
//     cout << lance << endl;
//     cout << "==========\n\n";
//
//     art.battle(lance);
//     jim.battle(lance);
//     linus.battle(billie);
//     billie.battle(lance);
//
//     cout << "==========\n\n"
//          << "Status after all battles, etc.\n";
//     cout << jim << endl;
//     cout << lance << endl;
//     cout << art << endl;
//     cout << linus << endl;
//     cout << billie << endl;
//     cout << "==========\n";
//
// } // main
//
// // Description: Overloading output overloading to display warrior info
// // Parameter: ostream& os: output stream
// //            const Warrior& theWarrior: a warrior
// // Return type: ostream
//
// ostream& operator<<(ostream& os, const Warrior& theWarrior) {
// 	os << theWarrior.warriorName << ": " << theWarrior.warriorStrength;
// 	return os;
// }
// // Description: Overloading output overloading to display noble info
// // Parameter: ostream& os: output stream
// //            const Noble& theNoble: a noble
// // Return type: ostream
// ostream& operator<<(ostream& os, const Noble& theNoble) {
// 	os << theNoble.nobleName << " has an army of " << theNoble.warriorArmy.size() << "\n";
// 	for(size_t i = 0; i < theNoble.warriorArmy.size(); i++) {
// 		os << "\t" << *theNoble.warriorArmy[i] << endl;
// 	}
// 	return os;
// }