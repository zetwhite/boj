#include <iostream> 
#include <vector> 

using namespace std; 

class Node{
public: 
    int parent; 
    vector<int> childs; 
    bool alive; 
    bool isLeaf(); 
}; 

Node nodes[55]; 

bool Node::isLeaf(){
    for(int i = 0; i < childs.size(); i++){
        if(nodes[childs[i]].alive) 
            return false;  
    }
    return true; 
}

void deleteNode(Node& n){
    n.alive = false; 
    for(int i = 0; i < n.childs.size(); i++){
        deleteNode(nodes[n.childs[i]]); 
    }
    n.childs.clear(); 
    return;
}


int main(){
    int n;
    cin >> n; 

    for(int i = 0; i < n; i++){
        int parent; 
        cin >> parent; 
        nodes[i].parent = parent;
        nodes[i].alive = true; 
        if(parent != -1)
            nodes[parent].childs.push_back(i); 
    }

    int del; 
    cin >> del; 
    deleteNode(nodes[del]); 
    
    int cnt = 0; 
    for(int i = 0; i < n; i++){
        if(nodes[i].alive)
            if(nodes[i].isLeaf()){
                //cout << i << " is child!" << endl; 
                cnt++; 
            }
    }

    cout << cnt << endl; 
    return 0; 
}