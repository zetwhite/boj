#include <stdio.h>

void swap(int* a, int*b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int gcd(int a, int b){
    if(a<b) swap(&a, &b);
    if(!(a%b)) return b;
    return gcd(b, a-b);
}

int main(){
    int a_ch, a_pa, b_ch, b_pa;
    scanf("%d%d%d%d", &a_ch, &a_pa, &b_ch, &b_pa);

    a_ch *= b_pa;
    b_ch *= a_pa;

    int child = a_ch + b_ch;
    int parent = a_pa*b_pa;
    int div = gcd(parent, child);
    printf("%d %d", child/div, parent/div);
    return 0;
}
