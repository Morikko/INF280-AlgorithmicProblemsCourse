#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

bool debug = false;
int* p_trees;
vector< vector<bool> > * p_graph;

class CompareD {
    public:
        bool operator()(vector<int>& d1, vector<int>& d2){
            if(d1.size() > d2.size())
                return true;
            else
                return false;
        }
};
void findNewCycles(priority_queue<vector<int>, vector< vector<int> >, CompareD>& sort_cycles, vector< vector<int> >& cycles, vector<int> sub_path);

int main(int argc, char** argv){
    int cases;
    cin >> cases;
    for(int c=0; c<cases; c++){
        /* Read the entry */
        int trees, paths;
        cin >> trees;
        cin >> paths;
        vector< vector<bool> > graph(trees, vector<bool>(trees, false));
        for(int i=0; i<paths; i++){
            int tree_from, tree_to;
            cin >> tree_from;
            cin >> tree_to;
            graph[tree_from][tree_to] = true;
            graph[tree_to][tree_from] = true;
        }
        if(debug){
            for(int i=0; i<trees; i++){
                for(int j=0; j<trees; j++){
                    cout << graph[i][j];
                }
                cout << endl;
            }
        }
        p_trees = &trees;
        p_graph = &graph;
        
        vector< vector<int> > cycles;
        priority_queue<vector<int>, vector< vector<int> >, CompareD> sort_cycles;
        for(int i=0; i<trees; i++){
            findNewCycles(sort_cycles, cycles, vector<int>(1,i));
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

        bool solution = false;
        while(!sort_cycles.empty()){
            vector<int> cycle = sort_cycles.top();
            sort_cycles.pop();
            vector<bool> isReached(trees, false);
            int cpt_reach = trees;
            for(int j=0; j<cycle.size();j++){
                if(!isReached[cycle[j]]){
                    isReached[cycle[j]]=true;
                    cpt_reach--;
                }
                // Neighboor
                for(int k=0; k<trees; k++){
                    if(graph[cycle[j]][k]){
                        if(!isReached[k]){
                            isReached[k]=true;
                            cpt_reach--;
                        }
                    }
                }
            }
            if(cpt_reach==0){
                cout << "Case " << c+1 << ": " << cycle.size() << endl;
                solution = true;
                break;
            }
        }

        if(!solution)
            cout << "Case " << c+1 << ": impossible" << endl;
        /*
        set< set<int> > cycles;
        for(int i=0; i<trees; i++){
            findNewCycles(set<int>(1,i));
        }

        if(debug){
            for(set< set<int> >::iterator it_1=cycles.begin(); it_1!=cycles.end(); it_1++){
                cout << "Cycle " << " : ";
                for(set<int>::iterator it_2=it_1->begin(); it_2!=it_1->end(); it_2++){
                    cout << *it_2 << " ";
                }
                cout << endl;
            }
        }
        */

    }    
    return 0;
}
/*
void findNewCycles(set<int> path){
    int start_node = *(path.begin());
    int next_node;gg
    set<int> sub;

    for(int i=0; i<*p_trees;i++){
        for(int j=0; j<*p_trees;j++){
            // Check if both node are linked
            if(j!=i && (*p_graph)[i][j]){
                int node1 = i, node2 = j;
                if(node1 == start_node)
                    next_node = node2;
                else
                    next_node = node1;
                if(!visited(path, next_node){

                }else if(paths.size()>2 && next_node == *(path.end())){
                    
                }

            }
        }
    }


}
*/
/*
 * Is the cycle already found
 */
//bool isNew(set< set<int> >& v, set<int>& x){
//    if(find(v.begin(), v.end(), x) != v.end())
//        return true;
//    else
//        return false;
//}
//
///*
// * Is the node already visited
// */
//bool visited(set<int>& v, int x){
//    if(find(v.begin(), v.end(), x) != v.end())
//        return true;
//    else
//        return false;
//}

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

void findNewCycles(priority_queue<vector<int>, vector< vector<int> >, CompareD>& sort_cycles, vector< vector<int> >& cycles, vector<int> sub_path)
{

    int start_node = sub_path[0];
    int next_node;

    // visit each edge and each node of each edge
    for(int i=0; i<*p_trees;i++){
        for(int j=0; j<*p_trees;j++){
            // Check if both node are linked
            if(j!=i && (*p_graph)[i][j]){
                if( i == start_node or j == start_node)
                {
                    int node1 = i, node2 = j;

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
                        findNewCycles(sort_cycles, cycles, sub);
                    } 
                    else if( sub_path.size() > 2 && next_node == sub_path.back() )
                    {
                        // cycle found
                        vector<int> p(sub_path);
                        rotate_to_smallest(p);
                        vector<int> inv(p);
                        invert(inv);

                        if( isNew(cycles, p) && isNew(cycles, inv) ){
                            cycles.push_back( p );
                            sort_cycles.push(p); 
                       }
                    }
                }
            }
        }
    }
}
