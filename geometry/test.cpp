#include <bits/stdc++.h>
#include <iostream>
using namespace std; 
typedef pair<double, double> coo; 
const int ZERO = 500; 
const int NUL = 2000; 

vector<int> xz_z; 
vector<int> yz_z; 
double xz_planes[1002][2]; 
double yz_planes[1002][2]; 

void fillPlane(bool xz, double x, int z){
    double(*planes)[2]; 
    if(xz)
        planes = xz_planes; 
    else
        planes = yz_planes; 

    if(planes[z][0] == NUL)
        planes[z][0] = x; 
    else if(planes[z][1] == NUL){
        if(planes[z][0] > x){
            planes[z][1] = planes[z][0];
            planes[z][0] = x; 
        }
        else
            planes[z][1] = x; 
    }
    else{
        if(x < planes[z][0])
            planes[z][0] = x; 
        else if(x > planes[z][1])
            planes[z][1] = x; 
    }
}


void fillMidValue(bool xz, int x1, int z1, int x2, int z2){
    if(z1 == z2)
        return; 
    if(z1 > z2){
        swap(z1, z2); 
        swap(x1, x2); 
    }
    double slope = static_cast<double>(x2-x1) / static_cast<double>(z2-z1); 
    for(int i = z1 + 1; i < z2; i++){
        double value = slope * (i - z1) + x1; 
        fillPlane(xz, value, i); 
    }
}

void fillPoly(bool xz){
    vector<int>* store = &xz_z; 
    if(xz == false)
        store = &yz_z; 

    int n, start_x, start_z; 
    cin >> n >> start_x >> start_z; 
    start_z = start_z + ZERO; 
    int old_x = start_x; 
    int old_z = start_z; 
    store->push_back(start_z); 
    fillPlane(xz, start_x, start_z); 
    int x, z; 
    for(int i = 1; i < n; i++){
        cin >> x >> z; 
        z = z + ZERO; 
        store->push_back(z); 
        fillPlane(xz, x, z); 
        fillMidValue(xz, x, z, old_x, old_z);
        old_x = x; 
        old_z = z; 
    }
    fillMidValue(xz, start_x, start_z, old_x, old_z); 
    sort(store->begin(), store->end()); 
}

double getLength(bool xz, int z){
    double (*plane)[2]; 
    if(xz)
        plane = xz_planes; 
    else 
        plane = yz_planes; 
    if(plane[z][0] == NUL || plane[z][1] == NUL)
        return 0; 
    else 
        return plane[z][1] - plane[z][0]; 
}

double getSegment(double k, double a, double b, double c, double d){
    double first = 1/3.00 * (b-a) * (d-c) * k; 
    double second = 1/2.00 * ((b-a)*c + (d-c)*a) * k; 
    double third = a*c*k; 
    return abs(first + second + third); 
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(5) << fixed; 
    for(int i = 0; i < 1002; i++){
        xz_planes[i][0] = NUL; 
        xz_planes[i][1] = NUL; 
        yz_planes[i][0] = NUL; 
        yz_planes[i][1] = NUL; 
    }
    fillPoly(true);
    fillPoly(false);  
    
    double result = 0; 
    int go = xz_z[0]; 
    int end = xz_z[xz_z.size()-1]; 
    int x_idx = 1; 
    int y_idx = 1; 
    int next_go = 0; 
    while(go < end){
        while(xz_z[x_idx] == go)
            x_idx++; 
        while(yz_z[y_idx] == go)
            y_idx++; 
        next_go = min(xz_z[x_idx], yz_z[y_idx]); 
        double a = getLength(true, go); 
        double b = getLength(true, next_go); 
        double c = getLength(false, go); 
        double d = getLength(false, next_go); 
        result += getSegment(next_go - go, a, b, c, d); 
        go = next_go; 
    }
    cout << result << endl; 
    return 0; 
}