

#include <iostream>
template <typename T>
struct Node
{
    T data;
    Node<T>* left;
    Node<T>* right;

    Node(T data)
    {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }
};
template <typename T>
void delete_tree(Node<T> *&root)
{
    if(!root)
    {
        return;
    }
    delete_tree(root->left);
    delete_tree(root->right);
    
    root = nullptr;
   
}

template <typename T>
void print(Node<T>* root)
{
    if(!root)
    {
        return;
    }
    print(root->left);
    std::cout << root->data<<" ";
    print(root->right);
}

template <typename T>
T find_max(Node<T>* root)
{
    if (!root->left&&!root->right)
    {
        return root->data;
    }
    
    if (root->left&&!root->right)
    {
        return std::max(root->data, find_max(root->left));
    }
    if(root->right&&!root->left)
    {
        return std::max(root->data, find_max(root->right));
    }

    return std::max(root->data, std::max(find_max(root->left), find_max(root->right)));
    
}

template <typename T>
void prune_tree(Node<T>* &root)
{
    if (!root)
    {
        return;
    }

    prune_tree(root->left);
    prune_tree(root->right);
    if (root->data < find_max(root))
    {
        delete_tree(root);
    }

   
}
int main()
{
    Node<int>* root = new Node<int>(10);
    Node<int>* rootL = new Node<int>(5);
    Node<int>* rootR = new Node<int>(20);
    Node<int>* rootLL = new Node<int>(2);
   
    Node<int>* rootRL = new Node<int>(15);
    Node<int>* rootRR = new Node<int>(25);
    Node<int>* rootRRL = new Node<int>(22);
    root->left = rootL;
    root->right = rootR;
    rootL->left = rootLL;

    rootR->left = rootRL;
    rootR->right = rootRR;
    rootRR->left = rootRRL;
    print(root);
    std::cout << '\n';
    prune_tree(root);
    print(root);
    delete_tree(root);
}

