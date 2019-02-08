#include "string_matching.h"

int string_matching_naive(char *text, int N, char* pattern, int M){
    int count = 0;
    int pos_pattern = 0;
    for (int i = 0; i<N; i++){ // fix N

        if (text[i] == pattern[pos_pattern]){
            pos_pattern++;
            if (pos_pattern == (M)){
                pos_pattern = 0;
                count++;
            }
        } else {
            i-=pos_pattern;
            pos_pattern = 0;
        }
    }
    return count;
}
