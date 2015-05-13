#include <iostream>
#include <climits>
#include <string>
#include <sstream>
#include <chrono>

using namespace std;

bool debug = true;
int nbr, money, nbr_coin;
int coins[5];

bool change(int sum, int coin, int limit_coins);

int main(int argc, char** argv){
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = chrono::system_clock::now();
    
    string temp;
    while(true){
        // Get Input
        if(!(cin >> nbr))
            break;
  
        cin >> money;
        getline(cin, temp);
        istringstream coins_value(temp);

        for(nbr_coin = 0; nbr_coin < 5 && (coins_value >> coins[nbr_coin]); nbr_coin++);

        if(debug){
            cout << "case : " << nbr << endl << "Money : " <<  money << endl << "Coins ";
            for(int i(0); i<nbr_coin; i++)
                cout << " " << coins[i];
            cout << endl;
            
        }

        // Search Solution
        if(change(money, 0, INT_MAX))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;

    }
    end = chrono::system_clock::now();
    chrono::duration<double> elapsed = end-start;
    std::cout << "Execution time : " << elapsed.count() << " s" << endl;   
    
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

