#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool debug = true;
bool recognize(int index, string & story, int memory);

int main(int argc, char** argv){
    int cases;
    cin >> cases;
    for(int c=1; c<=cases; c++){  
        /* Get the entry */
        int names, memory;
        string story;
        cin >> names;
        cin >> memory;
        cin >> story;

        /* count recognized */
        int recognized = 0;
        for(int i=0; i<names; i++){
            if(recognize(i, story, memory))
                recognized++;
        }

        cout << "Case " << c << ": " << recognized << endl; 
    }
    return 0;
}

bool recognize(int index, string & story, int memory){
    char name = story[index];
    for(int i=index-1, m=memory; i>=0 && m>0; i--){
        m--;
        if(story[i] == name)
            return true;
    }
    return false;
}
