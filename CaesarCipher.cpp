// CaesarCipher.cpp
// This is a program that lets the user employ a Caesar Cipher on a message of their choice
// with a shift amount of their choice in a direction of their choice (Direction technically 
// doesn't mattter e.g. shifting left by 1 is the same as shifting right by 25 but the choice is nice)
//
// Potential Next Steps:
//  - Adding a decrypter
//  - Exception Handling for direction characters and shift values
//  - Add Unit Tests


#include <iostream>
#include <string>
#include <limits>
using namespace std;

int char2num(char C) {
    // Inputs:
    //
    // char C: Takes in a character value
    //
    // Output:
    //
    // Maps a value from 0 to 51 and will give the character the proper index of the alphabet string to be traversed  
    //
    if (C >= 'a' && C <= 'z') {
        return C - 'a'; //Maps a -> 0, b -> 1, ..., z -> 25
    }
    else if (C >= 'A' && C <= 'Z') {
        return C - 'A' + 26; //Maps A -> 26, B -> 27, ..., Z -> 51
    }
    else {
        return static_cast<int>(C); //If this else block is reached, then its outside of the range of the alphabet and thus will not be affected by the cipher
    }
}

string alphaShift(string alpha, int shift, char dir) {
    // Inputs:
    //
    // string alpha: A string containing the alphabet in order
    // int shift: An integer determining how far the alphabet will be shifted
    // char dir: Indicates the direction that the alphabet will be shifted
    //
    // Output:
    //
    // newAlpha: Returns the new alphabet that will be used to encode our message
    string firstPiece;
    string lastPiece;
    string newAlpha;
    if (shift == 0) {
        return alpha;        
    }
    if (dir == 'l') {
        firstPiece = alpha.substr(0, shift);
        lastPiece = alpha.substr(shift);
        newAlpha = lastPiece + firstPiece;
        return newAlpha;
    }
    if (dir == 'r') {
        firstPiece = alpha.substr(0, 26 - shift);
        lastPiece = alpha.substr(26 - shift);
        newAlpha = lastPiece + firstPiece;
        return newAlpha;
    }
    cout << "Direction char is invalid" << endl;
    return "Error";
}

string caesarEncrypt(string shiftedAlpha, string shiftedAlphaCap, string message) {
    // Input:
    //
    // string shiftedAlpha: Our shifted lowercase alphabet
    //
    // string shiftedAlphaCap: Our shifted uppercase alphabet
    //
    // string message: Our message to be encryped
    //
    //
    // Output:
    //
    // Returns a copy of our message using our shifted alphabets
    int length = message.length();
    string strCopy = message;
    for (int i = 0; i < length; i++) {
        if(char2num(strCopy[i]) >= 0 && char2num(strCopy[i]) <= 25) {
            strCopy[i] = shiftedAlpha[char2num(strCopy[i])];
        }
        else if(char2num(strCopy[i]) >= 26 && char2num(strCopy[i]) <= 51) {
            strCopy[i] = shiftedAlphaCap[char2num(strCopy[i]) - 26];
        }
        else {
            strCopy[i] = strCopy[i];
        }
    }
    return strCopy;
}




int main() {

    //Start out by initializing our necessary variables

    string alphabet = "abcdefghijklmnopqrstuvwxyz"; // Lowercase alphabet to be shifted
    string alphabetCap = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Uppercase alphabet to be shifted
    bool flag = true; // Flag initialized to do repeated encryption
    int shiftVal; // Initializes our shift variable
    char dir; // Initializes our direction variable
    char cont; // Initializes our loop repetition variable
    string message; // Initializes our message variable
    string encryptedMessage; // Initializes our encrpyted message variable
    string newAlpha; // Initializes our variable for our shifted lowercase alphabet
    string newAlphaCap; // Initializes our variable for our shifted uppercase alphabet

    cout << "Welcome to the Caesar Cipher! Would you like to encrypt a message? (y or n)" << endl; 

    cin >> cont;

    if(cont == 'n') {
        flag = false;
    }

    while (flag) {        

        cout << "What message would you like to encrypt?" << endl; 

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clears our input buffer to be reused

        getline(cin, message); // Polls user for message input

        cout << "How much would you like to shift your alphabet by? (Insert an integer from 0 to 25)" << endl;

        cin >> shiftVal; // Polls user for shift amount input

        cout << "In what direction? (Input 'l' or 'r')" << endl;

        cin >> dir; // Polls user for direction input

        // These lines create our shifted alphabets to be used by our encrypt function

        newAlpha = alphaShift(alphabet, shiftVal, dir);

        newAlphaCap = alphaShift(alphabetCap, shiftVal, dir);


        encryptedMessage = caesarEncrypt(newAlpha, newAlphaCap, message); // Encrypts the message

        cout << "Your Message is: " << message << endl;

        cout << "Your encrypted message is " << encryptedMessage << endl;

        cout << "Would you like to encrypt another message? (y or n)" << endl;

        cin >> cont; // Polls if user would like to continue

        if(cont == 'n') {
            flag = false; // This flag will escape the loops and end the program
        }

    }

    cout << "Thank you for encrypting!" << endl;

    return 0;
}