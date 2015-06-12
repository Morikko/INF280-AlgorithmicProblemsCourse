#include <iostream>
#include <climits>
#include <string>
#include <sstream>
#include <queue>
#include <algorithm>

/**************
 * Kruskal algorithm from https://gist.github.com/calmhandtitan/8119078
 * *************/

#define pii pair<int, int>
#define pip pair<int, pii>
#define F first
#define S second

using namespace std;

bool debug = false;

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

//class implementing Union Find Data Structure with Path Compression
class Union_Find
{
  public:
 
	vector<int> id, sz;
	Union_Find(int n)	//class constructor
	{
		for (int i = 0; i < n; ++i)
		{
			id.push_back(i);
			sz.push_back(1);
		}
	}
	
	int root(int i)
	{
		while(i != id[i])
		{
			id[i] = id[id[i]];	//path Compression
			i = id[i];
		}
		return i;
	}
	int find(int p, int q)
	{
		return root(p)==root(q);
	}
	void unite(int p, int q)
	{
		int i = root(p);
		int j = root(q);
 
		if(sz[i] < sz[j])
		{
			id[i] = j;
			sz[j] += sz[i];
		}
		else
		{
			id[j] = i;
			sz[i] += sz[j];
		}
	}
};
 
void Kruskal_MST(long long int * T, int n, int e, vector<pip> & graph, vector< vector<road> > & graph_best)
{
	Union_Find UF(n);
	int u, v;
 
	for (int i = 0; i < e; ++i)
	{
		u = graph[i].S.F;
		v = graph[i].S.S;
		if( !UF.find(u, v) )
		{
//			printf("uniting %d and %d\n",u,v );
			UF.unite(u, v);
			*T += graph[i].F;
            graph_best[u-1].push_back((road){v-1, graph[i].F});
            graph_best[v-1].push_back((road){u-1, graph[i].F});
		}
	}
}
 
int main(int argc, char** argv){
    string temp;
    bool first = true;
    do{    
        if(first)
            first = false;
        else
            cout << endl;
        // Get entry
        // Get graph
        int nbr_cities, nbr_roads;
        cin >> nbr_cities;
        cin >> nbr_roads;

        vector< pip > roads(nbr_roads);

        for(int i=0; i<nbr_roads; i++){
            int city_from;
            cin >> city_from;
            int city_to;
            cin >> city_to;
            int danger;
            cin >> danger;
            roads[i] = pip( danger, pii(city_from, city_to));
        }
        sort(roads.begin(), roads.end());	//sort the edges in increasing order of cost

        // Misinum spanning tree
        vector< vector<road> > roads_best(nbr_cities, vector<road>());

        long long int T = 0;
        Kruskal_MST(&T, nbr_cities, nbr_roads, roads, roads_best);

        if(debug){
            for(int i=0; i<nbr_cities; i++){
                cout << "City " << i+1 << " : ";
                for(int j=0; j<roads_best[i].size(); j++){
                    cout << roads_best[i][j].target_city+1 << ":" << roads_best[i][j].dangerousness << " ";
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
            int max_dangerousness = 0;
             
            vector< vector<bool> > city_available(nbr_cities, vector<bool>(nbr_cities, true));
            vector<int> cities_dangerousness(nbr_cities, 0);
            priority_queue<d_info, vector<d_info>, CompareD> paths;
            paths.push((d_info){begin, max_dangerousness});
            bool not_finished = true;

            while(!paths.empty() && not_finished){
                int node = paths.top().next_node;
                int length = paths.top().length;
                for(int i=0; i<roads_best[node].size();i++){
                    if(city_available[node][roads_best[node][i].target_city]){
                        // Good solution
                        if(roads_best[node][i].target_city == end){
                            //if(max_dangerousness < length+roads_best[node][i].dangerousness)
                            //    min_dangerousness = length+roads_best[node][i].dangerousness;
                            max_dangerousness = length<roads_best[node][i].dangerousness?roads_best[node][i].dangerousness:length;
                            not_finished = false;
                            break;
                        }
                        // Continue looking
                        else{
                            paths.push((d_info){roads_best[node][i].target_city, length<roads_best[node][i].dangerousness?roads_best[node][i].dangerousness:length});
                            city_available[node][roads_best[node][i].target_city] = false;
                            city_available[roads_best[node][i].target_city][node] = false;
                        }
                    }
                }
                // Remove
                paths.pop();
            }
            if(debug)
                cout << begin+1 << " " << end+1 << " " << max_dangerousness << endl;
            else
                cout << max_dangerousness << endl;

        }

    getline(cin, temp);
    }while(getline(cin,temp));
    return 0;
}
