
#include <iostream>
#include <queue>

template <typename T>
struct Node
{
    T data;
    Node* left, * right;
    Node(T data)
    {
        this->data = data;
        left = nullptr;
        right = nullptr;
    }
    Node(T data, Node<T>* left, Node<T>* right)
    {
        this->data = data;
        this->left = left;
        this->right = right;
    }
};

template <typename T>
class BSTree
{
private:
    Node<T>* root;
    void isBST(Node<T>* root)
    {
        if (!root)
        {
            return true;
        }

        if (root->left)
        {
            if (root->left->data < root->data)
            {
                return true;
            }
            return false;
        }

        if (root->right)
        {
            if(root->right->data > root->data)
            {
                return true;
            }
            return false;
        }

        return isBST(root->left) && isBST(root->right);
    }

    T find_min(Node<T>* root)
    {
        Node<T>* temp = root;
        while(temp->left)
        {
            temp = temp->left;
        }
        return temp->data;
    }

    T find_max(Node<T>* root)
    {
        Node<T>* temp = root;
        while (temp->right)
        {
            temp = temp->right;
        }
        return temp->data;                      
    }

    void add_help(Node<T>* &root, const T& value)
    {
        if(!root)
        {
            root = new Node<T>(value);
        }

        if(value<root->data)
        {
            add_help(root->left, value);
        }
        if(value>root->data)
        {
            add_help(root->right, value);
        }
        else
        {
            throw "Element already in tree";
        }
    }

    void remove(Node<T>* &root, const T& value)
    {
        
        // 1. Namirame elementa
        
        if(!root)
        {
            return;
        }
        if(root->data<value) // ako e po malka nalqvo
        {
            remove(root->left, value);
        }
        else if(root-<data>value)  // ako stoinostta e po golqma otivame nadqsno
        {
            remove(root->right, value);
        }
        else  // Namerili sme go
        {
            if(!root->left&&!root->right) // 2.1 Listo e
            {
                delete root;
                return;
            }
            else if (!root->left || !root->right) // 2.2 ima edin naslednik
            {
                if(root->left)
                {
                    Node<T>* to_delete = root;
                    root = root->left;
                    delete to_delete;
                    return;
                }

                if (root->right)
                {
                    Node<T>* to_delete = root;
                    root = root->right;
                    delete to_delete;
                    return;
                }

            }
            else
            {
                Node<T>* temp = root;
                while(temp->right)
                {
                    temp = temp->right;
                }
                root->data = temp->data;
                remove(root->right, temp->data);
                return;
            }


        }

    }
    void print_inorder(Node<T>* root)
    {
        if(!root)
        {
            return;
        }
        print_inorder(root->left);
        std::cout << root->data << " ";
        print_inorder(root->left);
    }

    void print_levelOrder(Node<T>* root)
    {
        if(!root)
        {
            return;
        }

        std::queue<Node<T>*> q;
        q.push(root);
        q.push(NULL);
        while(q.size()>1)
        {
            Node<T>* curr = q.front();
            q.pop();

            if(!curr)
            {
                q.push(NULL);
                std::cout << '\n';
            }

            if(curr->left)
            {
                q.push(curr->left);
            }
            if(curr->right)
            {
                q.push(curr->right);
            }

            std::cout << curr->data << " ";
        }
    }

    void cleanup(Node<T>* &root)
    {
        if(!root)
        {
            return;
        }

        cleanup(root->left);
        cleanup(root->right);
        delete root;
    }

    Node<T>* copy(Node<T>* other)
    {
        if(!other)
        {
            return nullptr;
        }

        return new Node<T>(other->data, copy(other->left), copy(other->right));
    }
public:
    BSTree()
    {
        root = nullptr;
    }

    BSTree(const BSTree<T>& other):root(nullptr)
    {
        root = copy(other);
    }
    BSTree& operator=(const BSTree<T>& other)
    {
        if(!this!=other)
        {
            cleanup(root);
            root = copy(other);
        }
        return *this;
    }
    void isBST()
    {
        return isBST(root);
    }

    T min()
    {
        return find_min(root);
    }

    T max()
    {
        return find_max;
    }

    void add(const T& value)
    {
        add(root, value);
    }

    void remove(const T& value)
    {
        remove(root, value);
    }

    void print()
    {
        print_inorder(root);
    }

    void print_level_order()
    {
        print_levelOrder(root);
    }
    
    ~BSTree()
    {
        cleanup(root);
    }
};
int main()
{
   
}


