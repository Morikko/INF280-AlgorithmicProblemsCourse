#include <iostream>
#include <string>
#include <sstream>

using namespace std;

bool debug = false;
string days[20] = {
    "Imix",
    "Ik",
    "Akbal",
    "Kan",
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
    "Ajaw"
};
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
    "Wayeb"
};

int kin = 0, winal = 0, tun = 0, katun = 0, baktun = 8;
int add_kin = 0, add_winal = 0, add_tun = 0, add_katun = 0, add_baktun = 0;

int calc_ppcm(int X, int Y);
void toCalendarRound(int val);
void addCalendarRound();

int main(int argc, char** argv){
    int cases;
    string input;
    // Calculate PPCM between 260 et 365
    int ppcm = calc_ppcm(260, 365);

    int t_day_cal1, t_day_cal2, t_ind_day, t_ind_month;

    // Get the entry
    cin >> cases;
    for(int j=0; j<cases ;j++){
        cin >> input;
        int pos = input.find(".");
        t_day_cal1 = stoi(input.substr(0,pos))-1;
        for(t_ind_day = 0; t_ind_day<20; t_ind_day++){
            if(days[t_ind_day].compare(input.substr(pos+1)) == 0)
                break;
        }

        cin >> input;
        pos = input.find(".");
        t_day_cal2 = stoi(input.substr(0,pos))-1;
        for(t_ind_month = 0; t_ind_month<19; t_ind_month++){
            if(months[t_ind_month].compare(input.substr(pos+1)) == 0)
                break;
        }

        if(debug)
            cout << "Target : day_cal1 = " << t_day_cal1 << " | ind_day = " << t_ind_day << " | day_cal2 = " << t_day_cal2 << " | ind_month = " << t_ind_month << endl;

        // Initial condition : 9.Ajaw 3.Sip
        int day_cal1 = 8, day_cal2 = 2, ind_day = 19, ind_month = 2;
        int i;
        // Search offset
        for(i=0; i <= ppcm; i++){
            // Comparaison
            if(t_day_cal1 == day_cal1 &&
                    t_day_cal2 == day_cal2 &&
                    t_ind_day == ind_day &&
                    t_ind_month == ind_month)
                break;
            // Add
            day_cal1++;
            day_cal2++;
            ind_day++;
            // Format
            day_cal1 = day_cal1%13;
            ind_day = ind_day%20;
            if(ind_month < 18){
                ind_month += day_cal2/20;
                day_cal2 = day_cal2%20;
                // Last month
            }else{
                if(day_cal2 == 5){
                    day_cal2 = 0;
                    ind_month =0;
                }
            }
        }

        if(debug)
            cout << "Offset : " << i << endl;

        if(i < ppcm){
            kin = 0, winal = 0, tun = 0, katun = 0, baktun = 8;
            add_kin = 0, add_winal = 0, add_tun = 0, add_katun = 0, add_baktun = 0;
            toCalendarRound(i);
            addCalendarRound();
            toCalendarRound(ppcm);
            while(baktun < 10){
                addCalendarRound();
            }
        }else{
            cout << "NO SOLUTION" << endl;
        }
        if(j<cases-1)
            cout << endl;
    }
    return 0;
}

// Change offset in calendar round dimension
void toCalendarRound(int val){
    add_baktun = val/144000;
    val = val%144000;
    add_katun = val/7200;
    val = val%7200;
    add_tun = val/360;
    val = val%360;
    add_winal = val/20;
    val = val%20;
    add_kin = val;
}

// Sum the offset in calendar round dimension
void addCalendarRound(){
    kin += add_kin;
    if(kin>=20){
        winal += kin/20;
        kin = kin%20;
    }
    winal += add_winal;
    if(winal>=18){
        tun += winal/18;
        winal =  winal%18;
    }
    tun += add_tun;
    if(tun>=20){
        katun += tun/20;
        tun = tun%20;
    }
    katun += add_katun;
    if(katun>=20){
        baktun += katun/20;
        katun = katun%20;
    }
    baktun += add_baktun;
    if(baktun < 10) 
        cout << baktun << "." << katun << "." << tun << "." << winal << "." << kin << endl;
}

// Find ppcm
// Source : http://codes-sources.commentcamarche.net/source/9638-ppcm-de-deux-nombres-tout-compilateur
int calc_ppcm(int X, int Y){
  int A=X;
  int B=Y;
  while (A!=B)
  {
    while (A>B) B=B+Y;
    while (A<B) A=A+X;
  }
  return A;
}
