#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

bool debug = false;
int tasks, rules;

vector<int> task_order;
int target_task[100];
int dependencies[100];
int depend[100][100];

vector<int> insertBefore(int ref, int target);
bool isAfter(int ref, int target);

void heapsort(int* tab, int* tab1, int* tab2, int max);
void tam(int *tab, int* tab1, int* tab2, int node, int n);
void inverse(int* val1, int* val2);

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
       
        // Get dependencies 
        for(int r=0; r<rules; r++){
            cin >> target_task[r];
            cin >> dependencies[r];

            for(int d=0; d<dependencies[r]; d++){
                cin >> depend[r][d];
            }
        }
        int temp[100];
        for(int k=0; k<100; k++)
            temp[k] = k;

        // Order
        heapsort(target_task, dependencies, temp, rules);
        
        // Threat the rukes
        for(int r=0; r<rules; r++){
            heapsort(depend[temp[r]], NULL, NULL, dependencies[r]);
            for(int d=0; d<dependencies[r]; d++){
                if(isAfter(target_task[r], depend[temp[r]][d]))
                    task_order = insertBefore(target_task[r], depend[temp[r]][d]);
            }
        }
        
        // Print output
        for(int t=0; t<tasks; t++){
            cout << task_order[t];
            if(t<tasks-1)
                cout << " ";
        }

       cout << endl; 
       if(c<cases-1){
           cout << endl;
           task_order.clear();
       }

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

void heapsort(int* tab, int* tab1, int* tab2, int max){
    for(int i((max-1)/2); i>=0; i--)
        tam(tab, tab1, tab2, i, max-1);
    for(int i(max-1); i>=1; i--){
        inverse(&tab[i], &tab[0]);
        if(tab1 != NULL)
            inverse(&tab1[i], &tab1[0]);
        if(tab2 != NULL)
            inverse(&tab2[i], &tab2[0]);
        tam(tab, tab1, tab2, 0, i-1);
    }
}

void tam(int *tab, int* tab1, int* tab2, int node, int n){
    int k = node, j = 2*k;
    while(j<=n){
        if(j < n && tab[j] < tab[j+1])
            j++;
        if(tab[k] < tab[j]){
            inverse(&tab[k], &tab[j]);
            if(tab1 != NULL)
                inverse(&tab1[k], &tab1[j]);
            if(tab2 != NULL)
                inverse(&tab2[k], &tab2[j]);
            k = j;
            j = 2*k;
        }else
            break;
   }
}

void inverse(int* val1, int* val2){
    int temp = *val1;
    *val1 = *val2;
    *val2 = temp;
}
