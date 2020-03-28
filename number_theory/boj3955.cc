#include <bits/stdc++.h>
using namespace std;
#define lmt 1000000000

long long gcd(long long a, long long b){
    long long tmp;
    while(tmp = a%b){
        a = b;
        b = tmp;
    }
    return b;
}

pair<long long, long long> extend_euclid(long long a, long long b){
    long long q = -1*a/b;
    long long r = a%b;
    if(a%b == 0){
      //  printf("return 0, 0\n");
        return make_pair(0ll, 0ll);
    }
    pair<long long, long long> res = extend_euclid(b, r);
    if(res.first == 0 && res.second == 0){
      //  printf("return 1, %lld\n", q);
        return make_pair(1ll, q);
    }
    //printf("return %lld, %lld\n", res.second, res.second*q + res.first);
    return make_pair(res.second, res.second*q + res.first);
}

int main(){
    int t;
    scanf("%d", &t);

    for(int i = 0; i < t; i++){
        long long k, c;
        scanf("%lld %lld", &k, &c);
        long long g = gcd(k, c);
        if(g != 1)
            printf("IMPOSSIBLE\n");
        else if(c==1){
            if(k!= lmt) printf("%lld\n", k+1);
            else printf("IMPOSSIBLE\n");
        }
        else if(k == 1){
            printf("%lld\n", lmt/c);
        }
        else{
            pair<long long, long long> res = extend_euclid(k, c);
            while(res.second < 0){
                res.second += k;
            }
            while(res.second > lmt){
                res.second -= k;
            }
            long long x = (c*res.second - 1)/k;
            if(x <= 0)
                printf("IMPOSSIBLE\n");
            else
                printf("%lld\n", res.second);
        }
    }
}
