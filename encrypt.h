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

//Return the index if it's in the string and -1 if it isn't
int find(string x, char c){
    for(short i = 0; i < x.length(); i++){
        if(x[i] == c) return i;
    }

    return -1;
}

//Main class for encrypting
class Encrypt{
    private:
        vector<char> alphabet = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
        vector<string> slicedText;
        string KEY;
        string COMPLEMENT;
        map<char, string> replacedChar;

    public:
        void init(string text, string KEY, string& COMPLEMENT);
        string encrypt();
};

//Get the variables and delete the complement
void Encrypt::init(string text, string k, string& c){
    KEY = k;
    COMPLEMENT = c; c = ""; //Delete the complement

    //Break the text into blocks(8 chars)
    for(unsigned int i = 0, s = 0, ss = 0; i < text.length(); i++){
        if(s == 8){
            s = 0; ss++;
        }
        
        if(s == 0){
            slicedText.push_back("");
            slicedText[ss] += text[i];
        }else{
            slicedText[ss] += text[i];
        }

        s++;
    }

    /*
    for(short i = 0; i < slicedText.size(); i++){
        cout << slicedText[i] << endl;
    }
    */

    //Get the replacedChar variable(4 key chars == 1 text char)
    for(short i = 0, s = 0; i < alphabet.size(); i++, s += 4){
       replacedChar[alphabet[i]] = KEY[s];
       replacedChar[alphabet[i]] += KEY[s + 1];
       replacedChar[alphabet[i]] += KEY[s + 2];
       replacedChar[alphabet[i]] += KEY[s + 3];
    }

    /*
    for(auto it = replacedChar.begin(); it != replacedChar.end(); it++){
       cout << it->first << "|" << it->second << endl;
    }
    */
}


string Encrypt::encrypt(){
    string tr = "", r = "";

    //Put the encrypted complement at the start of the file
    for(short i = 0; i < COMPLEMENT.size(); i++){
        r += replacedChar[COMPLEMENT[i]];    
    }

    //Swap the blocks
    for(int i = 0; i < slicedText.size(); i += 2){
        if(i + 1 < slicedText.size()){
            swap(slicedText[i], slicedText[i + 1]);

            //cout << "Swaped: " << slicedText[i] << " | " << slicedText[i + 1] << endl;
        }else break;
    }

    //Encrypt the text with the complement
    for(int i = 0; i < slicedText.size(); i++){
        string start = COMPLEMENT, end;

        for(short s = 0; s < slicedText[i].length(); s++){
            short f = find(start, slicedText[i][s]);

            if(f == -1){
                end += slicedText[i][s] + std::to_string(s);
            }else{
                start.replace(f, 1, std::to_string(s));
            }
        }

        //cout << start << end << endl;

        tr += start + end + '9';
    }

    //Now encrypt but with the key
    for(int i = 0; i < tr.length(); i++){
        if(replacedChar.count(tr[i]) > 0){
            r += replacedChar[tr[i]];
        }else{
            r += tr[i];
        }
    }

    return r; //Here you have
}