#include <iostream> 

using namespace std; 

int main(){
  long long N, K; 
  cin >> N >> K; 
  int min_number = 0; 
  int max_number = 10; 
  int min_idx = 0; 
  int max_idx = 11; 
  int unit = 10; 

  int number = 0; 
  while(1){
    if(K <= max_idx){
      //cout << "K is between ( " << min_number << ", " << max_number << ")" << endl; 
      number = min_number; 
      K -= min_idx; 

      number += 10 * (K/unit); 
      K = K%unit; 

      /*
      cout << "number = " << number << endl; 
      cout << "K = " << K << endl; 
      cout << "space = " << unit/10 << endl; 
      */

      int space = unit / 10; 
      number += K / (space); 
      int left = K % (space); 
      if(left == 0){
      //cout << "final number  =" << number << endl; 
        if(number > N) 
          cout << -1 << endl;
        else
          cout << to_string(number)[space - 1] << endl; 
      }
      else{
        //cout << "final number  =" << number+ 1<< endl; 
        if(number+1 > N) 
          cout << -1 << endl;
        else
          cout << to_string(number+1)[left-1] << endl; 
      } 
      break; 
    }

    min_number = max_number;  
    max_number = max_number * 10; 
    unit = unit + 10; 
    min_idx = max_idx; 
    max_idx = max_idx + (unit * (max_number * 0.09)) + 1; 
  }

  return 0; 
}