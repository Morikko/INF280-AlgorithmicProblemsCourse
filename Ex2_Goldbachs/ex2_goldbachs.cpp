#include <iostream>
#include <string>
#include <sstream>

using namespace std;

bool debug = true;
int numbers[50];
int length =0;

int main(int argc, char** argv){
    /* Read the entry */
    do{
        cin >> numbers[length];
        length++;
    }while(numbers[length-1] != 0);
    length--;

    if(debug){
        cout << "List : ";
        for(int i(0); i<length; i++)
            cout << numbers[i] << " ";
        cout << endl;
    }
    
    // Calcul primes addition
    for(int i(0); i<length; i++){
        

    }

    return 0;
}


