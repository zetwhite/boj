#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    long long end_0 = 0;
    long long end_1 = 1;
    for(int i = 2; i <=n; i++){
        long long tmp_0 = end_0 + end_1;
        long long tmp_1 = end_0;
        end_0 = tmp_0;
        end_1 = tmp_1;
    }
    printf("%lld\n", end_0 + end_1);
}
