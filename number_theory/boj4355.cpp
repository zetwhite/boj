#include <iostream>
#include <vector>
#define MAX 1000000000
using namespace std;

int euler_phi(int n){
    int res = 1;
    int factor = 1;
    int old_n = n;
    int max = n/2 + 1;
    for(int k = 2; k <= max; k++){
        if(n%k == 0){
            factor *= k;
            n /= k;
            k--;
            continue;
        }
        if(factor == 1)
            continue;
        res *= (factor/k)*(k-1);
        factor = 1;
        if(n == 1)
            break;
    }
    if(res == 1)
        res = old_n - 1;
    return res;
}


int main(){

    while(true){
        int n;
        cin >> n;
        if(n == 0) break;
        cout << euler_phi(n) << endl;
    }
    return 0;
}
