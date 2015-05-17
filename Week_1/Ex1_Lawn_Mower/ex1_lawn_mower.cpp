#include <iostream>
#include <string>
#include <sstream>
#include <chrono>

using namespace std;

void heapsort(float* tab, int max);
void tam(float *tab, int node, int n);
void inverse(float* val1, float* val2);

int nx = 0, ny = 0;
float w = 0;
float x[1000], y[1000];
bool debug = true;

int main(int argc, char** argv){
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = chrono::system_clock::now();

    string temp;
    while(true){
        /* Read the entry */
        
        // Get first line
        cin >> nx;
        cin >> ny;
        cin >> w;
        
        if(debug)
            cout << w << " " << ny << " " << nx << " " << endl;

        for(int i(0); i<nx;i++)
            cin >> x[i];
        for(int i(0); i<ny;i++)
            cin >> y[i];

        // End of challenge
        if(nx==0 && ny==0 && w==0)
            break;

        /* Threat the problem */
        heapsort(x, nx);
        heapsort(y, ny);
        
        if(debug){
            for(int i(nx-1); i>=0;i--)
                cout << x[i] << " ";
            cout << endl;
            for(int i(ny-1); i>=0;i--)
                cout << y[i] << " ";
            cout << endl;
        }
        
        // Border 
        if(x[0]-w/2 > 0 || y[0]-w/2 > 0 || x[nx-1] + w/2 < 75 || y[ny-1] + w/2 < 100){
            cout << "NO" << endl;
            continue;
        }
        // Stadium
        bool good = true;
        for(int i(0); i<nx-1;i++){
            if(x[i+1]-x[i] > w){
                good = false;
                break;
            }
        }
        if(!good){
            cout << "NO" << endl;
            continue;
        }
        for(int i(0); i<ny;i++){
            if(y[i+1]-y[i] > w){
                good = false;
                break;
            }
        }
        if(!good){
            cout << "NO" << endl;
            continue;
        }
        cout << "YES" << endl;

    }
   
    end = chrono::system_clock::now();
    chrono::duration<double> elapsed = end-start;
    std::cout << "Execution time : " << elapsed.count() << " s" << endl;   
    
    return 0;
}

void heapsort(float* tab, int max){
    for(int i((max-1)/2); i>=0; i--)
        tam(tab, i, max-1);
    for(int i(max-1); i>=1; i--){
        inverse(&tab[i], &tab[0]);
        tam(tab, 0, i-1);
    }
}

void tam(float *tab, int node, int n){
    int k = node, j = 2*k;
    while(j<=n){
        if(j < n && tab[j] < tab[j+1])
            j++;
        if(tab[k] < tab[j]){
            inverse(&tab[k], &tab[j]);
            k = j;
            j = 2*k;
        }else
            break;
   }
}

void inverse(float* val1, float* val2){
    float temp = *val1;
    *val1 = *val2;
    *val2 = temp;
}
