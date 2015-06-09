#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool debug = false;
void checkWord(string & word, int w_size, int off_x, int off_y, int off_r, int off_c, vector< vector<char> > & grid, vector < vector<bool> > & used);

int main(int argc, char** argv){
    string temp;
    bool first=false;
    int rows;
    //do{
    while(cin >> rows){  
        //if(first)
        //    cout << endl;
        first = true;
        /* Get the entry */
        int columns, nbr_words;
        //cin >> rows;
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
        vector< vector<bool> > used(rows, vector<bool>(columns));

        for(int w=0; w<nbr_words; w++){
            string word = words[w];
            int w_size = word.size()-1;
            // Read the grid
            for(int r=0; r<rows; r++){
                for(int c=0; c<columns;c++){
                    // North
                    if(r-w_size>=0){
                        checkWord(word, w_size, 0, -1, r, c, grid, used);
                    }
                    // North-East
                    if(r-w_size>=0 && c+w_size<columns){
                        checkWord(word, w_size, 1, -1, r, c, grid, used);
                    }
                    // East
                    if(c+w_size<columns){
                        checkWord(word, w_size, 1, 0, r, c, grid, used);
                    }
                    // South-East
                    if(r+w_size<rows && c+w_size<columns){
                        checkWord(word, w_size, 1, 1, r, c, grid, used);
                    }
                    // South
                    if(r+w_size<rows){
                        checkWord(word, w_size, 0, 1, r, c, grid, used);
                    }
                    // South-West
                    if(r+w_size<rows && c-w_size>=0){
                        checkWord(word, w_size, -1, 1, r, c, grid, used);
                    }
                    // West
                    if(c-w_size>=0){
                        checkWord(word, w_size, -1, 0, r, c, grid, used);
                    }
                    // North-West
                    if(r-w_size>=0 && c-w_size>=0){
                        checkWord(word, w_size, -1, -1, r, c, grid, used);
                    }
                }
            }
        }
        if(debug){
            for(int r=0; r<rows; r++){
                for(int c=0; c<columns;c++){
                    cout << (used[r][c]);
                }
                cout << endl;
            } 
            cout << endl;
        }

        for(int r=0; r<rows; r++){
            for(int c=0; c<columns;c++){
                if(!used[r][c])
                    cout << grid[r][c];
            }
        } 
        cout << endl;        

    }//while(getline(cin,temp));    
    return 0;
}

void checkWord(string & word, int w_size, int off_x, int off_y, int off_r, int off_c, vector< vector<char> > & grid, vector < vector<bool> > & used){
    // Check word
    for(int s=0; s<=w_size; s++){
        if(word[s] != grid[off_r][off_c])
            return;
        off_r += off_y;
        off_c += off_x;
    }
    // Update used letter        
    for(int s=0; s<=w_size; s++){
        off_r -= off_y;
        off_c -= off_x;
        used[off_r][off_c] = true;
    }

}
