#include <iostream> 

using namespace std; 

char arr[101][101]; 
int main(){ 
    int n; 
    cin >> n; 

    for(int i = 0; i < n; i++){
        string str; 
        cin >> str; 
        for(int j = 0; j < n; j++){            
            arr[i][j] = str[j]; 
        }
    }

    bool success = true; 
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= i; j++){
            //cout << "i = " << i << ", j = " << j << endl; 
            if(arr[i][j] != arr[j][i]){
                success = false; 
                break; 
            }
        }
        if(success == false)
            break; 
    }

    if(success)
        cout << "YES"; 
    else 
        cout << "NO"; 
    return 0; 
}