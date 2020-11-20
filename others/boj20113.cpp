#include <iostream> 

using namespace std; 

int crew[102]; 

int main(){
    int n; 
    cin >> n;

    for(int i = 0; i <= n; i++){
        crew[i] = 0; 
    }

    int tmp; 
    for(int i = 0; i < n; i++){
        cin >> tmp; 
        crew[tmp]++; 
    }

    int max = 0; 
    int idx = 0; 
    bool dup = false; 
    for(int j = 1; j <= n; j++){
        if(max == crew[j]){
            dup = true; 
        }
        if(max < crew[j]){
            idx = j; 
            max = crew[j]; 
            dup = false; 
        }
    }

    if(dup)
        cout << "skipped"; 
    else
        cout << idx; 

    return 0; 
}