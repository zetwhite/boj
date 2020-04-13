#include <iostream>
#include <string>
using namespace std;

int n;
int* time;
int* pay;

string multi(int count){
    string taps = " ";
    for(int i = 0; i < count; i++){
        taps += taps;
    }
    return taps;
}

int getMax(int pick, int sum, int count){
    //cout <<multi(count);
    //cout << "getMax (pick= " << pick <<", sum =" << sum <<")" << endl;
    int n_sum = sum;
    if(pick >= n){
        //cout <<multi(count);
        //cout << "end return" << n_sum << endl;
        return n_sum;
    }
    int tmp1 = 0, tmp2 =0;
    if(pick + time[pick] <= n)
        tmp1 = getMax(pick+time[pick], sum+pay[pick], count+1);
    tmp2 = getMax(pick+1, sum, count+1);
    if(tmp1 > tmp2)
        n_sum = tmp1;
    else
        n_sum = tmp2;
    return n_sum;
}

int main(){
    cin >> n;
    time = new int[n];
    pay = new int[n];
    for(int i = 0; i < n; i++){
        cin >> time[i];
        cin >> pay[i];
    }
    cout << getMax(0, 0, 0) << endl;
    delete[] time;
    delete[] pay;
    return 0;
}
