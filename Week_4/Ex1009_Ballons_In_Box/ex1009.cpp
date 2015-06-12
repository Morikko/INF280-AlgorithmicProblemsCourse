#include <iostream>
#include <string>
#include <vector>
#include <cfloat>
#include <cmath>

# define M_PI           3.14159265358979323846

using namespace std;

bool debug = false;

struct Point{
    int x;
    int y;
    int z;
    int diameter;
};

int main(int argc, char** argv){
    bool first=true;
    int nbr_points;
    int box_nbr = 0;
    cin >> nbr_points;
    while(nbr_points>0){
        
        float volume;
        Point border_low, border_high;
        vector<Point> points(nbr_points);
        vector< vector<float> > distance(nbr_points, vector<float>(nbr_points+1, FLT_MAX));
        vector< bool > done(nbr_points, false);

        if(first)
            first = false;
        else
            cout << endl;
        box_nbr++;
        // Get entry
        cin >> border_low.x;
        cin >> border_low.y;
        cin >> border_low.z;
        cin >> border_high.x;
        cin >> border_high.y;
        cin >> border_high.z;

        for(int i=0;i<nbr_points;i++){
            cin >> points[i].x;
            cin >> points[i].y;
            cin >> points[i].z;
        }   

        volume = (border_high.x - border_low.x) * (border_high.y - border_low.y) * (border_high.z - border_low.z);

        // Distance Box Border
        for(int i=0;i<nbr_points;i++){
            int d_x, d_y, d_z;
            d_x = min(border_high.x - points[i].x, points[i].x - border_low.x);
            d_y = min(border_high.y - points[i].y, points[i].y - border_low.y);
            d_z = min(border_high.z - points[i].z, points[i].z - border_low.z);
            distance[i][0] = min(d_z, min(d_x, d_y));
        }

        if(debug){
            cout << "Volume : " << volume << endl;
            cout << "Distance" << endl;
            for(int i=0; i< nbr_points; i++){
                for(int j=0; j< nbr_points+1; j++)
                    cout << distance[i][j] << " ";
                cout << endl;
            }
        }
        
        
        int still_working = nbr_points;
        while(still_working>0){
            float max_dst = 0;
            int index = -1;
            for(int i=0; i< nbr_points; i++){
                // Select minimal distance before reach something for each point
                if(!done[i]){
                    float min_dst = FLT_MAX;
                    for(int j=0; j< nbr_points+1; j++){
                        if(distance[i][j] > 0)
                            min_dst = min(min_dst, distance[i][j]);
                    }
                    // Take the biggest distance among all the points
                    if(min_dst>max_dst)
                        max_dst = min_dst;
                    index = i;
                }
            }   
                  
            // Update value 
            for(int j=1; j< nbr_points+1; j++){
                if(index != j-1){
                    int x, y ,z;
                    x = abs(points[index].x - points[j-1].x);
                    y = abs(points[index].y - points[j-1].y);
                    z = abs(points[index].z - points[j-1].z);
                    float x_y = x*x+y*y;
                    distance[index][j] = (sqrt(x_y+z*z) - max_dst);
                    if(distance[index][j] <= 0)
                        done[j-1] = true;
                }
            }
            volume -= 4*M_PI*max_dst*max_dst*max_dst/(float)3;
            done[index] = true;

           still_working=0;
            for(int i=0; i<nbr_points; i++)
               if(!done[i])
                  still_working++; 
           
            if(debug){
              cout << "Volume : " << volume << endl;
              cout << "Reste : " << still_working << endl;
              cout << "Distance" << endl;
              for(int i=0; i< nbr_points; i++){
                  for(int j=0; j< nbr_points+1; j++)
                      cout << distance[i][j] << " ";
                  cout << endl;
              }
           }
        }           
       
        cout << "Box " << box_nbr << ": " << round(volume) << endl;
        
        cin >> nbr_points;
    }
    return 0;
}
