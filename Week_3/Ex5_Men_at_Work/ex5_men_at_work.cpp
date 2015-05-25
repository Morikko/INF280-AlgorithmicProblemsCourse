#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

bool debug = false;
int calc_ppcm(int X, int Y);
struct coord{
    int x;
    int y;
};    
struct d_info{
    coord c;
    int dimension;
    int length;
};

class CompareD {
    public:
        bool operator()(d_info& d1, d_info& d2){
            if(d1.length < d2.length)
                return false;
            else
                return true;
        }
};

int main(int argc, char** argv){
    string temp;
    bool first = true;
    do{
        if(first)
            first = false;
        else
            cout << endl;

        int size;
        cin >> size;
        getline(cin, temp);
        
        // Get road
        vector< vector< vector<bool> > > graph(1, vector< vector<bool> >(size, vector<bool>(size)));
        for(int i=0; i<size;i++){
            getline(cin, temp);
            for(int c=0; c<size; c++){
                if(temp[c] == '.')
                    graph[0][i][c] = true;
                else
                    graph[0][i][c] = false;
            }
        }

        // Get work schedule
        vector< vector<int> > schedule(size, vector<int>(size));
        vector<bool> duration(10, false);
        for(int i=0; i<size;i++){
            getline(cin, temp);
            for(int c=0; c<size; c++){
                schedule[i][c] = temp[c] - (int)48;
                if(schedule[i][c]>0)
                    duration[schedule[i][c]] = true;
            }
        }

        if(debug){
            for(int i=0; i<size;i++){
                for(int c=0; c<size; c++){
                    cout << graph[0][i][c];
                }
                cout << endl;
            }
            for(int i=0; i<size;i++){
                for(int c=0; c<size; c++){
                    cout << schedule[i][c];
                }
                cout << endl;
            }
        }

        // Calcul PPCM
        int ppcm = 0;
        for(int i=1; i<10; i++){
            if(duration[i]==true){
                if(ppcm==0)
                    ppcm=i;
                else
                    ppcm = calc_ppcm(ppcm,i);
            }
        }
        // Duration is half free, half in work
        ppcm *=2;
        if(debug)
            cout << "PPCM : " << ppcm << endl;

        // Create 3-dimension graph
        vector< vector< vector<bool> > > available(ppcm, vector< vector<bool> >(size, vector<bool>(size, true)));
        vector< vector<int> > cpt(size, vector<int>(size, 0));
        for(int i=1; i<ppcm; i++){
            graph.push_back(vector< vector<bool> >(size, vector<bool>(size)));
            for(int l=0; l<size; l++){
                for(int c=0; c<size; c++){
                    cpt[l][c]++;
                    if(cpt[l][c] == schedule[l][c] && schedule[l][c] > 0){
                        cpt[l][c] = 0;
                        graph[i][l][c] = !graph[i-1][l][c];
                    }else
                        graph[i][l][c] = graph[i-1][l][c];
                    //cout << graph[i][l][c];
                }
                //cout << endl;
            }
            //cout << endl << endl;
       }

        // Search shortest path
        priority_queue<d_info, vector<d_info>, CompareD> paths;
        paths.push((d_info){{0, 0}, 0, 0});
        bool not_finished = true;
        available[0][0][0] = false;

        while(!paths.empty() && not_finished){
            int x = paths.top().c.x;
            int y = paths.top().c.y;
            int dimension = (paths.top().dimension+1)%ppcm;
            int length = paths.top().length;
            // Search next available node
            vector<coord> next_cell;
            // Add down
            if(y < size-1){
                if(graph[dimension][y+1][x] && available[dimension][y+1][x])
                    next_cell.push_back((coord){x, y+1});
            }
            // Add left
            if(x < size -1){
                if(graph[dimension][y][x+1] && available[dimension][y][x+1])
                    next_cell.push_back((coord){x+1, y});
            }
            // Add wait
            if(graph[dimension][y][x] && available[dimension][y][x])
                next_cell.push_back((coord){x, y});
            // Add right
            if(x > 0){
                if(graph[dimension][y][x-1] && available[dimension][y][x-1])
                    next_cell.push_back((coord){x-1, y});
            }
            // Add up
            if(y > 0){
                if(graph[dimension][y-1][x] && available[dimension][y-1][x])
                    next_cell.push_back((coord){x, y-1});
            }
            for(int i=0; i<next_cell.size();i++){
                // Good solution
                if(next_cell[i].y == size-1 && next_cell[i].x == size-1){
                    cout << (length+1) << endl;
                    not_finished = false;
                    break;
                }
                // Continue looking
                else{
                    paths.push((d_info){{next_cell[i].x, next_cell[i].y}, dimension, length+1});
                    available[dimension][next_cell[i].y][next_cell[i].x] = false;
                }
            }
            // Remove
            paths.pop();
        }
        // No solution
        if(paths.empty() && not_finished)
            cout << "NO" << endl;
       
        if(debug)
            cout << "---------------------------" << endl;
    }while(getline(cin,temp));
    
    return 0;
}

int calc_ppcm(int X, int Y){
  int A=X;
  int B=Y;
  while (A!=B)
  {
    while (A>B) B=B+Y;
    while (A<B) A=A+X;
  }
  return A;
}
