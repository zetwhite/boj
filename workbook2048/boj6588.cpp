#include <bits/stdc++.h>
#define N 1000001

using namespace std;

bool* table;

void check_prime(bool* table){
    memset(table, 1, N);
    table[0] = false;
    table[1] = false;
    for(int i = 2; i < N; i++){
        if(table[i]){
            int j = i + i;
            while(j < N){
                table[j] = 0;
                j += i;
            }
        }
    }
}

void make_prime_list(vector<int>& l, bool* arr){
    for(int i = 2; i*2< N; i++){
        if(arr[i]){
            l.push_back(i);
        }
    }
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    table = new bool[N];
    vector<int> prime_list;

    check_prime(table);
    make_prime_list(prime_list, table);

    int n;
    int size = prime_list.size();
    cin >> n;
    while(n){
        int i = 0;
        int a = 0;
        for(i = 0; i < size; i++){
            a = prime_list.at(i);
            if(table[n-a])
                break;
        }
        if(i==size)
            cout << "Goldbach's conjecture is wrong.\n";
        else
            cout << n << " = " << a << " + " << n-a << "\n";
        cin >> n;
    }

    return 0;
}
