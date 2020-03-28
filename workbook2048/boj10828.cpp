#include <bits/stdc++.h>

using namespace std;

class Stack{
private :
    int cursor = -1;
    int max_length = 10000;
    int *arr;
public :
    Stack(int length = 0){
        max_length = length;
        arr = new int[length];
    }
    void push(int number);
    int pop();
    int get_size();
    bool is_empty();
    int top();
};

void Stack::push(int number){
    cursor++;
    arr[cursor] = number;
}

int Stack::pop(){
    int res;
    if(cursor != -1){
        res = arr[cursor];
        cursor--;
    }
    else{
        res = -1;
    }
    return res;
}

int Stack::get_size(){
    return cursor + 1;
}

bool Stack::is_empty(){
    if(cursor < 0)
        return true;
    else
        return false;
}

int Stack::top(){
    if(cursor != -1){
        return arr[cursor];
    }
    else
        return -1;
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    Stack s(n);

    for(int i = 0; i < n; i++){
        string str;
        cin >> str;
        if(str == "push"){
            int num;
            cin >> num;
            s.push(num);
        }
        else if(str == "pop"){
            cout << s.pop() << endl;
        }
        else if(str == "top"){
            cout << s.top() << endl;
        }
        else if(str == "empty"){
            cout << int(s.is_empty()) << endl;
        }
        else if(str == "size"){
            cout << s.get_size() << endl;
        }
    }
    return 0;
}
