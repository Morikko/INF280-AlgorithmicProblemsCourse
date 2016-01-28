#include <iostream>
#include <climits>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <stdio.h>
#include <string.h>

/***
 * 1.Start from the end: when going back to beginning bring the ending one
 */

#define NWORDS_MAX 10000
#define LENGTH_MAX 1002

using namespace std;

char str[LENGTH_MAX];
char *dict[NWORDS_MAX];

const char* morse[26] = {".-",
            "-...",
            "-.-.",
            "-..",
            ".",
            "..-.",
            "--.",
            "....",
            "..",
            ".---",
            "-.-",
            ".-..",
            "--",
            "-.",
            "---",
            ".--.",
            "--.-",
            ".-.",
            "...",
            "-",
            "..-",
            "...-",
            ".--",
            "-..-",
            "--.-",
            "--.." };

int startswith(int pos, int w) {
    for ( unsigned int i = 0; i < strlen(dict[w]); i++) {
        if (dict[w][i] == '\n')
            break;
        int l = dict[w][i] - 'A';
        for ( unsigned int j = 0; j < strlen(morse[l]); j++) {
            if (str[pos] != morse[l][j])
                return -1;
            pos++;
        }
    }
    return pos;
}

int main(int argc, char** argv){
    int ncases, nwords, length;
    scanf("%d", &ncases);
    for ( int ncase = 0; ncase < ncases; ncase++) {
        scanf("%s", str);
        length = strlen(str);
        scanf("%d", &nwords);
        getchar();
        for( int i = 0; i < nwords; i++) {
            size_t size = 0;
            getline(&(dict[i]), &size, stdin);
        }
        long nposs[LENGTH_MAX];
        nposs[length] = 1;

        for ( int pos = length-1; pos >= 0; pos--) {
            nposs[pos] = 0;
            for ( int i = 0; i < nwords; i++ ) {
                int pos2;
                if ((pos2 = startswith(pos, i)) > 0)
                    nposs[pos] += nposs[pos2];
            }
        }
        printf("%s%ld\n", ncase ? "\n" : "", nposs[0]);
    }

    return 0;
}
