#include <iostream>

struct Node
{
    int data;
    Node* left;
    Node* right;

    Node(int data)
    {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }
};

void deleteNode(Node* root)
{
    if (!root) 
    {
        return;
    }
    deleteNode(root->left);
    deleteNode(root->right);
    delete root;
}

void inorder(Node* root)
{
    if (!root)
    {
        return;
    }
    inorder(root->left);
    std::cout << root->data << " ";
    inorder(root->right);
}

void addRow(Node* &root, int val)
{
    if(!root)
    {
        return;
    }

    if(!root->left&&!root->right)
    {
        root->left = new Node(val);
        root->right = new Node(val);
        return;
    }
    addRow(root->left, val);
    addRow(root->right, val);
}

Node* sol(int h)
{
    Node* root = new Node(0);
    for(int i = 1;i<=h;i++)
    {
        addRow(root, i);
    }
    return root;
}
int main()
{
    Node* root = new Node(0);
    inorder(sol(2));
    deleteNode(root);
}

