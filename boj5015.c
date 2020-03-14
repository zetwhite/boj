#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#define LEN 101

int cache [LEN][LEN];

void init_cache(){
    for(int i = 0; i < LEN; i++)
        memset(cache, -1, sizeof(cache));
}

bool match(char* p, char* s, int p_idx, int s_idx, int p_sz, int s_sz){
    if(p_idx == p_sz && s_idx == s_sz)
        return true;
    if(p_idx > p_sz || s_idx > s_sz)
        return false;
    int c = cache[p_idx][s_idx];
    if(c != -1)
        return c;
    if(p[p_idx] == '*'){
        while(s_idx <= s_sz){
            int tmp = match(p, s, p_idx+1, s_idx, p_sz, s_sz);
            cache[p_idx+1][s_idx] = tmp;
            s_idx++;
            if(tmp)
                return tmp;
        }
    }
    if(p[p_idx] == s[s_idx]){
        cache[p_idx][s_idx] = match(p, s, p_idx + 1, s_idx + 1, p_sz, s_sz);
        return cache[p_idx][s_idx];
    }
    if(p[p_idx] != s[s_idx])
        return false;
}

int main(){
    char p[LEN];
    scanf("%s", p);
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        char s[LEN];
        init_cache();
        scanf("%s", s);
        if(match(p, s, 0, 0, strlen(p), strlen(s)))
            printf("%s\n", s);
    }
    return 0;
}
