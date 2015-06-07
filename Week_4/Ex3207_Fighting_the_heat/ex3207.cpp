#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool debug = true;

int main(int argc, char** argv){
    string temp;
    do{  
        /* Get the entry */
        int rows, columns, nbr_words;
        cin >> rows;
        cin >> columns;
        cin >> nbr_words;

        vector<string> words;
        for(int w=0; w<nbr_words; w++){
            cin >> temp;
            words.push_back(temp);
        }

        vector< vector<char> > grid(rows, vector<char>());
        for(int r=0; r<rows; r++){
            for(int c=0; c<columns;c++){
                char d;
                cin >> d;
                grid[r].push_back(d);
            }
        }

        if(debug){
            for(int w=0; w<nbr_words; w++){
                cout << "Word " << w+1 << " : " << words[w] << endl;
            }
            for(int r=0; r<rows; r++){
                for(int c=0; c<columns;c++){
                    cout << grid[r][c];
                }
                cout << endl;
            }
        }

    getline(cin, temp);
    
    }while(getline(cin,temp));    
    return 0;
}
