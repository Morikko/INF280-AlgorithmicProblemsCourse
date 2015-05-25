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
