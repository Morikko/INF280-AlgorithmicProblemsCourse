#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

bool debug = true;
int calc_ppcm(int X, int Y);

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
        vector< vector< vector<bool> > > available(ppcm, vector< vector<bool> >(size, vector<bool>(size, false)));
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
