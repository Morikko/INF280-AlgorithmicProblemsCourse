#include <iostream>
#include <climits>
#include <string>
#include <sstream>
#include <chrono>

using namespace std;

bool debug = false;
int money, nbr_coin;
int coins[5];

bool change(int sum, int coin, int limit_coins);

int main(int argc, char** argv){
    string temp;
    int nbrcases = 0;
    cin >> nbrcases;
    for(int nbr=0; nbr< nbrcases; nbr++){    
        cin >> money;
        cin >> nbr_coin;

        for(int n = 0; n < nbr_coin; n++)
            cin >> coins[n];

        if(debug){
            cout << "case : " << nbr << endl << "Money : " <<  money << endl << "Coins ";
            for(int i(0); i<nbr_coin; i++)
                cout << " " << coins[i];
            cout << endl;
            
        }
        if(nbr) cout << endl;
        // Search Solution
        if(change(money, 0, INT_MAX))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}

bool change(int sum, int coin, int limit_coins){
    // Set values
    int coin_val = coins[coin], rest;
    int max_coins = money/coin_val;
    if(max_coins > limit_coins)
        max_coins = limit_coins;

    // 
    for(; max_coins>0;max_coins--){
        rest = sum - max_coins*coin_val;
        // Good solution
        if(rest == 0)
            return true;
        // Continue to next type of coin
        else if(rest > 0){
            if(coin+1<nbr_coin){
                if(change(rest, coin+1, max_coins))
                    return true;
            }
        }
    }

    // No solution found
    return false;
}

