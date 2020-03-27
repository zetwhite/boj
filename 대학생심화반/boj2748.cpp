#include <bits/stdc++.h>
#define N 91

using namespace std;


int main(){
    long long fibo[N];
    fibo[0] = 0;
    fibo[1] = 1;

    for(int i = 2; i < N; i++)
        fibo[i] = fibo[i-1] + fibo [i-2];

    int n;
    cin >> n;
    cout << fibo[n] <<endl;

    return 0;
}
