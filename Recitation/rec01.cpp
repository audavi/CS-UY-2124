/*
  Emily Lopez
  el4100
  rec01.cpp
*/


//
// Function prototypes for tasks 15-17
//
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

// Task 15. Function to display a vector of ints
void display_vector(vector<int>& ints);
// Task 16. Function to modify the vector, using indices
void double_vector(vector<int>& ints);
// Task 17. Function to modify the vector, using a ranged for
void range_for_double_vector(vector<int>& ints);

//
// main
//

int main() { // Yes, it has to have an int for the return type
    //
    // Output
    //

    // Task 1. Printing hello ...  No use of "using namespace"
    std :: cout << "hello ...\n" << endl;

    // Task 2  Printing hello ...  Using "using namespace"
    cout << "hello ...\n" << endl;


    // Types and variables
    //

    // Task 3  Displaying uninitialized variable
    int x;
    cout << "x: " << x << endl;

    // Task 4 Use the sizeof function to see the size in bytes of
    //        different types on your machine.
    int y = 17;
    int z = 2000000017;
    double pie = 3.14159;
    cout << "Size of y: " << sizeof(y) << endl;
    cout << "Size of z: " << sizeof(z) << endl;
    cout << "Size of pie: " << sizeof(pie) << endl; // takes up most memory

    // Task 5  Attempt to assign the wrong type of thing to a variable
    //ERROR: Compilation
    //x = "felix";

    //
    // Conditions
    //

    // Task 6  Testing for a range
    if (y >= 10 && y <= 20){
        cout << "y is between 10 and 20." << endl;
    }
    else{
        cout << "y is not in between 10 and 20." << endl;
    }

    //
    // Loops and files
    //

    // Task 7  Looping, printing values 10 to 20 inclusive

    // First with a for loop
    for (int x = 10; x <= 20; x++){
        cout << x << endl;
    }
    // Then with a while loop
    int i = 10;
    while(i <= 20){
        cout << i << " " << endl;
        i++;
    }
    // Finally with a do-while loop
    i =10;
    do {
        cout << i << ' ';
        i++;
    } while (i <= 20);
    cout << endl;


    // Task 8  Looping to successfully open a file, asking user for the name
    ifstream ifs;
    do {
        string filename;
        cout << "input filename: ";
        cin >> filename;
        ifs.open(filename);
    } while(!ifs);
    // Task 9  Looping, reading file word by "word".
    string something;
    while(ifs >> something){
        cout << something << endl;
    }
    ifs.close();

    // Task 10 Open a file of integers, read it in, and display the sum.
    ifstream intfile("integers.txt");
    if(!intfile){
        cerr << "File was not opened.";
        exit(1);
    }
    int numbers;
    int sum = 0;
    while(intfile >> numbers){
        sum +=numbers;
    }
    intfile.close();
    cout << "sum: " << sum << endl;
    // Taks 11 Open and read a file of integers and words. Display the sum.

    ifstream mixed("mixed.txt");
        if(!mixed){
          cerr << "File was not opened.";
          exit(1);
        }
        int num;
        int sums = 0;

        while(mixed >> num){
          sums += num;
          }
        cout << "sum: " << sums << endl;
        mixed.close();
    //
    // Vectors
    //

    // Task 12 Filling a vector of ints
    vector<int> VectorOfInts;
    for(int i = 10; i <= 100; i+= 2){
        VectorOfInts.push_back(i);
    }
    // Task 13 Displaying the vector THREE times
    //         a) using the indices,
    for(size_t i = 0; VectorOfInts.size(); i++){
        cout << VectorOfInts[i] << " ";
    }
    cout << endl;
    //         b) using a "ranged for"
    for(int value: VectorOfInts){
        cout << value << " ";
    }
    cout << endl;
    //         c) using indices again but backwards
    for(size_t i = VectorOfInts.size(); i > 0; i--){
        cout << VectorOfInts[i - 1] << " ";
    }

    // Task 14. Initialize a vector with the primes less than 20.
    vector<int> primes {2, 3, 5, 7, 11, 13, 17, 19};
    for(size_t i = 0; primes.size(); i++){
        cout << primes[i] << " ";
    }
    cout << endl;

}

//
// Function definitions for tasks 15-17
//

// Task 15. Function to display a vector of ints
void display_vector(vector<int>& ints) {
    for(int num : ints) {
        cout << "number in the vector: " << num << endl;
    }
}


// Task 16. Function to modify the vector, using indices
void double_vector(vector<int>& ints) {
    for(size_t it = 0; it <= ints.size(); it++) {
        ints[it] *= 2;
    }
}

// Task 17. Function to modify the vector, using a ranged for
void range_for_double_vector(vector<int>& ints) {
    for(int& num: ints) {
        num *= 2;
    }
}


