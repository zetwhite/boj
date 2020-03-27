#include <stdio.h>
#define MOD 1000000000

void add_arr(long long* result, long long* tmp){
    for(int i = 0; i < 10; i++){
        result[i] = tmp[i]%MOD;
        tmp[i] = 0;
    }
}

int main(){
    int n;
    scanf("%d", &n);
    long long result[10];
    long long tmp[10];

    result[0] = 0;
    for(int i = 1; i < 10; i++)
        result[i] = 1;
    for(int i = 0; i < 10; i++)
        tmp[i] = 0;

    for(int i = 2; i <= n; i++){
        for(int j = 0; j < 10; j++){
            if(j == 0)
                tmp[1] += result[0];
            else if(j == 9)
                tmp[8] += result[9];
            else{
                tmp[j-1] += result[j];
                tmp[j+1] += result[j];
            }
        }
        add_arr(result, tmp);
    }
    long long res = 0;
    for(int i = 0; i < 10; i++)
        res += result[i]%MOD;
    printf("%lld\n", res%MOD);
}
