// hw01.cpp
// Emily Lopez (el4100)
// Purpose: Take in an encrypted file to be decrypted

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//function prototypes
char decryptedChar(char letter, int rotation);
void modifyLine(string &line, int rotation);

int main(){
    ifstream text("encrypted.txt");
    if (!text){
        cerr << "Failed to open file.\n";
        exit(1);
    }
    string lines;
    int rotation;
    text >> rotation; //store rotation value
    vector<string> linesReversed; // lines are still in reverse order

    //Get each line in file and store into a vector for  reversing
    while (getline(text, lines)){
        modifyLine(lines,rotation);
        linesReversed.push_back(lines);
    }
    //Reverse the lines in the file
    for (int i = linesReversed.size()-1; i >= 0; i--){
        cout << linesReversed[i] << endl;
    }
    //close file
    text.close();
    return 0;
}

/*Function 1: Returns the corresponding decrypted character
 Parameters: An encrypted character and rotation distance
 Returns corresponding decrypted character
 */
char decryptedChar(char encryptedChar, int rotation){
    //character literal is upper and is rotated
    if (encryptedChar <= 90 && encryptedChar >= 65){
        encryptedChar -= rotation;
        //character literal was rotated but is now lowercase(> 90)
        if (encryptedChar > 90){
            int wrapAround = encryptedChar - 90;
            encryptedChar = 64 + wrapAround;
        }
        //character literal was rotated but is not upper anymore (< 65)
        else if (encryptedChar < 65){
            int wrapAround = 65 - encryptedChar;
            // wraps around to the end of the upper alphabet
            encryptedChar = 91 - wrapAround;
        }
    }
    return encryptedChar;
}

/*Function 2: Modifies the string by using function 1 into an unencrypted form.
 Parameters: String of lines from file and rotation distance
 Does not return anything
*/
void modifyLine(string& str, int rotation){
    //for every charcter in the file, decrypt using the rotation
    for(size_t i = 0; i < str.size(); i++){
        char modified_char = decryptedChar(str[i], rotation);
        //changes each character based on function 1 result
        str[i] = modified_char;

    }
}
