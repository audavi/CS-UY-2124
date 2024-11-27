 /*
 hw02.cpp
 Emily Lopez (el4100)
 Purpose: Modeling a game of medieval times
 */



// fix before start hw 3
//  Overall Feedback
//  Deductions:
//  -1 does not handle case where a non-existent warrior is battled
//  Warnings:
//      - include comment about types (comment about your warrior struct)
//      - better to use a different variable name for your stream, file for a stream is misleading




 #include <iostream>
 #include <fstream>
 #include <string>
 #include <vector>
 using namespace std;

 //Warrior struct
 struct Warrior {
     string name;
     int strength;
 };

 //Function prototypes
 void openFile(ifstream& file);
 void fillWarriorVector(ifstream& file, vector<Warrior>& totalWarriors);
 void displayWarriors(const vector<Warrior>& warriors);
 size_t findWarrior(const string &name, const vector<Warrior> &totalWarriors);
 void battle(const Warrior& warrior1, const Warrior& warrior2, vector<Warrior>& warriors);


 int main() {
     //open file
     ifstream file;
     openFile(file);
     // create two warriors
     Warrior warrior1, warrior2;
     string commandLine;
     // warrior names
     string name1, name2;
     //warrior locations
     size_t warrior1Loc, warrior2Loc;
     //collection of warriors
     vector<Warrior> totalWarriors;


     while (file >> commandLine) {
         //check to either view status, begin battle, or save warrior info
         if (commandLine == "Warrior") {
             // save the warrior name and strength
             fillWarriorVector(file, totalWarriors);
         } else if (commandLine == "Status") {
             displayWarriors(totalWarriors);
         } else if (commandLine == "Battle") { //create a battle between 2 specified warriors
             file >> name1 >> name2; // Name the two warriors who will battle
             //find the location of Warrior 1 and 2 in the vector
             warrior1Loc = findWarrior(name1, totalWarriors);
             warrior2Loc = findWarrior(name2, totalWarriors);
             warrior1 = totalWarriors[warrior1Loc];
             warrior2 = totalWarriors[warrior2Loc];
             battle(warrior1, warrior2,totalWarriors);
         }
     }
     file.close();
 }
 //FUNCTIONS

 // Description: Opens file
 // Parameter: ifstream file of commands
 // Return type: void
 void openFile(ifstream& file) {
     file.clear();
     file.open("warriors.txt");
     if (!file) {
         cerr << "Error opening file\n";
         exit(1);
     }
 }
 // Description: Fills a vector storing Warrior data based on the file information
 // Parameter: ifstream& file: file of commands,
 //            vector<Warrior> totalWarrior: contains all warrior names and strength
 // Return type: void
 void fillWarriorVector(ifstream& file, vector<Warrior>& totalWarriors) {
     string name;
     int strength;
     Warrior newWarrior;
     file >> name >> strength;
     newWarrior.name = name;
     newWarrior.strength = strength;
     //must check if the warrior has already exists
     bool nameTaken = false;
     for (const Warrior& currentWarrior : totalWarriors) {
         if (currentWarrior.name == newWarrior.name) {
             //name has been taken and will not be added
             nameTaken = true;
             break;
         }
     }
     if (!nameTaken) {
         //if name is not taken, add to the vector
         totalWarriors.push_back(newWarrior);
     } else {
         cout << "Error: Warrior " << newWarrior.name << " already exists\n";
     }

 }
 //Description: Displays the saved warrior information.
 // Parameter:
 //           const vector<Warrior>& warriors: contains all warrior names and strength
 // Return type: void
 void displayWarriors(const vector<Warrior>& warriors){
     //Go through a vector of warriors to display their information.
     cout << "There are: "<< warriors.size() << " warriors" << endl;
     for (const Warrior& warriorInfo : warriors) {
         cout << "Warrior: "<< warriorInfo.name << ", strength: " << warriorInfo.strength << endl;
     }
 }
 // Description: Find the location of a warrior inside the vector
 // Parameter: const string &name: Name of a warrior
 //            const vector<Warrior> &totalWarriors: contains all warrior names and strength
 // Return type: size_t
 size_t findWarrior(const string &name, const vector<Warrior> &totalWarriors) {
     for (size_t i = 0; i < totalWarriors.size(); i++) {
         if (totalWarriors[i].name == name) {
             return i;
         }
     }
     return totalWarriors.size();
 }
 // Description: Displays who is fighting and report results.
 // Parameter: Warrior& warrior1: a warrior object
 //            Warrior& warrior2: a warrior object
 // Return type: void
 void battle(const Warrior& warrior1, const Warrior& warrior2, vector<Warrior>& warriors) {
     cout << warrior1.name << " battles " << warrior2.name << endl;
     //find location of each warrior in the collection of all warriors
     size_t warrior1Loc = findWarrior(warrior1.name, warriors);
     size_t warrior2Loc = findWarrior(warrior2.name, warriors);

     //Both are alive but have the same strength
     if (warrior1.strength > 0 && warrior2.strength > 0 && warrior1.strength == warrior2.strength) {
         cout << "Mutual Annihilation: " << warrior1.name << " and " << warrior2.name << " die at each other's hands" << endl;
         warriors[warrior1Loc].strength = 0;
         warriors[warrior2Loc].strength = 0;
     //Warrior 1 is alive but warrior 2 is dead
     } else if (warrior1.strength > 0 && warrior2.strength == 0) {
         cout << "He's dead, " << warrior1.name << endl;
     //Warrior 2 is alive but warrior 1 is dead
     } else if (warrior1.strength == 0 && warrior2.strength > 0) {
         cout << "He's dead, " << warrior2.name << endl;
     //Both warriors are dead -> no battle
     } else if (warrior1.strength == 0 && warrior2.strength == 0) {
         cout << "Oh, NO! They're both dead! Yuck!" << endl;
     //Warrior 1 is stronger and wins -> takes damage based on warrior 2 strength
     } else if (warrior1.strength > warrior2.strength) {
         cout << warrior1.name << " defeats " << warrior2.name << endl;
         //Store the new strength for warrior 1
         int newStrength = warrior1.strength - warrior2.strength;
         warriors[warrior1Loc].strength = newStrength;
         warriors[warrior2Loc].strength = 0;
     //Warrior 2 is stronger and wins -> takes damage based on warrior 1 strength
     } else if (warrior1.strength < warrior2.strength) {
         cout << warrior2.name << " defeats " << warrior1.name << endl;
         int newStrength = warrior2.strength - warrior1.strength;
         //Store the new strength for warrior 2
         warriors[warrior2Loc].strength = newStrength;
         warriors[warrior1Loc].strength = 0;
     }
 }
