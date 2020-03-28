#include <bits/stdc++.h>
using namespace std;

long long gcd(long long a, long long b){
    if(a%b==0)
        return b;
    return gcd(b, a%b);
}

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

int main(){
    long long n, a;
    cin >> n >> a;

    long long plus_inverse = n - a;
    long long mult_inverse;

    if(gcd(n, a) != 1)
        mult_inverse = -1;
    else{
        pair<long long, long long> res = extend_euclid(n, a);
        long long tmp = res.second;
        while(tmp < 0)
            tmp += n;
        while(tmp > n)
            tmp -= n;
        mult_inverse = tmp;
    }
    cout << plus_inverse << " " << mult_inverse << endl;
    return 0;
}
