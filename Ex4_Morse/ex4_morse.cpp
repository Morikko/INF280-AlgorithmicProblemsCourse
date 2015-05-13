#include <iostream>
#include <climits>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <chrono>

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
void search_words(int pos, string word);
bool inDictionary(string word);

int main(int argc, char** argv){
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = chrono::system_clock::now();
    
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
            cout << "case : " << nbr << endl << "Code : " << morse << endl << "Dictionary (" <<  nbr_words << " Words)" << endl;
            for(int i(0); i<nbr_words; i++)
                cout << i+1 << ". " << dictionary[i] << endl;
        }

        // Search number of possibility
        occurrence = 0;
        search_words(0, "");
        cout << occurrence << endl;
    }

    end = chrono::system_clock::now();
    chrono::duration<double> elapsed = end-start;
    std::cout << "Execution time : " << elapsed.count() << " s" << endl;   
    return 0;
}

void search_words(int pos, string word){
    vector<char> letters = search_letters(pos);
    int current_pos = pos;
    for(int i(0); i<letters.size(); i++){
        string current_word = word + letters[i];
        current_pos++;
        // End of morse
        if(current_pos == morse.size()){
            // We have find a sentence
            if(inDictionary(current_word)){
                occurrence++;
            }
            return;
        }
        // Word is good, try a new one
        if(inDictionary(current_word))
            search_words(current_pos, "");
        // Continue with same base
        search_words(current_pos, current_word);

    }

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

bool inDictionary(string word){
    if(find(dictionary.begin(), dictionary.end(), word) != dictionary.end())
        return true;
    else
        return false;
}
