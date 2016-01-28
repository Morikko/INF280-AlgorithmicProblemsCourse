#include <iostream>
#include <climits>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <stdio.h>

using namespace std;

#define LENGTH_MAX 1002

int str[LENGTH_MAX];
vector< vector<int> > morse_dictionary;

const string morse[26] = {".-",
            "-...",
            "-.-.",
            "-..",
            ".",
            "..-.",
            "--.",
            "....",
            "..",
            ".---",
            "-.-",
            ".-..",
            "--",
            "-.",
            "---",
            ".--.",
            "--.-",
            ".-.",
            "...",
            "-",
            "..-",
            "...-",
            ".--",
            "-..-",
            "-.--",
            "--.." };

int isWord(int word, string& phrase, int pos){
    int wSize = morse_dictionary[word].size();
    if(wSize > phrase.length()-pos)
        return 0;
    int offset = 0;
    for(int i = 0; i < wSize; i++){
        for ( int j = 0; j < morse[(morse_dictionary[word])[i]].size(); j++) {
            if(morse[(morse_dictionary[word])[i]][j] != phrase[pos + offset + j])
                return 0;
        }
        offset += morse[(morse_dictionary[word])[i]].size();
    }
    return pos + offset;
}

int search(string& phrase, int pos){
    // Pass
    if(phrase.length() == pos) {
        return 1;
    }
    // Already compute
    if ( str[pos] >= 0 ) 
        return str[pos];

    // Set to 0 the nbr of solution
    str[pos] = 0;

    // Compute
    for( int i = 0; i < morse_dictionary.size(); i++) {
        int newpos = 0;
        if( (newpos = isWord(i, phrase, pos) ) ) 
            str[pos] += search(phrase, newpos);
    }
    return str[pos];
}

int main(int argc, char** argv){
    int nbr;
    scanf("%d", &nbr);
    for(int i=0; i< nbr; i++){
        if(i>0)
            cout << endl;
        int nbr_words;
        string morse;
        morse_dictionary.clear();
        cin >> morse; 
        cin >> nbr_words;
        for(int n(0); n<nbr_words; n++){
            string temp;
            vector<int> val;
            cin >> temp;
            for(int j = 0; j < temp.size(); j++)
                val.push_back(temp[j] - 'A');
            morse_dictionary.push_back(val);
        }
        for ( int l = 0; l < LENGTH_MAX; l ++ ) { 
            str[l] = -1;
        }

        // Search number of possibility
        search(morse, 0);
        cout << str[0] << endl;
    }

    return 0;
}
