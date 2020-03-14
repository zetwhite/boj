#include <stdio.h>
#include <stdlib.h>

int max_2(int a, int b){
    if(a > b)
        return a;
    return b;
}

int max_3(int a, int b, int c){
    int tmp = a > b ? a : b;
    tmp = c > tmp ? c : tmp;
    return tmp;
}

int main(){
    int t;
    scanf("%d", &t);

    for(int i = 0; i < t; i++){
        int n;
        scanf("%d", &n);
        int* line1 = (int*) malloc(sizeof(int)*(n+1));
        int* line2 = (int*) malloc(sizeof(int)*(n+1));
        for(int j = 1; j <= n; j++)
            scanf("%d", line1+j);
        for(int j = 1; j <= n; j++)
            scanf("%d", line2+j);

        line1[2] += line2[1];
        line2[2] += line1[1];
        for(int j = 3; j <= n; j++){
            line1[j] += max_3(line1[j-2], line2[j-2], line2[j-1]);
            line2[j] += max_3(line1[j-2], line1[j-1], line2[j-2]);
        }
        printf("%d\n", max_2(line1[n], line2[n]));
        free(line1);
        free(line2);
    }
}
