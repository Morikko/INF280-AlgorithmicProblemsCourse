#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

bool debug = false; 
int *p_cross;
vector< vector<int> > * p_graph;
bool solution;

void findNewCycles(vector< vector<int> >& cycles, vector<int> sub_path);
bool visisted( int v, const std::vector<int> & path );
void rotate_to_smallest(vector<int>& path );
void invert( std::vector<int>& path );
bool isNew(const vector< vector<int> >& cycles, const std::vector<int> & path );
void search(int* reach, vector<bool>& state_node, vector< vector<bool> > isReached);

int main(int argc, char** argv){
    string temp;
    while(getline(cin, temp)){
        if(temp.size()<2)break;
        /* Get entry */
        int cross, streets;
        stringstream ss(temp);
        ss  >> cross;
        ss  >> streets;
        
        vector< vector<int> > graph(cross, vector<int>());
        for(int i=0; i<streets; i++){
            int from, to;
            cin >> from;
            cin >> to;
            graph[from-1].push_back(to-1);
            graph[to-1].push_back(from-1);
        }
        if(debug){
            for(int i=0;i<cross;i++){
                cout << "C" << i+1 << " ";
                for(int j=0; j<graph[i].size(); j++)
                    cout << graph[i][j] << " ";
                cout << endl;
            }
            cout << endl;
        }

        p_cross = &cross;
        p_graph = &graph;

        vector< vector<int> > cycles;
        solution=true;
        for(int i=0; i<cross; i++){
            findNewCycles(cycles, vector<int>(1,i));
            // There is an odd cycle
            if(!solution)
                break;
        }
        if(debug){
            for(int i=0; i<cycles.size(); i++){
                cout << "Cycle "<< i << " : ";
                for(int j=0; j<cycles[i].size(); j++){
                    cout << cycles[i][j]+1 << " ";
                }
                cout << endl;
            }
        }

        if(solution){
            vector< vector<bool> > isReached(streets, vector<bool>(streets, false));
            vector<bool> node(cross, false);
            int reach = streets;
        }else
            cout << "Impossible" << endl;
        
        getline(cin, temp);
    }
    return 0;
}


bool visisted( int v, const std::vector<int> & path ){
    return std::find(path.begin(),path.end(),v) != path.end();
}

void rotate_to_smallest(vector<int>& path ){
    std::rotate(path.begin(), std::min_element(path.begin(), path.end()), path.end());
}

void invert( std::vector<int>& path ){
    std::reverse(path.begin(),path.end());
    rotate_to_smallest(path);
}

bool isNew(const vector< vector<int> >& cycles, const std::vector<int> & path ){
    return std::find(cycles.begin(), cycles.end(), path) == cycles.end();
}

void findNewCycles(vector< vector<int> >& cycles, vector<int> sub_path){

    int start_node = sub_path[0];
    int next_node;

    // visit each edge and each node of each edge
    for(int i=0; i<*p_cross;i++){
        for(int j=0; j<(*p_graph)[i].size(); j++){
            if( i == start_node or j == start_node)
            {
                int node1 = i, node2 = (*p_graph)[i][j];

                if(node1 == start_node)
                    next_node = node2;
                else
                    next_node = node1;

                if( !visisted(next_node, sub_path) )
                {
                    // neighbor node not on path yet
                    std::vector<int> sub;
                    sub.push_back(next_node);
                    sub.insert(sub.end(), sub_path.begin(), sub_path.end());
                    findNewCycles(cycles, sub);
                } 
                else if( sub_path.size() > 2 && next_node == sub_path.back() )
                {
                    // cycle found
                    vector<int> p(sub_path);
                    rotate_to_smallest(p);
                    vector<int> inv(p);
                    invert(inv);

                    if( isNew(cycles, p) && isNew(cycles, inv) ){
                        // ODD
                        if(p.size()%2)
                            solution=false;
                        cycles.push_back( p );
                    }
                }
            }
        }
    }
}
