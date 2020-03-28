#include <bits/stdc++.h>
#define up_r right++;
#define up_l left++;
#define N 4000001

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
    for(int i = 2; i< N; i++){
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
    int sz = prime_list.size();
    delete []table;

    int left, right;
    int number;
    int sum;
    int count = 0;

    cin >> number;
    left = right = 0;

    sum = prime_list.at(left);
    if(number == 1){
        cout << 0 << endl;
        return 0;
    }
    while(prime_list.at(right) <= number && right < sz-1){;
        if(sum == number){
            count++;
            up_r;
            sum+= prime_list.at(right);
        }
        else if(sum < number){
            up_r;
            sum+= prime_list.at(right);
        }
        else if(sum > number && left < right){
            sum-= prime_list.at(left);
            up_l;
        }
        else{
            up_r; up_l;
            sum = prime_list.at(right);
        }
    }
    cout << count << endl;
    return 0;
}
