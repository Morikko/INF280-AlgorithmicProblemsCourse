#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

bool debug = true;
int* p_trees;
vector< vector<bool> > * p_graph;

void findNewCycles(vector< vector<int> >& cycles, vector<int> sub_path);

int main(int argc, char** argv){
    int cases;
    cin >> cases;
    for(int i=0; i<cases; i++){
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
        for(int i=0; i<trees; i++){
            findNewCycles(cycles, vector<int>(1,i));
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
    int next_node;
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

void findNewCycles(vector< vector<int> >& cycles, vector<int> sub_path)
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
                        findNewCycles(cycles, sub);
                    } 
                    else if( sub_path.size() > 2 && next_node == sub_path.back() )
                    {
                        // cycle found
                        vector<int> p(sub_path);
                        rotate_to_smallest(p);
                        vector<int> inv(p);
                        invert(inv);

                        if( isNew(cycles, p) && isNew(cycles, inv) )
                            cycles.push_back( p );
                    }
                }
            }
        }
    }
}
