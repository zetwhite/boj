#include <bits/stdc++.h>
#define m 1000000007
using namespace std;

pair<long long, long long> extend_euclid(long long a, long long b){
    if(b == 1){
        return make_pair(0ll, 1ll);
    }
    long long q = -1*a/b;
    long long r = a%b;
    if(r == 1){
        return make_pair(1ll, q);
    }
    pair<long long, long long> res = extend_euclid(b, r);
    return make_pair(res.second, res.second*q + res.first);
}

long long get_inverse(long long num, long long mod){
    long long inverse = extend_euclid(mod, num%mod).second;
    while(inverse < 0) inverse+=mod;
    while(inverse > mod) inverse-=mod;
    return inverse;
}

int main(){
    long long n, k;
    cin >> n >> k;

    long long res = 1;
    for(long long i = n; i >= n-k+1; i--){
        res = (res*(i%m))%m;
    }
    for(long long i = k; i >=1; i--)
        res = (res*get_inverse(i, m))%m;
    cout << res << endl;
    return 0;
}
