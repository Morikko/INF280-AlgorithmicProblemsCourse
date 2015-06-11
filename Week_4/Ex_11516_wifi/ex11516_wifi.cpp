#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

bool debug = false;

int main(int argc, char** argv){
    cout << std::fixed << std::setprecision(1);
    int cases;
    cin >> cases;
    for(int c=0; c<cases; c++){
        /* Read the entry */
        int nbr_access, nbr_houses;
        vector<int> house_number;
        cin >> nbr_access;
        cin >> nbr_houses;

        for(int h=0; h<nbr_houses; h++){
            int temp;
            cin >> temp;
            house_number.push_back(temp);
        }

        
        int distance = (*house_number.begin() + *--house_number.end()) / nbr_access;
        //cout << "Distance : " << distance << endl;
        
        int region_limit = distance;
        int region_start = house_number[0], region_end = 0;
        float max_distance = 0;
        for(int h=1; h<nbr_houses; h++){
            if(house_number[h]>region_limit){
                region_end = house_number[h-1];
                if( (region_end -region_start)/(float)2 > max_distance )
                    max_distance = (region_end - region_start) / (float)2;
                region_start = house_number[h];
                region_limit += distance;
            }
        }
        region_end = house_number[nbr_houses-1];
        if( (region_end -region_start)/(float)2 > max_distance )
            max_distance = (region_end - region_start) / (float)2;

        cout << round(max_distance*10)/10 << endl;

        //if(c<cases-1)
        //    cout << endl;
    
    }    
    return 0;
}
