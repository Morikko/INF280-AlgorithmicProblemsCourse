#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <climits>
#include <vector>

using namespace std;

bool debug = true;
int p_current[4][2]; 
int p_target[4][2];
int order[4];
int distances[4][5][5];
int board[8][8][8];

int distance(int r1, int c1, int r2, int c2);
void searchBest(int ind);
void isPossible(int ind);

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
                order[3-ind] = j;
                if(ind<3){
                    distances[ind+1][4][j] = i+1;
                    distances[ind+1][i][4] = j+1;
                    searchBest(ind+1);
                }else{
                    distances[ind][4][j] = i+1;
                    distances[ind][i][4] = j+1;
                    if(debug){
                        cout << "Solution" << endl;
                        for(int k=0; k<5; k++){
                            for(int l=0; l<5; l++){
                                cout << distances[ind][k][l] << " ";
                            }
                            cout << endl;
                        }
                    }
                    isPossible(0);
                    return;
                }

            }
        }
    }
}

// 
void isPossible(int ind){
    if(debug){
        cout << "Order = ";
        for(int v=0; v<4; v++)
            cout << order[v]+1 << " ";
        cout << endl;
    }
    vector<int> id, move_x, move_y;
    
    // Get allowed moves
    for(int i=0; i<4; i ++){
        int x = 0, y = 0;
        int mul_x = 0, mul_y = 0;
        int target= distances[3][4][i];
        if(x == p_target[target][0]){
            mul_x = 0;
        }else if(y == p_target[target][1]){
            mul_y = 0;
        }else if(x > p_target[target][0]){
            mul_x = -1;
        }else if(x < p_target[target][0]){
            mul_x = 1;
        }else if(y > p_target[target][1]){
            mul_y = -1;
        }else if(y < p_target[target][1]){
            mul_y = 1;
        }

        int m_x = 0, m_y = 0;
        if((x + mul_x*1) < 8 && board[ind][x+mul_x*1][y] == 0){
            m_x = mul_x*1;
        }else if((x + mul_x*2) < 8 && board[ind][x+mul_x*2][y] == 0){
            m_x = mul_x*2;
        }

        if((y + mul_y*1) < 8 && board[ind][x][y+mul_y*1]== 0){
            m_y = mul_y*1;
        }else if((y + mul_y*2) < 8 && board[ind][x][y+mul_y*2]== 0){
            m_y = mul_y*2;
        }

        if(m_x != 0){
            id.push_back(i);
            move_x.push_back(m_x);        
            move_y.push_back(y);
        }        
        if(m_y != 0){
            id.push_back(i);
            move_x.push_back(x);        
            move_y.push_back(m_y);
        }        
   }    


    // For each move adapt board and go to move+1
}
