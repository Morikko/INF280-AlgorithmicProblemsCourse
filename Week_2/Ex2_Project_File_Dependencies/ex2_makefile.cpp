#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

bool debug = true;
int tasks, rules;

vector<int> task_order;

vector<int> insertBefore(int ref, int target);
bool isAfter(int ref, int target);

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
                int depen;
                cin >> depen;
                if(isAfter(target_task, depen))
                    task_order = insertBefore(target_task, depen);

            }

        }
        for(int t=0; t<tasks; t++)
           cout << task_order[t] << " ";

       cout << endl; 


    }    
    return 0;
}

// Look if a task target is after a task ref
bool isAfter(int ref, int target){
    for(int t=0; t<tasks; t++){
        if(task_order[t] == ref)
            return true;
        if(task_order[t] == target)
            return false;
    }
    return false;
}

vector<int> insertBefore(int ref, int target){
    vector<int> temp;
    for(int t=0; t<tasks; t++){
        if(task_order[t] == ref){
            temp.push_back(target);
            temp.push_back(ref);
        }else if(task_order[t] == target){
        }else{
            temp.push_back(task_order[t]);
        }
   }
   return temp;
}

