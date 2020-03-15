#include <stdio.h>
#define MOD 10007

void update(int* result, int* tmp, int which){
    for(int k = which; k < 10; k++){
        tmp[k] += result[which];
    }
}

void mov(int* src, int* dest){
    for(int k = 0; k < 10; k++){
        dest[k] = src[k]%MOD;
        src[k] = 0;
    }
}

int main(){
    int result[10];
    int tmp[10];

    int n;
    scanf("%d", &n);
    for(int i = 0; i < 10; i++)
        result[i] = 1;
    for(int i = 0; i < 10; i++)
        tmp[i] = 0;

    for(int i = 2; i <= n; i++){
        for(int j = 0; j < 10; j++){
            update(result, tmp, j);
        }
        mov(tmp, result);
    }

    int res = 0;
    for(int i = 0; i < 10; i++)
        res += result[i]%MOD;
    printf("%d\n", res%MOD);
    return 0;
}
