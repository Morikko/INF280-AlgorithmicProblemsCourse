#include <iostream>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

bool debug = false;
        int cells, finish, counter;
        int nbr_mice = 0;
        int connections[100][100];
        // True if the mouse in the cell can reach the exit
        bool reach[100];
        // How many times should take a nouse to reach the exit
        int weight[100];
        queue<int> nextCell;

int main(int argc, char** argv){
    int cases;
    cin >> cases;
    for(int c =0; c< cases; c++){
        nbr_mice = 0;
        /* Read the entry */
        cin >> cells;
        cin >> finish;
        cin >> counter;

        if(debug)
            cout << "There are " << cells << " cells (" << finish <<  "," << counter << ")" << endl;

        int connection;
        cin >> connection;
        // Get the value of the connection between two cases
        for(int i = 0; i<connection; i++){
            int a, b, val;
            cin >> a;
            cin >> b;
            cin >> val;
            connections[a-1][b-1] = val;
            if(debug)
                cout << "From " << a << " to " << b << " is " << val << endl;
        }

        // Start from the end
        nextCell.push(finish-1);
        // Add mouse on case finish
        nbr_mice++;
        // While a mouse can reach the end from a cell
        while(!nextCell.empty()){
            int current = nextCell.front();
            nextCell.pop();
            for(int a=0; a<cells; a++){
                if(connections[a][current] != 0){
                    // In the time
                    if(connections[a][current]+weight[current] <= counter){
                        // Add mouse just one time
                        if(!reach[a]){
                            nbr_mice++;
                            reach[a] = true;
                        }
                        // Update weight
                        if(weight[a] == 0 || connections[a][current]+weight[current]<weight[a]){
                            weight[a] = connections[a][current]+weight[current];
                            nextCell.push(a);
                        }
                   }
                }
            }
        }

        cout << nbr_mice << endl;

        if(c<cases-1)
            cout << endl;
        // Reset array
        for(int i=0; i<cells; i++){
            for(int j=0; j<cells; j++)
                connections[i][j] = 0;
            reach[i] = false;
            weight[i] = 0;
        }
    }    
    return 0;
}


