#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool debug = false;
// Ref
// Entry
vector< vector<int> > * p_events;
// Output
vector<int> * p_col_order;
// Number of one for a line
vector<int> * p_one_in_line;
// Is column already used
vector<bool> * p_col_available;
int * p_columns;
int * p_lines;
int * p_still_col;

bool search(vector<int> * v_ref);
// Has next column at least the same one if there are still ones for the lines
bool isCorrect(vector<int> * v_ref, vector<int> * v_tar);
// Update the number of ones present in a line
void removeOne(vector<int> * v_ref);
void addOne(vector<int> * v_ref);

int main(int argc, char** argv){
    int cases;
    cin >> cases;
    for(int c=0; c<cases; c++){
        /* Read the entry */
        int lines, columns, still_col;
        cin >> lines;
        cin >> columns;

        vector< vector<int> > events(columns, vector<int>(lines+1));

        vector<int> col_order;
        vector<int> one_in_line(columns);
        vector<bool> col_available(columns, true);

        p_columns = &columns;
        p_lines = &lines;
        p_events = &events;
        p_col_order = &col_order;
        p_one_in_line = &one_in_line;
        p_col_available = &col_available;
        p_still_col = &still_col;

        // Index at the beginning
        for(int i=0; i<columns;i++){
            events[i][0] = i;
        }


        for(int l=0; l<lines; l++){
            string temp;
            cin >> temp;
            int ones = 0;
            for(int i=0; i<columns;i++){
                if((events[i][l+1] = (int)temp[i]-(int)48) == 1 && i>0)
                    ones++;
            }
            one_in_line[l] = ones;
        }

        if(debug){
            cout << "Lines : " << lines << endl;
            cout << "Columns : " << columns << endl;
            for(int i=0; i<columns;i++){
                for(int l=0; l<lines+1; l++){
                    cout << events[i][l];
                    if(l==0)
                        cout << ".";
                }
                cout << endl;
            }
            cout << "-----------------" << endl; 
            for(int i=0; i<lines;i++)
                cout << i << "." << one_in_line[i] << endl;
        }

        /* Let's search */
        col_order.push_back(0);
        *p_still_col = columns-1;
        search(&(events[0]));

        /* Print result */
        for(int i=0; i<columns; i++)
            cout << col_order[i] << endl;

        if(c<cases-1)
            cout << endl;
    
    }    
    return 0;
}

bool search(vector<int> * v_ref){
    for(int i=1; i<*p_columns; i++){
        // Column not used
        if((*p_col_available)[i] == true){
            if(isCorrect(v_ref, &(*p_events)[i])){
                // Take current column and update value
                (*p_col_order).push_back(i);
                removeOne(&(*p_events)[i]);
                (*p_col_available)[i] = false;
                (*p_still_col)--;
                // Continue searching
                if(*p_still_col > 0){
                    if(search(&(*p_events)[i])){
                        return true;
                    }
                // Done                   
                }else{
                    return true;
                }
            }
        }
    }
    // No solution further
    // Update value to remove current column
    int remove = (*p_col_order).back();
    (*p_col_order).pop_back();
    addOne(&(*p_events)[remove]);
    (*p_col_available)[remove] = true;
    (*p_still_col)++;
    return false;
}

bool isCorrect(vector<int> * v_ref, vector<int> * v_tar){
    for(int l=1; l<=(*p_lines); l++){
        // Need a one in next col but there isn't
        if((*v_ref)[l] == 1 && (*v_ref)[l] != (*v_tar)[l] && (*p_one_in_line)[l-1] > 0)
            return false;

    }
    return true;
}

void removeOne(vector<int> * v_ref){
    for(int l=1; l<=(*p_lines); l++){
        // Need a one in next col but there isn't
        if((*v_ref)[l] == 1)
            (*p_one_in_line)[l-1]--;
    }
}

void addOne(vector<int> * v_ref){
    for(int l=1; l<=(*p_lines); l++){
        // Need a one in next col but there isn't
        if((*v_ref)[l] == 1)
            (*p_one_in_line)[l-1]++;
    }
}
