#include <bits/stdc++.h>

using namespace std;

struct node {
    char character;
    struct node *left;
    struct node *right;
    node(char ch) : character(ch), left(NULL), right(NULL) {}
};

struct node_info{
    char left;
    char right;
};

class Tree{
public:
    struct node* root;
    void make_node(struct node** new_node, char ch, struct node_info (*info)[26]){
        *new_node = new node(ch);
        if((*info)[ch-'A'].left != -1)
            make_node(&((*new_node)->left), (*info)[ch-'A'].left, info);
        if((*info)[ch-'A'].right != -1)
            make_node(&((*new_node)->right), (*info)[ch-'A'].right, info);
    }

    void print_preorder(struct node* root){
        cout << root->character;
        if(root->left)
            print_preorder(root->left);
        if(root->right)
            print_preorder(root->right);
    }

    void print_inorder(struct node* root){
        if(root->left)
            print_inorder(root->left);
        cout << root->character;
        if(root->right)
            print_inorder(root->right);
    }

    void print_postorder(struct node* root){
        if(root->left)
            print_postorder(root->left);
        if(root->right)
            print_postorder(root->right);
        cout << root->character;
    }
};

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    struct node_info infos[26];
    for(int i = 0; i < n; i++){
        char ch, tmp;
        cin >> ch;
        cin >> tmp;
        if(tmp != '.')
            infos[ch - 'A'].left = tmp;
        else
            infos[ch - 'A'].left = -1;
        cin >> tmp;
        if(tmp != '.')
            infos[ch - 'A'].right = tmp;
        else
            infos[ch - 'A'].right = -1;
    }

    Tree tree;
    tree.make_node(&(tree.root), 'A', &infos);
    tree.print_preorder(tree.root);
    cout << endl;
    tree.print_inorder(tree.root);
    cout << endl;
    tree.print_postorder(tree.root);
    cout << endl;
    return 0;
}
