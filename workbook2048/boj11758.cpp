#include <bits/stdc++.h>
using namespace std;
#define INTP pair<int, int>

int main(){
    INTP p[3];
    for(int i = 0; i < 3; i++){
        cin >> p[i].first;
        cin >> p[i].second;
    }

    INTP l[2];
    for(int i =0; i<2; i++){
        l[i].first = p[i+1].first - p[i].first;
        l[i].second = p[i+1].second - p[i].second;
    }

    int res = l[0].first*l[1].second - l[1].first*l[0].second;
    if(res > 0)
        cout << "1\n";
    else if( res < 0 )
        cout << "-1\n";
    else
        cout << "0\n";

    return 0;
}
