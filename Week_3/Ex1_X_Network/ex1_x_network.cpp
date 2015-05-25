#include <iostream>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

bool debug = false;
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
    int cases;
    cin >> cases;
    for(int c =0; c< cases; c++){
        // Get entry
        int nbr_camarades;
        cin >> nbr_camarades;

        vector< vector<int> > camarades(nbr_camarades);

        for(int i=0; i<nbr_camarades; i++){
            int cam;
            cin >> cam;
            int nbr;
            cin >> nbr;
            for(int j=0; j<nbr; j++){
                int link;
                cin >> link;
                camarades[cam].push_back(link);
            }
        }
        int begin, end;
        cin >> begin;
        cin >> end;

        if(debug){
            for(int i=0; i<nbr_camarades; i++){
                for(int j=0; j<camarades[i].size(); j++){
                    cout << camarades[i][j];
                }
                cout << endl;
            }
        }
        
        vector<bool> cam_available(nbr_camarades, true);
        priority_queue<d_info, vector<d_info>, CompareD> paths;
        paths.push((d_info){begin, 0});
        bool not_finished = true;
        cam_available[begin] = false;

        while(!paths.empty() && not_finished){
            int node = paths.top().next_node;
            int length = paths.top().length;
            for(int i=0; i<camarades[node].size();i++){
                if(cam_available[camarades[node][i]]){
                    // Good solution
                    if(camarades[node][i] == end){
                        cout << begin << " " << end << " " << length << endl;
                        not_finished = false;
                        break;
                    }
                    // Continue looking
                    else{
                        paths.push((d_info){camarades[node][i], length+1});
                        cam_available[camarades[node][i]] = false;
                    }
                }
            }
            // Remove
            paths.pop();
        }

        if(c<cases-1)
            cout << endl;


    }    
    return 0;
}
