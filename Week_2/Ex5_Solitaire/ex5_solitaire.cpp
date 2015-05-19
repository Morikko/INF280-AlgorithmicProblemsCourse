#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <climits>

using namespace std;

bool debug = true;
int p_current[4][2]; 
int p_target[4][2];
int distances[4][5][5] = {0};

int distance(int r1, int c1, int r2, int c2);
void searchBest(int ind);

int main(int argc, char** argv){
    // Get the entry
    for(int i=0; i<4; i++){
        cin >> p_current[i][0];
        cin >> p_current[i][1];
    }

    for(int i=0; i<4; i++){
        cin >> p_target[i][0];
        cin >> p_target[i][1];
    }

    // Search the best solutions
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            distances[0][j][i] = distance(p_current[i][0], p_current[i][1], p_target[j][0], p_target[j][1]);
        }
    }
    if(debug){
        cout << "Matrix distances" << endl;
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                cout << distances[0][i][j] << " ";
            }
            cout << endl;
        }
    }

    searchBest(0);


    // Try it

    return 0;
}

int distance(int r1, int c1, int r2, int c2){
    return abs(r1-r2)+abs(c1-c2);
}

void searchBest(int ind){
    // Get smallest value
    int small_value = INT_MAX;
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(distances[ind][i][j] < small_value && distances[ind][4][j] == 0 && distances[ind][i][4] == 0)
                small_value = distances[ind][i][j];
        }
    }
    
    // Link one piece
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(distances[ind][i][j] == small_value && distances[ind][4][j] == 0 && distances[ind][i][4] == 0){
                for(int k=0; k<5; k++){
                    for(int l=0; l<5; l++){
                        distances[ind+1][k][l] = distances[ind][k][l];
                    }
                }
                if(ind<3){
                    distances[ind+1][4][j] = i+1;
                    distances[ind+1][i][4] = j+1;
                    searchBest(ind+1);
                }else{
                    distances[ind][4][j] = i+1;
                    distances[ind][i][4] = j+1;
                    if(debug){
                        cout << "Solution" << endl;
                        for(int i=0; i<5; i++){
                            for(int j=0; j<5; j++){
                                cout << distances[ind][i][j] << " ";
                            }
                            cout << endl;
                        }
                    }
                    return;
                }

            }
        }
    }
}

// 
void isPossible(int t1, int t2, int t3, int t4){
    
}
