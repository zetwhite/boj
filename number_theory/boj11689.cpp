#include <iostream>
#include <vector>
#define MAX 1000000000
#define ll long long
using namespace std;

ll euler_phi(ll n){
    ll res = n;
    ll prime = 2;
    while(prime * prime <= n){
        if(n%prime == 0)
            res = res/prime*(prime -1);
        while(n % prime == 0)
            n = n/prime;
        prime++;
    }
    if(n != 1)
        res = res/n*(n-1);
    return res;
}

int main(){
    ll n;
    cin >> n;
    cout << euler_phi(n) << endl;
    return 0;
}
