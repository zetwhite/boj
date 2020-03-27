#include <stdio.h>
#include <stdbool.h>
#define MAX 15000

bool possible[MAX + 1] = {0, };
int new_poss[MAX + 1] = {0, };

int main(){
    int n;
    scanf("%d", &n);
    int max = 0;
    int count = 0;
    for(int i = 0; i < n; i++){
        int tmp;
        scanf("%d", &tmp);

        int lmt = max;
        for(int j = 1; j <= lmt; j++){
            if(possible[j]){
                new_poss[count++] = tmp + j;
                if(j > tmp){
                    new_poss[count++] = j - tmp;
                }
                else if (j != tmp) {
                    new_poss[count++] = tmp - j;
                }
            }
         }

         for(int j = 0; j < count ; j++){
            possible[new_poss[j]] = 1;
         }
         count = 0;
         possible[tmp] = 1;
         max += tmp;
    }

    int m;
    scanf("%d", &m);
    for(int i = 0; i < m; i++){
        int in;
        scanf("%d", &in);
        if(in > MAX || !possible[in])
            printf("N ");
        else
            printf("Y ");
    }
    return 0;
}
