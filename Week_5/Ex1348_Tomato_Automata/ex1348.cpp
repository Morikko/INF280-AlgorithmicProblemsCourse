#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>

using namespace std;

bool debug = false;
enum command {DIE, IFGO, LOOP, PASS, JUMP};
void parse(string & temp,vector<command> & commands, vector<int> & param_1,vector<int> & param_2);
bool look_infinite(int index, vector<command> & commands, vector<int> & param_1);

int main(int argc, char** argv){
    string temp;

    while(getline(cin, temp)){
        bool infinity = false;
        vector<command> commands;
        vector<int>     param_1, param_2, param_2_save; 

        do{
            parse(temp, commands, param_1, param_2);
            getline(cin, temp);
        }while(temp.size()>1);
        param_2_save = param_2;

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
        int inst_pt = 0;
        int count = 0;
        bool run = true;
        
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = chrono::system_clock::now();
        chrono::duration<double> elapsed;

        while(run){
            end = chrono::system_clock::now();
            elapsed = end - start;
            // Too long, we are in a loop
            if(elapsed.count()>0.01){
                cout << "infinity" << endl;
                break;
            }
            
            count++;
            switch(commands[inst_pt]){
                case DIE:
                    run = false;
                    break;
                case JUMP:
                    inst_pt = param_1[inst_pt];
                    break;
                case IFGO:
                    if( param_1[param_1[inst_pt]] > 0 )
                        inst_pt = param_1[inst_pt];
                    else
                        inst_pt++;
                    break;
                case LOOP:
                    if( param_2[inst_pt]-1 > 0){
                        param_2[inst_pt]--;
                        inst_pt = param_1[inst_pt];
                    }else{
                        // Reset loop counter
                        param_2[inst_pt] = param_2_save[inst_pt];
                        inst_pt++;
                    }
                    break;
                default:
                    inst_pt++;
            }
            inst_pt %= commands.size();
        }
       if(elapsed.count()<=0.01)
            cout << count << endl;
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
        param_1.push_back(i-1);
        param_2.push_back(0);
    }else if(!s.compare("jump")){
        commands.push_back(JUMP);
        int i;
        ss >> i;
        param_1.push_back(i-1);
        param_2.push_back(0);
    }else if(!s.compare("die")){
        commands.push_back(DIE);
        param_1.push_back(0);
        param_2.push_back(0);
    }else if(!s.compare("loop")){
        commands.push_back(LOOP);
        int i;
        ss >> i;
        param_1.push_back(i-1);
        int ii;
        ss >> ii;
        param_2.push_back(ii);
    }else{
        commands.push_back(PASS);   
        param_1.push_back(0);
        param_2.push_back(0);
    }
}

bool look_infinite(int index, vector<command> & commands, vector<int> & param_1){
    int i = index;
    while(i >= 0){
        if(commands[i] == IFGO && param_1[i] > index && param_1[param_1[i]] > 0)
           return false;
        if(commands[i] == JUMP && param_1[i] > index)
            return false;
        i--;
    }
    return true;
}
