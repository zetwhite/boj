#include <stdio.h>
#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX 1000000
#define INT(c) (c-'0')

void check_prime(bool* table, int sz){
    memset(table, 1, sz);
    table[0] = table[1] = false;
    for(int i = 2; i < sz; i++){
        if(table[i]){
            int j = i+i;
            while(j < sz){
                table[j] = 0;
                j += i;
            }
        }
    }
}

int string_mod(char* s, int divider){
    //a = b*c
    //a mod t = ((b mod t)*c) mod t
    int len = strlen(s);
    int res = 0;
    for(int i = 0; i < len; i++){
        int tmp = INT(s[i]) % divider;
        res = ((res * 10) + tmp) % divider;
    }
    return res;
}

int main(){
    char p[100];
    int k;
    scanf("%s %d", p, &k);

    bool* table = (bool*)malloc(sizeof(bool)*(k+1));
    check_prime(table, k+1);
    int i=k;
    for(i = 2; i<k; i++){
        if(table[i] && !(string_mod(p, i)))
            break;
    }
    if(i == k)
        printf("GOOD\n");
    else
        printf("BAD %d\n", i);
    return 0;
}
