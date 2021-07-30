#include <iostream> 
#include <cmath>

using namespace std; 

double x, y, c; 

double guessC(double t){
  double h_x = sqrt(x*x - t*t); 
  double h_y = sqrt(y*y - t*t); 
  double h = h_x + h_y; 
  double c = h_x * h_y / (h_x + h_y); 
  return c; 
}

double binarySearch(double min, double max){
  double mid = (min + max) / 2; 
  if( min + 0.00001 > max){
    return mid;  
  }
  double gc = guessC(mid);
  if( gc ==  c)
    return mid; 
  else if (gc > c)
    return binarySearch(mid, max); 
  else
    return binarySearch(min, mid); 
}

int main(){
  cin >> x >> y >> c; 

  double max = min(x, y); 
  double min = 0.00001; 
  cout << round(binarySearch(min, max)*1000)/1000 << endl; 
  return 0; 
}


