/******
 *  Tricks
 *  1. Make your algorithm as it gives you the best solution first under constraint (biggest difference between the two primes number)
 *  2. Prefer big array instead of compute a lot
 *  3. Eratosthenes algorithms
 *  ****/

#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>

#define MAX 1000002

using namespace std;

bool composite[MAX];

void eratosthenes(){
    composite[0] = composite[1] = true;
    for (int i = 2; i<MAX; i++) {
        if(composite[i])
            continue;
        for (int j=2*i; j<MAX; j+=i)
            composite[j] = true;
    }
}

int main(int argc, char** argv){
    eratosthenes();
    while (1) {
        int target;
        scanf("%d", & target);
        if( !target )
            break;
        for ( int i = 3; i < target; i += 2) {
            if(!composite[i] && !composite[target-i]) {
                printf("%d = %d + %d\n", target, i, target-i);
                break;
            }
        }
    }
    return 0;
}

