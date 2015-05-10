#include <iostream>
#include <string>
#include <sstream>

using namespace std;

bool debug = true;
int nbr, money, nbr_coin;
int coins[5];

int main(int argc, char** argv){
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

    }
    return 0;
}

