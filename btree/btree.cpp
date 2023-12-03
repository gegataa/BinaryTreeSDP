#include <iostream>
#include <vector>

template <typename T>
struct Node
{
    T data;
    Node<T>* left;
    Node<T>* right;

    Node(const T& data)
    {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }
};

template <typename T>
class BinaryTree
{
private:
    Node<T>* root;
    bool member(Node<T>* root, const T& data)
    {
        if (!root)
        {
            return false;
        }

        return root->data == data ||
            member(root->left, data) ||
            member(root->right, data);
    }
public:
    BinaryTree()
    {
        root = nullptr;
    }
   
    bool member(const T& data)
    {
        member(root, data);
    }
    
};


int main()
{
  
    
   

    return 0;
}

