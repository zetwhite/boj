#include <iostream>
#include <vector>
#define MAX 10000000000
#define MIN -10000000000
using namespace std;

void make_oper(int* numbers, int* oper, int res, long long& max, long long& min, int n, int count){
   if(count == n){
        if(max < res) max = res;
        if(min > res) min = res;
    }
    if(oper[0]){
        oper[0]--;
        make_oper(numbers, oper, res+numbers[count], max, min, n, count+1);
        oper[0]++;
    }
    if(oper[1]){
        oper[1]--;
        make_oper(numbers, oper, res-numbers[count], max, min, n, count+1);
        oper[1]++;
    }
    if(oper[2]){
        oper[2]--;
        make_oper(numbers, oper, res*numbers[count], max, min, n, count+1);
        oper[2]++;
    }
    if(oper[3]){
        oper[3]--;
        make_oper(numbers, oper, res/numbers[count], max, min, n, count+1);
        oper[3]++;

    }
}

int main(){
    int n;
    cin >> n;
    int* numbers = new int[n];
    for(int i = 0; i < n; i++)
        cin >> numbers[i];
    int oper[4];//+,-,*, /
    for(int i = 0; i < 4; i++)
        cin >> oper[i];

    long long max = MIN;
    long long min = MAX;
    make_oper(numbers, oper, numbers[0], max, min, n, 1);
    cout << max << endl;
    cout << min << endl;

    return 0;
}
