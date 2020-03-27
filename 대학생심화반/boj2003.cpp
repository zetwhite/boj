#include <bits/stdc++.h>
#define s_add add_s(&sum,&s,n_arr[s])
#define t_add add_t(&sum,&t,n_arr[t+1])
using namespace std;

inline void add_s(long long *sum, int *s, int _s){
    *sum -= _s;
    (*s)++;
}

inline void add_t(long long *sum, int *t, int _t){
    *sum += _t;
    (*t)++;
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    long long m;
    int s = 0;
    int t = 0;
    long long sum = 0;
    int result = 0;

    cin >> n >> m;
    int* n_arr = new int[n];
    for(int i = 0; i < n; i++){
        cin >> n_arr[i];
    }

    sum = n_arr[0];
    while(1){
        if(t == n )
            break;
        if(sum > m){
            if(s == t){
                s_add; t_add;
            }
            else if(s < t)
                s_add;
            else{
                s_add; t_add;
            }
        }
        else if( sum < m ){
            t_add;
        }
        else{
            result ++;
            if(s == t){
                s_add; t_add;
            }
            else
                t_add;
        }
    }

    cout << result << endl;

    delete [] n_arr;
    return 0;
}
