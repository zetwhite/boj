#include <iostream>
#include <vector> 

using namespace std; 

int is_lower(vector<int>& LIS, int start, int end, int value){
    if(start >= end)
        return start;
    int mid = (start + end) /2 ; 
    if( value <= LIS[mid] )
        return is_lower(LIS, start, mid, value); 
    else 
        return is_lower(LIS, mid+1, end, value); 
}

int main(){
    int n; 
    cin >> n; 
    int* numbers = new int[n]; 
    int* indexs = new int[n]; 
    vector<int> LIS;
    for(int i = 0; i < n; i++)
        cin >> numbers[i]; 
    LIS.push_back(numbers[0]);
    indexs[0] = 0; 

    for(int i = 1; i < n; i++){
        if(numbers[i] > LIS[LIS.size()-1]){
            LIS.push_back(numbers[i]); 
            indexs[i] = LIS.size() - 1; 
        }
        else{
            int replace_idx = is_lower(LIS, 0, LIS.size()-1, numbers[i]);
            LIS[replace_idx] = numbers[i]; 
            indexs[i] = replace_idx; 
        }
    }

    int sz = LIS.size(); 
    cout << sz << endl; 
    int check = 0; 
    for(int i = 0; i < n; i++){
        if(indexs[i] == check){
            cout << numbers[i] << " "; 
            check++; 
        }
        if(check >= sz)
            break; 
    }
    return 0; 
}