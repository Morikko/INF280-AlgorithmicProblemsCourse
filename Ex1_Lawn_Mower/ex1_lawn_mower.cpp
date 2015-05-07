#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int nx = 0, ny = 0;
float w = 0;
float x[1000], y[1000];

int main(int argc, char** argv){
    string temp;
    while(true){
        /* Read the entry */
        
        // Get first line
        cin >> nx;
        cin >> ny;
        cin >> w;
        // DEBUG
        //cout << w << " " << ny << " " << nx << " " << endl;

        for(int i(0); i<nx;i++)
            cin >> x[i];
        for(int i(0); i<ny;i++)
            cin >> y[i];
        
        /* DEBUG
        for(int i(nx-1); i>=0;i--)
            cout << x[i] << " ";
        cout << endl;
        for(int i(ny-1); i>=0;i--)
            cout << y[i] << " ";
        cout << endl;
        */

        // End of challenge
        if(nx==0 && ny==0)
            break;

        /* Threat the problem */
       // order();
        // Border 
        if(x[0]-w/2 > 0 || y[0]-w/2 > 0 || x[nx-1] + w/2 < 75 || y[ny-1] + w/2 < 100){
            cout << "NO" << endl;
            continue;
        }
        for(int i(0); i<nx-1;i++){
            if(x[i+1]-x[i] > w){
                cout << "NO" << endl;
                continue;
            }
        }
        for(int i(0); i<ny;i++){
            if(y[i+1]-y[i] > w){
                cout << "NO" << endl;
                continue;
            }
        }
        cout << "YES" << endl;

    }
    
    return 0;
}
