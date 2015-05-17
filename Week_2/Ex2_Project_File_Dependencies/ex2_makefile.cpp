#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

bool debug = true;
int tasks, rules;

vector<int> task_order;

int main(int argc, char** argv){
    int cases;
    cin >> cases;
    for(int c=0; c<cases; c++){
        /* Read the entry */
        cin >> tasks;
        cin >> rules;
        
        // Initiate tasks order in ...
        for(int t=0; t<tasks; t++)
            task_order.push_back(t+1);
        
        // Threat the rukes
        for(int r=0; r<rules; r++){
            int target_task;
            cin >> target_task;
            int dependencies;
            cin >> dependencies;

            for(int d=0; d<dependencies; d++){


            }

        }
        for(int t=0; t<tasks; t++)
           cout << task_order[t] << " ";

       cout << endl; 


    }    
    return 0;
}
