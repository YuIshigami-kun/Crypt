#include <string>
#include <string.h>
#include <vector>
#include <map>
//#include <iostream>

using std::string;
using std::vector;
using std::map;
//using std::cout; using std::endl;

//Extend the string to x chars
void extendString(string &x, short length){
    for(int i = 0; i < length; i++){
        if(i >= x.length()){
            x += ' ';
        }
    }
}

//Check if a char is int
bool isInt(char a){
    if(a >= '0' && a <= '9') return true;
    else return false;
}

//Check if it's in the alphabet vector
bool isSpecial(vector<char> alphabet, char b){
    for(short i = 0; i < alphabet.size(); i++){
        if(alphabet[i] == b) return false;
    }

    return true;
}

//Main class for decrypting
class Decrypt{
    private:
        vector<char> alphabet = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
        string contents = "";
        string COMPLEMENT;
        map<string, char> replacedChar;

    public:
        void init(string c, string k);
        string decrypt();

};

//Get the complement, contents and replacedChar
void Decrypt::init(string c, string k){
    string tC = c.substr(0, 400); //First 400 chars of the text is the encripted complement
    
    contents = c.substr(400, c.size()); //Removes the complement from the contents

    //cout << tC << " (" << tC.length() << ")";

    //4 chars in the key == 1 char in the alphabet
    for(short i = 0, s = 0; i < alphabet.size(); i++, s += 4){
        string x = "";
        x += k[s]; x += k[s + 1]; x += k[s + 2]; x += k[s + 3];

        replacedChar[x] = alphabet[i];
    }

    /*
    for(auto it = replacedChar.begin(); it != replacedChar.end(); it++){
       cout << it->first << "|" << it->second << endl;
    }
    */

    //Decrypt the complement
    for(short i = 0; i < tC.length(); i += 4){
        string x = "";
        x += tC[i]; x += tC[i + 1]; x += tC[i + 2]; x += tC[i + 3];

        COMPLEMENT += replacedChar[x];
    }

    //cout << "Complement: " << COMPLEMENT;
}


string Decrypt::decrypt(){
    string dText = "", result = "";
    vector<string> tResult;
    
    //Replace the 4 key chars to 1 text char
    for(int i = 0; i < contents.length(); i++){
        string x = "";

        if(isInt(contents[i]) == true || isSpecial(alphabet, contents[i]) == true){
            dText += contents[i];
        }else{
            x += contents[i];
            x += contents[i + 1];
            x += contents[i + 2];
            x += contents[i + 3];

            //cout << x << "->" << replacedChar[x] << endl;
            
            dText += replacedChar[x];

            i += 3;
        }
    }

    //cout << dText << endl;
    string x = "";
    char y;

    //Decrypt the blocks
    for(int i = 0, s = 0, s2 = 0; i < dText.length(); i++, s++){
        if(dText[i] != '9'){
            int pos = dText[i] - '0';

            if(s < 100 && isInt(dText[i]) == true){
                extendString(x, pos + 1);

                x[pos] = COMPLEMENT[s];
            }else if(s >= 100){
                if(s2 == 0){
                    y = dText[i];
                    s2++;

                }else{
                    s2 = 0;
                    extendString(x, pos + 1);

                    x[pos] = y;
                }
            }
        }else{
            s = -1;
            tResult.push_back(x);
            x = "";
        }
    }

    /*
    for(int i = 0; i < tResult.size(); i++){
        cout << tResult[i] << endl;
    }
    */

   //Swap the blocks
    for(int i = 0; i < tResult.size(); i += 2){
        if(i + 1 < tResult.size()){
            swap(tResult[i], tResult[i + 1]);

            //cout << "Swaped: " << tResult[i] << " | " << tResult[i + 1] << endl;
        }else break;
    }

    //From vector to string
    for(int i = 0; i < tResult.size(); i++){
        result += tResult[i];
    }

    return result; //Here you have
}