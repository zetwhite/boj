#include <iostream> 
#include <vector>
#include <algorithm>  
using namespace std; 

bool desc(int a, int b){
    return a > b; 
}

class Node{
public: 
    int parent; 
    vector<pair<int, int>> childs; //depth, childs
    int underDepth; 
    int radius; 
    Node() : parent(-1), underDepth(-1), radius(-1){}
    
    void add_c(int depth, int child){
        childs.push_back(make_pair(depth, child));
    }
    int getRadius(); 
};

Node* nodes; 

int Node::getRadius(){

    if(childs.size() == 0){
        radius = 0; 
        return 0; 
    }
    if(childs.size() == 1){
        radius = childs[0].first + nodes[childs[0].second].underDepth;  
        return radius; 
    }
    vector<int> tmp; 
    for(int i = 0; i < childs.size(); i++){
        tmp.push_back(childs[i].first + nodes[childs[i].second].underDepth); 
    }
    sort(tmp.begin(), tmp.end(), desc); 
    radius = tmp[0] + tmp[1]; 
    return radius; 
}

int getMaxDepth(Node& n){
    
    if(n.underDepth != -1)
        return n.underDepth; 
    if(n.childs.empty()){
        n.underDepth = 0; 
        return 0; 
    }
    int max = 0; 
    for(int i = 0; i < n.childs.size(); i++){
        int tmp = getMaxDepth(nodes[n.childs[i].second]); 
        tmp += n.childs[i].first; 
        if(tmp > max) 
            max = tmp; 
    }
    n.underDepth = max; 
    return max; 
    
   return 0; 
}

int main(){
    int n; 
    cin >> n; 
    nodes = new Node[n+1]; 

    for(int i = 1; i < n; i++){
        int parent, child, depth; 
        cin >> parent >> child >> depth; 

        nodes[parent].add_c(depth, child); 
        nodes[child].parent = parent; 
    }

    int root = 0; 
    for (int i = 1; i <= n; i++){
        if(nodes[i].parent == -1)
            root = i; 
    }
    getMaxDepth(nodes[root]); 

    int maxRadius = 0; 
    for(int i = 1; i <= n; i++){
        int tmp = nodes[i].getRadius();
        if(tmp > maxRadius)
            maxRadius = tmp; 
    }
    cout << maxRadius << endl; 
    return 0; 
}