#include <iostream> 
#include <cmath>
using namespace std; 

class Vector3d{
public : 
  double x; 
  double y; 
  double z; 

  double getSum(){
    return x + y + z; 
  }
  double getSize(){
    return x*x + y*y + z*z; 
  }

  Vector3d(double _x, double _y, double _z){
    x = _x; 
    y = _y; 
    z = _z; 
  }
  Vector3d(){}
}; 

Vector3d A, B, C; 
istream& operator >> (istream& is, Vector3d& v){
  is >> v.x >> v.y >> v.z;
  return is; 
}

ostream& operator << (ostream& os, Vector3d& v){
  os << "(" << v.x << ", " << v.y << ","  << v.z << ")"; 
  return os; 
}


Vector3d operator- (const Vector3d& a, const Vector3d& b){ 
  return Vector3d(a.x - b.x, a.y - b.y, a.z - b.z); 
}

Vector3d operator+ (const Vector3d& a, const Vector3d& b){ 
  return Vector3d(a.x + b.x, a.y + b.y, a.z + b.z); 
}

Vector3d operator* (const Vector3d& a, const Vector3d& b){
  return Vector3d(a.x * b.x, a.y * b.y, a.z * b.z); 
}


int main(){
  cin >> A >> B >> C; 
  Vector3d Line = B - A; 
  //cout << "Line = " <<Line << endl; 
  double t = (Line * (C-A)).getSum() / Line.getSize(); 
  //cout <<t << endl; 

  Vector3d H = A + Vector3d(Line.x *t, Line.y*t , Line.z*t); 
  //cout << "H is " << H << endl; 
  Vector3d AH = H-A; 
  Vector3d BH = H-B; 
  Vector3d ABH = AH * BH;  
  if(ABH.x > 0 || ABH.y > 0 || ABH.z > 0){
    if(AH.getSize() < BH.getSize())
      H = A; 
    else 
      H = B;
  }

  cout<<fixed;
  cout.precision(8);
  cout << sqrt((C-H).getSize()) << endl; 
  return 0; 
}