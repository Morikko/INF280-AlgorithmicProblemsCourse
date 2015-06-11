#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

bool debug = false;

struct Point{
    int r;
    int c;
};
enum Way {NORTH, WEST, EAST, SOUTH};

int main(int argc, char** argv){
    bool first=false;
    int cases;
    cin >> cases;
    for(int c=0; c<cases; c++){
        // Get entry
        int rows, cols;
        cin >> rows;
        cin >> cols;

        vector< vector<bool> > laby(rows, vector<bool>(cols));
        for(int r=0; r<rows; r++){
            for(int cl=0; cl<cols;cl++){
                char piece;
                cin >> piece;
                if(piece == '.')
                    laby[r][cl] = true;
            }
        }
        // Search entry
        Point start = {-1, -1};
        std::queue<Point> look_b;
        vector< vector<bool> > used(rows, vector<bool>(cols));
        look_b.push((Point){0, 0});
        look_b.push((Point){0, cols-1});
        look_b.push((Point){rows-1, 0});
        look_b.push((Point){rows-1, cols-1});
        used[0][cols-1] = true;
        used[0][0] = true;
        used[rows-1][0] = true;
        used[rows-1][cols-1] = true;
        while(!look_b.empty()){
           Point pt = look_b.front(); 
           look_b.pop();
           // Border 
           if(pt.r == 0 || pt.c == cols-1 || pt.c == 0 || pt.r == rows-1){
              for(int i=pt.r-1; i<pt.r+2; i++){
                for(int j=pt.c-1; j< pt.c+2;j++){
                    if(i>=0 && i<rows && j>=0 && j<cols && laby[i][j] && !used[i][j]){
                        look_b.push((Point){i, j});
                        used[i][j] = true;
                    }
                }
              } 
           }
           // It's in courtyard
           else if(!(!laby[pt.r-1][pt.c]&&!laby[pt.r+1][pt.c] || !laby[pt.r][pt.c-1]&&!laby[pt.r][pt.c+1])){
              for(int i=pt.r-1; i<pt.r+2; i++){
                for(int j=pt.c-1; j< pt.c+2;j++){
                    if(i>0 && i<rows-1 && j>0 && j<cols-1 && laby[i][j] && !used[i][j]){
                        look_b.push((Point){i, j});
                        used[i][j] = true;
                    }
                }
              } 
           }
           // Entry !!
           else{
               start.r = pt.r;
               start.c = pt.c;
               break;
           }
           if(debug){
               cout << endl;
               for(int r=0; r<rows; r++){
                   for(int cl=0; cl<cols;cl++){
                           if(!laby[r][cl])
                               cout << "@";
                           else if(used[r][cl])
                               cout << ":";
                           else
                               cout << ".";
                   }
                   cout << endl;
               }
               cout << endl;

           }

        }

        // Get first way
        Way way;
        if(start.r-1>=0 && laby[start.r-1][start.c] && !used[start.r-1][start.c])
            way = NORTH;
        else if(start.r+1<rows && laby[start.r+1][start.c] && !used[start.r+1][start.c])
            way = SOUTH;
        else if(start.c-1>=0 && laby[start.r][start.c-1] && !used[start.r][start.c-1])
            way = WEST;
        else if(start.c+1<cols && laby[start.r][start.c+1] && !used[start.r][start.c+1])
            way = EAST;
        else
            return 1;

        // Search courtyard entry
        Point court_entry = {-1 , -1};
        std::queue<Point> look;
        look.push((Point){rows/2, cols/2});
        used[rows/2][cols/2] = true;
        while(!look.empty()){
           Point pt = look.front(); 
           look.pop();
           // It's in courtyard
           if(!(!laby[pt.r-1][pt.c]&&!laby[pt.r+1][pt.c] || !laby[pt.r][pt.c-1]&&!laby[pt.r][pt.c+1])){
              for(int i=pt.r-1; i<pt.r+2; i++){
                for(int j=pt.c-1; j< pt.c+2;j++){
                    if(laby[i][j] && !used[i][j]){
                        look.push((Point){i, j});
                        used[i][j] = true;
                    }
                }
              } 
           }
           // Entry !!
           else{
               court_entry.r = pt.r;
               court_entry.c = pt.c;
               break;
           }

        }
            
        used[court_entry.r][court_entry.c] = false;
        
    
        if(debug){
            cout << "Start : " << start.r << "," <<  start.c <<endl;
            cout << "Courtyard : " << court_entry.r << "," <<  court_entry.c <<endl;
            cout << "Way : " << way << endl;
            cout << endl;
            for(int r=0; r<rows; r++){
                for(int cl=0; cl<cols;cl++){
                    if(r == start.r && cl == start.c)
                        cout << 'X';
                    else if (r == court_entry.r && court_entry.c == cl)
                        cout << 'C';
                    else{
                        if(laby[r][cl])
                            cout << ".";
                        else
                            cout << "@";
                    }
                }
                cout << endl;
            }
            cout << endl;
        }

        // Path
        Point current = start;
        while(true){
            if(debug){
                cout << endl;
                for(int r=0; r<rows; r++){
                    for(int cl=0; cl<cols;cl++){
                        if(r == current.r && cl == current.c)
                            cout << 'H';
                        else if(r == start.r && cl == start.c)
                            cout << 'X';
                        else if (r == court_entry.r && court_entry.c == cl)
                            cout << 'C';
                        else{
                            if(laby[r][cl])
                                cout << ".";
                            else
                                cout << "@";
                        }
                    }
                    cout << endl;
                }
                cout << endl;
                char a;
                cin >> a;
            }

            Point next;
            Way n_way;
            // Finish
            if(current.r == court_entry.r && current.c == court_entry.c){
                cout << "YES" << endl;
                break;
            }
            ///////////////
            // First left
            if(way==NORTH){
                next = (Point){current.r, current.c-1};
                n_way = WEST;
            }
            else if(way==SOUTH){
                next = (Point){current.r, current.c+1};
                n_way = EAST;
            }
            else if(way==EAST){
                next = (Point){current.r-1, current.c};
                n_way = NORTH;
            }
            else{
                next = (Point){current.r+1, current.c};
                n_way = SOUTH;
            }

            // Take 
            if(laby[next.r][next.c]){
                // Game Over
                if(used[next.r][next.c]){
                    cout << "NO" << endl;
                    break;
                }
                way = n_way;
                current = next;
                used[next.r][next.c] = true;
                continue;
            }
            /////////////////
            // Second Forward
            if(way==NORTH)
                next = (Point){current.r-1, current.c};
            else if(way==SOUTH)
                next = (Point){current.r+1, current.c};
            else if(way==EAST)
                next = (Point){current.r, current.c+1};
            else
                next = (Point){current.r, current.c-1};

            // Take 
            if(laby[next.r][next.c]){
                // Game Over
                if(used[next.r][next.c]){
                    cout << "NO" << endl;
                    break;
                }
                current = next;
                used[next.r][next.c] = true;
                continue;
            }
            //////////////////////
            // End right
            if(way==NORTH){
                next = (Point){current.r, current.c+1};
                n_way = EAST;
            }
            else if(way==SOUTH){
                next = (Point){current.r, current.c-1};
                n_way = WEST;
            }
            else if(way==EAST){
                next = (Point){current.r+1, current.c};
                n_way = SOUTH;
            }
            else{
                next = (Point){current.r-1, current.c};
                n_way = NORTH;
            }
            
            // Take 
            if(laby[next.r][next.c]){
                // Game Over
                if(used[next.r][next.c]){
                    cout << "NO" << endl;
                    break;
                }
                way = n_way;
                current = next;
                used[next.r][next.c] = true;
                continue;
            }
            ///////////////////
            // Fuck
            cout << "NO" << endl;
            break;

        }
        if(c<cases-1)
            cout << endl;
    }
    return 0;
}
