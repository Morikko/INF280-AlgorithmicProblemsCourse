#include <iostream>
#include <string>
#include <sstream>

using namespace std;

bool debug = true;
string days[20] = {
    "IMIX",
    "IK",
    "AKBAL",
    "KAN",
    "Chikchan",
    "Kimi",
    "Manik",
    "Lamat",
    "Muluk",
    "Ok",
    "Chuen",
    "Eb",
    "Ben",
    "Ix",
    "Men",
    "Kib",
    "Kaban",
    "Etznab",
    "Kawak",
    "Ajaw"};
string months[19] = {
    "Pohp",
    "Wo",
    "Sip",
    "Zotz",
    "Sek",
    "Xul",
    "Yaxkin",
    "Mol",
    "Chen",
    "Yax",
    "Sak",
    "Keh",
    "Mak",
    "Kankin",
    "Muan",
    "Pax",
    "Kayab",
    "Kumku",
    "Wayeb"};


int main(int argc, char** argv){
    string input;
    // Calculate PPCM between 260 et 365
    int ppcm = 18980;
    
    cin >> input;
    cout << stoi(input.substr(0,2)) << endl;
    cout << input.substr(2) << endl;

    cin >> input;
    cout << stoi(input.substr(0,2)) << endl;
    cout << input.substr(2) << endl;

      
    return 0;
}
