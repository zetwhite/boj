#include <iostream>

using namespace std; 

class Node{
public: 
    Node* left; 
    Node* right; 
    int colIndex; 
    int depth; 
    Node():left(NULL), right(NULL), colIndex(0){}
}; 

Node* nodes; 
int cnt = 1; 
int* mind; 
int* maxd; 

void inordering(Node& root, int depth){
    if(root.left != NULL)
        inordering(*(root.left), depth + 1);
    root.depth = depth; 
    root.colIndex = cnt; 
    cnt++; 
    if(root.right != NULL)
        inordering(*(root.right), depth + 1); 
}

void search(Node& root){
    int idx = root.colIndex; 
    if(mind[root.depth] > idx) 
        mind[root.depth] = idx; 
    if(maxd[root.depth] < idx) 
        maxd[root.depth] = idx; 
    if(root.left != NULL)
        search(*(root.left)); 
    if(root.right != NULL)
        search(*(root.right)); 
}

int main(){
    int n; 
    cin >> n; 
    nodes = new Node[n+1]; 
    int* pcnt = new int[n+1](); 
    for(int i = 1; i <= n; i++){
        int parent, left, right; 
        cin >> parent >> left >> right; 
        if(left != - 1){
            nodes[parent].left = nodes+left; 
            pcnt[left]++; 
        }

        if(right != -1){
            nodes[parent].right = nodes+right; 
            pcnt[right]++; 
        }
    }

    int root = 0; 
    for(int i = 1; i <= n; i++){
        if(pcnt[i] == 0){
            root = i; 
        }
    }
    //cout << "root = " << root << endl; 
    inordering(nodes[root], 1); 

    int maxDepth = 0; 
    for(int i = 1; i <= n; i++){
        /*cout << "==================" << endl; 
        cout << i << " : " << i << endl; 
        cout <<"depth : " << nodes[i].depth << endl; 
        cout <<"idx   : " << nodes[i].colIndex << endl; */
        if(nodes[i].depth > maxDepth)
            maxDepth = nodes[i].depth; 
    }
    //cout << "maxDepth = " << maxDepth << endl; 
    mind = new int[maxDepth+1]; 
    maxd = new int[maxDepth+1]; 
    for(int i = 0; i <= maxDepth; i++){
        mind[i] = 20000; 
        maxd[i] = -1; 
    }
    search(nodes[root]); 
    int height = 0; 
    int width = 0; 

    for(int i = 1; i <= maxDepth; i++){
        int newWidth = maxd[i] - mind[i] + 1; 
        if(newWidth > width){
            width = newWidth; 
            height = i; 
        }
    }
    cout << height << " " << width << endl; 
    return 0; 
}