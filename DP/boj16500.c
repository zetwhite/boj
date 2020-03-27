#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <memory.h>

char s[100];
char a_set[100][100];
int dp[100][100];
bool not_possible[100] = {0, };

bool match(int s_pos, int n){
    if(s[s_pos] == '\0')
        return true;
    if(s_pos > strlen(s))
        return false;
    for(int i = 0; i < n; i++){
        if(dp[s_pos][i] != -1){
            if(dp[s_pos][i]){
                if(not_possible[s_pos + strlen(a_set[i])] == false && match(s_pos + strlen(a_set[i]), n))
                    return true;
                else
                    not_possible[s_pos + strlen(a_set[i])] = true;
            }
            else
                continue;
        }
        else if(strncmp(s+s_pos, a_set[i], strlen(a_set[i])) == 0){
            dp[s_pos][i] = 1;
            if (not_possible[s_pos + strlen(a_set[i])] == false && match(s_pos + strlen(a_set[i]), n) )
                return true;
            else
                not_possible[s_pos + strlen(a_set[i])] = true;
        }
        else
            dp[s_pos][i] = 0;
    }
    return false;
}

int main(){
    scanf("%s", s);
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%s", a_set[i]);

    for(int i = 0; i < 100; i++)
        memset(dp+i, -1, sizeof(int)*100);
    if(match(0, n))
        printf("1\n");
    else
        printf("0\n");
    return 0;
}
