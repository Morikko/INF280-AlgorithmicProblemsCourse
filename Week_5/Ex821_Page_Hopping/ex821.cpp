#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <vector>
#include <map>
#include <climits>

using namespace std;

bool debug = false;

int main(int argc, char** argv){
    cout << std::fixed << std::setprecision(3);
    int cases=0;
    while(true){
        cases++;
        /* Get the input */
        int size=0;

        vector< vector<int> > links(100, vector<int>());
        bool first = true;
        while(true){
            int a, b;
            cin >> a;
            cin >> b;
            if(a==0 && b==0)
                break;
            first = false;
            links[a-1].push_back(b-1);
        }
        // Two first numbers are 0
        if(first)
            break;

        // Update tab and size
        map<int, int> eq;
        for(int i=0; i<100; i++){
            if(links[i].size() > 0){
                size++;
                eq[i] = size-1;
            }
        }
        vector< vector<int> > dist(size, vector<int>(size, INT_MAX));
        for(int i=0; i<size; i++)
            dist[i][i] = 0;
        for(int i=0; i<100; i++){
            if(links[i].size() > 0){
                for(int j=0; j<links[i].size(); j++){
                    dist[eq[i]][eq[links[i][j]]] = 1;
                }
            }
        }


        /* Floyd-Warshall algorithm */
        for(int k=0 ; k<size; k++){
            for(int i = 0; i<size ;i++){
                for(int j=0; j<size; j++){
                    if(dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][j] > dist[i][k] + dist[k][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
        
                }
            }
        }

        int val = 0, nbr = 0;
        for(int i = 0; i<size ;i++){
            for(int j=0; j<size; j++){
                val += dist[i][j]; 
            }
        }
        nbr = size*(size-1);
        cout << "Case " << cases << ": average length between pages = " << (float)val/(float)nbr << " clicks" << endl;
    } 
    return 0;
}
