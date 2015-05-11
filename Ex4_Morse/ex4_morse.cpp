#include <iostream>
#include <climits>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

bool debug = true;
int nbr, nbr_words, occurrence;
/* Create binary tree for morse code
 * Left child : .
 * Right child : -
 * # : beginning
 * ! not a letter
 */
char morse_code[29] = {'#', 'E', 'T', 'I', 'A', 'N', 'M', 'S', 'U', 'R', 'W', 'D', 'K', 'G', 'O', 'H', 'V', 'F', '!', 'L', '!', 'P', 'J', 'B', 'X', 'C', 'Y', 'Z', 'Q'};
string morse;
vector<string> dictionary;

vector<char> search_letters(int pos);

int main(int argc, char** argv){
    while(true){
        // Get Input
        if(!(cin >> nbr))
            break;
        
        cin >> morse; 
        cin >> nbr_words;
        for(int i(0); i<nbr_words; i++){
            string temp;
            cin >> temp;
            dictionary.push_back(temp);
        }

        if(debug){
            cout << "case : " << nbr << endl << "Dictionary (" <<  nbr_words << " Words)" << endl;
            for(int i(0); i<nbr_words; i++)
                cout << i+1 << ". " << dictionary[i] << endl;
        }

        // Search number of possibility
        occurrence = 0;
        vector<char> result = search_letters(0);

        for(int i(0); i<result.size(); i++)
            cout << result[i] << ":";


    }
}

void search_words(){


}
/**
 * Return all the letters available at position pos in the morse code
 */
vector<char> search_letters(int pos){
    vector<char> letters;
    int pos_tree = 1, pos_code = pos;
    while(pos_code < morse.size() && pos_tree < 30){
        char code = morse[pos_code];
        // Look over the binary tree
        if(code == '.')
            pos_tree *= 2;
        else
            pos_tree = 2*pos_tree + 1;
        // Get result
        if(morse_code[pos_tree-1] != '!')
            letters.push_back(morse_code[pos_tree-1]);
        // End of array
        else
            break;
        pos_code++;
      
    }
    return letters;
}
