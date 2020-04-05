#include <iostream>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    int* people = new int[n];
    for(int i = 0; i < n; i++)
        cin >> people[i];
    int b, c;
    cin >> b >> c;

    long long count = 0;
    for(int i = 0; i < n; i++){
        people[i]-=b;
        count++;
        if(people[i]>0){
            int p = people[i]/c;
            count += p;
            int r = people[i]%c;
            if(r > 0)
                count++;
        }
    }
    cout << count << endl;
}
