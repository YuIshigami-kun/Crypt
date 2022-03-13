#include <string>
#include <random>
#include <time.h>
#include <iostream>
#include "include/encrypt.h"
#include "include/decrypt.h"

using namespace std;

//I created this function for making random keys and complements
string Gen(short length){
    string r;
    vector<char> v = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    short x, y;

    for(short i = 0; i < length; i++){
        x = rand() % v.size();

        r += v[x];
    }

    return r;
}

int main(){
    string text = "abc123", encrypted, decrypted;

    srand(time(NULL)); //Random generating seed
    Encrypt encrypter; //Class for encrypting
    Decrypt decrypter; //Class for decrypting

    string KEY = Gen(208); //Must be 208 characters long
    string COMPLEMENT = Gen(100); //Must be 100 characters long

    encrypter.init(text, KEY, COMPLEMENT);
    encrypted = encrypter.encrypt(); //The complement gets deleted

    cout << "Encrypted: " << encrypted << endl << endl;

    decrypter.init(encrypted, KEY);
    decrypted = decrypter.decrypt();

    cout << "Decrypted: " << decrypted << endl;

    return 0;
}