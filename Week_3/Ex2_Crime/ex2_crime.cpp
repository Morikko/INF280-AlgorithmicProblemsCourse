#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cfloat>

using namespace std;

bool debug = false;
float level[100], height[100], width[100], depth[100], volume;

void heapsort(float* tab, float* tab1, float* tab2, float* tab3, int max);
void tam(float *tab, float* tab1, float* tab2, float* tab3, int node, int n);
void inverse(float* val1, float* val2);

int main(int argc, char** argv){
    int cases;
    cin >> cases;
    cout << std::fixed << std::setprecision(2);
    for(int i=0; i<cases; i++){
        /* Read the entry */
        int nbr_cisterns;
        cin >> nbr_cisterns;
        for(int c=0; c<nbr_cisterns; c++){
            cin >> level[c];
            cin >> height[c];
            cin >> width[c];
            cin >> depth[c];
        }

        cin >> volume;

        heapsort(level, height, width, depth, nbr_cisterns);

        if(debug){
            for(int c=0; c<nbr_cisterns; c++){
                cout << "Cistern " << c << " : " << level[c] << " " << height[c] << " " << width[c] << " " <<depth[c] << endl;
            }
        }   

        float total_level = 0;
        int cistern = 0;
        float min_level, min_height, next_level, current_height, eq_vol;
        while(volume>0 && cistern < nbr_cisterns){
            while(level[cistern] == 0 && height[cistern] == 0)
                cistern++;
            min_level = level[cistern];
            // Only support
            if(min_level>0){
                for(int c=cistern; c<nbr_cisterns; c++){
                    level[c] -= min_level;
                }
                total_level += min_level;
            // We touch a cistern
            }else{
                // Take the smallest cistern and the next smallest height
                min_height = FLT_MAX;
                for(int c=cistern; c<nbr_cisterns-1 && level[c]==0; c++){
                    if(height[c] < min_height)
                        min_height = height[c];
                    if(level[c+1]>0){
                        next_level = level[c+1];
                        break;
                    }
                }
                
                // Take the smallest height before change
                // Cistern is smaller than height
                if(min_height<next_level){
                    current_height = min_height;
                // Height is bigger then cistern
                }else{
                    current_height = next_level;
                }
                
                // Find equivalent volume for all cisterns at the level
                eq_vol = 0;
                for(int c=cistern; c<nbr_cisterns && level[c]==0; c++){
                    if(height[c] > 0){
                        eq_vol += current_height * width[c] * depth[c];
                    } 
                }

                // Update value
                // End
                if(eq_vol > volume){
                    total_level += (volume/eq_vol) * current_height;
                    volume = 0;
                }else{
                    total_level += current_height;
                    volume -= eq_vol;
                }
               
                for(int c=cistern; c<nbr_cisterns; c++){
                    if(level[c]>0)
                        level[c] -= current_height;
                    else
                        height[c] -= current_height;
                }

            }
        }

        if(volume==0)
            cout << total_level << endl;
        else
            cout << "OVERFLOW" << endl;

        if(i<cases-1)
            cout << endl;

    }    
    return 0;
}

void heapsort(float* tab, float* tab1, float* tab2, float* tab3, int max){
    for(int i((max-1)/2); i>=0; i--)
        tam(tab, tab1, tab2, tab3, i, max-1);
    for(int i(max-1); i>=1; i--){
        inverse(&tab[i], &tab[0]);
        inverse(&tab1[i], &tab1[0]);
        inverse(&tab2[i], &tab2[0]);
        inverse(&tab3[i], &tab3[0]);
        tam(tab, tab1, tab2, tab3, 0, i-1);
    }
}

void tam(float *tab, float* tab1, float* tab2, float* tab3, int node, int n){
    int k = node, j = 2*k;
    while(j<=n){
        if(j < n && tab[j] < tab[j+1])
            j++;
        if(tab[k] < tab[j]){
            inverse(&tab[k], &tab[j]);
            inverse(&tab1[k], &tab1[j]);
            inverse(&tab2[k], &tab2[j]);
            inverse(&tab3[k], &tab3[j]);
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
