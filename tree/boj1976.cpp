#include <iostream> 
using namespace std; 

int connect[201][201]; 

class Node{
public : 
    Node() : root(nullptr){}; 
    Node* root; 
    int value; 
}; 

Node* getRoot(Node& node){
    Node* next = &node; 
    while(next->root != nullptr){
        next = next->root; 
    }
    return next; 
}

void MakeConnection(Node& n1, Node& n2){
    Node* root1 = getRoot(n1); 
    Node* root2 = getRoot(n2); 

    if(root1 != root2){
        root2->root = root1; 
        n2.root = root1; 
    }
}

int main(){
    int N, M; 
    cin >> N >> M; 
    Node nodes[N + 1]; 

    for(int i = 1; i <= N; i++){
        nodes[i].value = i; 
    }

    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            cin >> connect[i][j]; 
        }
    }

    for(int i = 2; i <= N; i++){
        for(int j = 1; j < i; j++){
            if(connect[i][j] == 1){
                MakeConnection(nodes[i], nodes[j]); 
            }
        }
    }

    int start; 
    cin >> start; 
    int group = getRoot(nodes[start])->value; 
    int next;
    bool success = true; 
    for(int i = 1; i < M; i++){
        cin >> next; 
        if(group != getRoot(nodes[next])->value){
            success = false; 
        }
    }
    if(success)
        cout << "YES" << endl; 
    else
        cout << "NO" << endl; 
    return 0; 
}