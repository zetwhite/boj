#include <iostream> 

using namespace std; 

int main(){
  int A, B, C, X, Y; 
  cin >> A >> B >> C >> X >> Y; 
  
  if(A >= C*2)
    A = C*2; 
  if(B >= C*2)
    B = C*2; 

  if(A + B <= C*2){
    cout << A*X + B*Y;  
  }
  else{
    int mix = min(X, Y);
    cout << C*mix*2 + A*(X - mix) + B*(Y - mix); 
  }
  return 0; 
}