#include <iostream>
#include <stdio.h>
#include <climits>
#include <string>
#include <sstream>

/****
 * Tricks 
 * 1. Array mpossible keep in memory if a path was already done in order to avoid computing again
 * 2. Cumul value of coin since we have to spend at least same number of c_k+1 that c_k: put the contrainst as  part of the algorithm
 * 3. Use greedy algorithm as a state machine that choose between: pass / fail / continue
 */


using namespace std;

int cvalues[5], mpossible[100002];
bool possible( int target, int cn);

int main(int argc, char** argv){
    int ncases, topay, ncoins;
    scanf("%d", &ncases);
    for(int ncase=0; ncase < ncases; ncase++){
        scanf("%d%d", &topay, &ncoins);
        for (int i = 0; i < ncoins; i++) {
            scanf("%d", &(cvalues[i]));
            cvalues[i] += i ? cvalues[i-1] : 0;
        }
        for (int i = 0; i <= topay; i++)
            mpossible[i] = -1;
        printf("%s%s\n", ncase?"\n":"", possible(topay, ncoins)?"YES":"NO");
    }
    return 0;
}

bool possible( int target, int cn) {
    if (target < 0)
        return false; 
    if(!target)
        return true;
    if(!cn)
        return false;
    if(mpossible[target] >= 0)
        return mpossible[target];
    if(possible(target - cvalues[cn-1], cn))
        return (mpossible[target] = 1);
    if(possible(target, cn-1))
        return (mpossible[target] = 1);
    return (mpossible[target] = 0);
}

