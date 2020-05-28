#include <iostream>
using namespace std; 

int main(){
    int num = 1; 
    while(1){
        int L, P, V; 
        cin >> L >> P >> V; 
        if( L==0 && P==0 & V==0 )
            break;
        int q = V/P;
        int r = V%P; 
        if(r > L) 
            r = L; 
        int res = q*L + r;
        cout << "Case " << num << ": " << res << endl; 
        num++; 
    }
    return 0;
}