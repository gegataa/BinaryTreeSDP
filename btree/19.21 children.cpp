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

int get_successors(Node* root)
{
    if(!root)
    {
        return 0;
    }
    
    return 1 + get_successors(root->left) + get_successors(root->right);
}

void solution(Node*& root)
{
    if(!root)
    {
        return;
    }
    solution(root->left);
    root->data = get_successors(root);
    solution(root->right);
}
int main()
{
    Node* root = new Node(10);
    Node* rootL = new Node(5);
    Node* rootR = new Node(20);
    Node* rootLL = new Node(2);
    Node* rootRL = new Node(15);
    Node* rootRR = new Node(25);
    Node* rootRRL = new Node(22);
    root->left = rootL;
    root->right = rootR;
    rootL->left = rootLL;
    rootR->left = rootRL;
    rootR->right = rootRR;
    rootRR->left = rootRRL;
    inorder(root);
    std::cout << get_successors(root);
    solution(root);
    std::cout << std::endl;
    inorder(root);
    deleteNode(root);
}

