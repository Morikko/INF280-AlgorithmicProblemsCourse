#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

bool debug = true;
enum command {DIE, IFGO, LOOP, PASS, JUMP};
void parse(string & temp,vector<command> & commands, vector<int> & param_1,vector<int> & param_2);

int main(int argc, char** argv){
    string temp;

    while(getline(cin, temp)){
        vector<command> commands;
        vector<int>     param_1, param_2; 

        do{
            parse(temp, commands, param_1, param_2);
            getline(cin, temp);
        }while(temp.size()>1);

        if(debug){
            cout << "CODE" << endl;
            for(int s=0; s<commands.size(); s++){
                switch(commands[s]){
                    case DIE:
                        cout << "DIE";
                        break;
                    case IFGO:
                        cout << "IFGO";
                        break;
                    case LOOP:
                        cout << "LOOP";
                        break;
                    case JUMP:
                        cout << "JUMP";
                        break;
                    default:
                        cout << "PASS";
                }
                if(commands[s] == IFGO || commands[s] == JUMP)
                    cout << " " << param_1[s];
                if(commands[s] == LOOP)
                    cout << " " << param_1[s] << " " << param_2[s];
                cout << endl;
            }
            cout << endl;
        }

        /* Execute tomato code */



    } 
    return 0;
}

void parse(string & temp,vector<command> & commands, vector<int> & param_1,vector<int> & param_2){
    stringstream ss(temp);
    string s;
    ss >> s;
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    if(!s.compare("ifgo")){
        commands.push_back(IFGO);
        int i;
        ss >> i;
        param_1.push_back(i);
        param_2.push_back(0);
    }else if(!s.compare("jump")){
        commands.push_back(JUMP);
        int i;
        ss >> i;
        param_1.push_back(i);
        param_2.push_back(0);
    }else if(!s.compare("die")){
        commands.push_back(DIE);
        param_1.push_back(0);
        param_2.push_back(0);
    }else if(!s.compare("loop")){
        commands.push_back(LOOP);
        int i;
        ss >> i;
        param_1.push_back(i);
        int ii;
        ss >> ii;
        param_2.push_back(ii);
    }else{
        commands.push_back(PASS);   
        param_1.push_back(0);
        param_2.push_back(0);
    }
}

