#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool debug = true;

int main(int argc, char** argv){
    int cases;
    cin >> cases;
    for(int c=0; c<cases; c++){  
        /* Get the entry */
        int number, length;
        vector<int> items;
        cin >> number;
        cin >> length;
        
        for(int i=0;i<number;i++){
            int temp;
            cin >> temp;
            items.push_back(temp);
        }
        sort(items.begin(), items.end());

        if(debug){
            cout << "SORT" << endl;
            for(int i=0; i<number;i++)
                cout << items[i] << endl;
            cout << endl;
        }
        
        int bins = 0;
        int low_index = 0, high_index = items.size()-1;

        while(low_index <= high_index){
            if(items[low_index] + items[high_index] <= length){
                low_index++;
                high_index--;
                bins++;
            }else{
                high_index--;
                bins++;
            }
        }

        cout << bins << endl; 
        if(c<cases-1)
            cout << endl;
    }
    return 0;
}
