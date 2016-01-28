#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;
 
/*** Nice tricks
 * O. Using library for sorting instead of doing its own function
 * 1. Use function for testing nx and ny
 * 2. Add -w/2 and l+w/2 for automaticaly testing the border
 */

#define WIDTH 75
#define LENGTH 100

bool one_way(int n, int l, double w);

int main() {
    int nx, ny;
    double w;
    while(1) {
        scanf("%d %d", &nx, &ny);
        if (!nx) 
            break;
        scanf("%lf", &w);
        bool bx = one_way(nx, WIDTH, w);
        bool by = one_way(ny, LENGTH, w);
        printf("%s\n", bx && by ? "YES" : "NO");
    }
    return 0;
}

bool one_way(int n, int l, double w){
    vector<double> v;
    v.push_back(-w/2);
    v.push_back(l+w/2);
    for(int i = 0; i < n; i++) {
        double pos;
        scanf("%lf", &pos);
        v.push_back(pos);
    }
    sort(v.begin(), v.end());
    for (unsigned int i = 1; i < v.size(); i++) {
        if (v[i] - v[i-1] > w)
            return false;
    }
    return true;    
}
