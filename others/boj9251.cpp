#include <iostream> 

using namespace std; 

int main(){
    string str1, str2; 
    cin >> str1 >> str2; 

    str1 = "0" + str1; 
    str2 = "0" + str2; 

    int len1 = str1.length(); 
    int len2 = str2.length(); 
    int dp[len1][len2] ; //??new grammer? 

    for(int i = 0; i < len2; i++){
        dp[0][i] = 0; 
    }
    for(int i = 1; i < len1; i++){
        dp[i][0] = 0; 
        for(int j = 1; j < len2; j++){
            if(str1[i] == str2[j]){
                dp[i][j] = dp[i-1][j-1] + 1; 
            }
            else{
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]); 
            }
        }
    }
    cout << dp[len1-1][len2-1] << endl; 
    return 0; 
}