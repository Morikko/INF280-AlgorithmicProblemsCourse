#include <iostream>
#include <climits>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

bool debug = true;

struct road {
    int target_city;
    int dangerousness;
};

struct d_info{
    int next_node;
    int length;
};

class CompareD {
    public:
        bool operator()(d_info& d1, d_info& d2){
            if(d1.length < d2.length)
                return false;
            else
                return true;
        }
};

int main(int argc, char** argv){
    string temp;
    do{    
        // Get entry
        // Get graph
        int nbr_cities, nbr_roads;
        cin >> nbr_cities;
        cin >> nbr_roads;

        vector< vector<road> > roads(nbr_cities);

        for(int i=0; i<nbr_roads; i++){
            int city_from;
            cin >> city_from;
            int city_to;
            cin >> city_to;
            int danger;
            cin >> danger;
            roads[city_from-1].push_back((road){city_to-1, danger});
            roads[city_to-1].push_back((road){city_from-1, danger});
        }

        if(debug){
            for(int i=0; i<nbr_cities; i++){
                cout << "City " << i+1 << " : ";
                for(int j=0; j<roads[i].size(); j++){
                    cout << roads[i][j].target_city+1 << ":" << roads[i][j].dangerousness << " ";
                }
                cout << endl;
            }
        }
        
        // Get missions
        int nbr_missions;
        cin >> nbr_missions;

        for(int m=0; m<nbr_missions; m++){
            int begin, end;
            cin >> begin;
            begin--;
            cin >> end;
            end--;

            int min_dangerousness = INT_MAX;

            vector< vector<bool> > road_available(nbr_cities, vector<bool>(nbr_cities, true));
            priority_queue<d_info, vector<d_info>, CompareD> paths;
            paths.push((d_info){begin, 0});
            bool not_finished = true;

            while(!paths.empty() && not_finished){
                int node = paths.top().next_node;
                int length = paths.top().length;
                for(int i=0; i<roads[node].size();i++){
                    if(road_available[node][roads[node][i].target_city]){
                        // Good solution
                        if(roads[node][i].target_city == end){
                            paths.push((d_info){roads[node][i].target_city, length+roads[node][i].dangerousness});
                            road_available[node][roads[node][i].target_city] = false;
                            road_available[roads[node][i].target_city][node] = false;
                            if(min_dangerousness > length+roads[node][i].dangerousness)
                                min_dangerousness = length+roads[node][i].dangerousness;
                            //not_finished = false;
                            //break;
                        }
                        // Continue looking
                        else{
                            paths.push((d_info){roads[node][i].target_city, length+roads[node][i].dangerousness});
                            road_available[node][roads[node][i].target_city] = false;
                            road_available[roads[node][i].target_city][node] = false;
                        }
                    }
                }
                // Remove
                paths.pop();
            }
            cout << begin+1 << " " << end+1 << " " << min_dangerousness << endl;
        }

    getline(cin, temp);
    }while(getline(cin,temp));
    return 0;
}
