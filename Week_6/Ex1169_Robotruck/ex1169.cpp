#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

bool debug = true;

struct Package{
    int x;
    int y;
    int weight;
};

int* p_weight;

int distribute(vector<Package> & packages, int index);

int main(int argc, char** argv){
    int cases;
    cin >> cases;
    for(int c=0; c<cases; c++){  
        /* Get the entry */
        int number, weight;
        vector<Package> packages;
        cin >> weight;
        cin >> number;

        p_weight = &weight;
        
        for(int i=0;i<number;i++){
            int x, y, w;
            cin >> x; cin >> y; cin >> w;
            packages.push_back((Package){x, y, w});
        }

        int min_steps = distribute(packages, 0);

        cout << min_steps << endl;
        
        if(c<cases-1)
            cout << endl;
    }
    return 0;
}

int count_steps(int x1, int y1, int x2, int y2){
    return abs(x1-x2) + abs(y1-y2);
}

int distribute(vector<Package> & packages, int index){
    int min_steps = INT_MAX;
    int current_steps = 0;
    int w = 0, offset = 0;
    int pos_x = 0, pos_y = 0;
    // Try every set of packages less than weight
    while(index+offset < packages.size() && w+packages[index+offset].weight <= *p_weight){
        // Calcule for current move
        Package package = packages[index+offset];
        w += package.weight;
        current_steps += count_steps(pos_x, pos_y, package.x, package.y); 
        pos_x = package.x;
        pos_y = package.y;    

        //Continue to next move
        int steps = current_steps + count_steps(pos_x, pos_y, 0, 0);
        if(index+offset+1 < packages.size())
            steps += distribute(packages, index+offset+1);
        // Update value
        offset++;
        if(min_steps>steps)
            min_steps = steps;
    }

    return min_steps;
}
