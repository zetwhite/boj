#include <string>
#include <vector>
#include <iostream> 

using namespace std;

string solution(string number, int k) {
    string answer = "";
    int cnt = 0; 
    for(int i = 0; i < number.size()-1; i++){
        if(cnt < k && number[i] < number[i+1]){
            number.erase(i, 1); 
            cnt++;
            if(i >= 1){
                i = i - 2; 
            }
            else
                i--;  
        }
    }

    if(cnt < k){
        int left = k - cnt;
        int size = number.size(); 
        number.erase(size-left, left); 
    }
    return number; 
}
