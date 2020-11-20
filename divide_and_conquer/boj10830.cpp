#include <iostream> 
#include <vector> 
using namespace std; 

class Matrix{
public :
    int size; 
    int** data;  
    Matrix(int n)
    :size(n){
        data = new int*[n]; 
        for(int i = 0; i < n; i++){
            data[i] = new int[n]; 
        }
    }

    Matrix(const Matrix& m){
        size = m.size; 
        data = new int*[size]; 
        for(int i = 0; i < size; i++)
            data[i] = new int[size]; 
    }

    Matrix& operator= (const Matrix& other){
        size = other.size; 
        data = new int*[size]; 
        for(int i = 0; i < size; i++){
            data[i] = new int[size]; 
        }
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                data[i][j] = other.data[i][j]; 
            }
        }
        return *this; 
    }

    ~Matrix(){
        for(int i = 0; i < size; i++)
            delete[] data[i]; 
        delete[] data; 
    }
}; 

Matrix operator* (Matrix& lhs, Matrix& rhs){
    Matrix result(lhs.size);
    for(int i = 0; i < lhs.size; i++){
        for(int j = 0; j < lhs.size; j++){
            result.data[i][j] = 0; 
            for(int k = 0; k < lhs.size; k++){
                result.data[i][j] += lhs.data[i][k] * rhs.data[k][j]; 
                result.data[i][j] %= 1000; 
            }
        }
    }
    return result; 
}

ostream& operator<< (ostream& os, const Matrix& m){
    for(int i = 0; i < m.size; i++){
        for(int j = 0 ; j < m.size; j++){
            os << m.data[i][j] << " "; 
        }
        os << "\n"; 
    }
    return os; 
}

int getBitLength(long long n){
    int size = 0; 
    while(n != 0){
        n = n / 2; 
        size++; 
    }
    return size; 
}

int main(){
    int N; 
    long long B; 
    cin >> N >> B; 
    
    int length = getBitLength(B); 

    vector<Matrix> power;
    power.reserve(length); 
    for(int i = 0; i < N; i++){
        power.emplace_back(N); 
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> power[0].data[i][j]; 
            power[0].data[i][j] %= 1000; 
        }
    }
    
    for(int i = 1; i < length; i++){
        power[i] = power[i-1] * power[i-1]; 
    }

    Matrix result(N); 
    bool init = false; 
    int cnt = 0; 
    int re; 
    
    while(B != 0){
        re = B % 2; 
        B = B / 2; 
        if(re == 1){
            if(init == false){
                result = power[cnt]; 
                init = true;
            }
            else
                result = result * power[cnt]; 
        }
        cnt++; 
    }
    cout << result; 
    return 0; 
}