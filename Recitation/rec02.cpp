#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
using namespace std;

struct molecule {
    vector<string> name;
    int carb;
    int hydro;
};
// Prototypes
void openFile(ifstream& file);
void fillVector(vector<molecule>& moles, ifstream& file);
void insertInfo(vector<molecule> &moles, const string& name, int numCarb, int numHydro);
void display_vector(const vector<molecule>& moles);
size_t findLocation(const vector<molecule>& moles, int numCarb, int numHydro);
void printSingle(const molecule& mole);
void sort_vector(vector<molecule> &moles);

int main() {
    ifstream file;
    openFile(file);

    vector<molecule> moles;
    fillVector(moles, file);

    file.close();
    cout << "Unsorted: " << endl;
    display_vector(moles);
    sort_vector(moles);
    cout << "Sorted: " << endl;
    display_vector(moles);
}
void openFile(ifstream& file) {
    string input;
    do {cout << "File name?" << endl;
        cin >> input;
        file.open(input);
    } while (!file); // if file is not opened, keep asking
}

void fillVector(vector<molecule>& moles, ifstream& file) {
    string name; //name
    char carbon, hydrogen;
    int numCarb, numHydro;
    while(file >> name >> carbon >> numCarb >> hydrogen >> numHydro) {
        insertInfo(moles, name, numCarb, numHydro);
    }
}
void insertInfo(vector<molecule> &moles, const string& name, int numCarb, int numHydro) {
    size_t vector_loc = findLocation(moles, numCarb, numHydro);
    if (vector_loc == moles.size()) {
        molecule new_mole;
        new_mole.carb = numCarb;
        new_mole.hydro = numHydro;
        new_mole.name.push_back(name);
        moles.push_back(new_mole);
    }
    else {
        moles[vector_loc].name.push_back(name);

    }

}

size_t findLocation(const vector<molecule>& moles, int numCarb, int numHydro) {
    for(size_t i = 0; i < moles.size(); i++) {
        if (moles[i].carb == numCarb && moles[i].hydro == numHydro) {
            return i;
        }
    }
    return moles.size();
}
void display_vector(const vector<molecule>& moles) {
    for (const molecule& mole: moles) {
        printSingle(mole);
    }
}
void printSingle(const molecule& mole) {
    cout << "C" << mole.carb << "H" << mole.hydro << " ";
    // incldue names
    for (const string& name : mole.name) {
        cout << name << ' ';
    }
    cout << endl;
}
//SORTING
void sort_vector(vector<molecule> &moles) {
    //false until all formulas have been sorted through
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (size_t i = 0; i < moles.size() -1; ++i) {
            if (moles[i+1].carb < moles[i].carb || moles[i+1].carb == moles[i].carb
                && moles[i+1].hydro < moles[i].hydro) {
                swap(moles[i + 1], moles[i]);
                sorted = false;
            }
        }
    }
}