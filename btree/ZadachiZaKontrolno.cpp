#include <iostream>
#include <queue>
#include <vector>
#include <sstream>
template <typename T>
struct Node
{
    T data;
    Node<T>* left;
    Node<T>* right;
    Node()
    {
        left = nullptr;
        right = nullptr;
    }
    Node(T data)
    {
        this->data = data;
        left = nullptr;
        right = nullptr;
    }

};

template <typename T>
void deleteNode(Node<T>* &root)
{
    if(!root)
    {
        return;
    }
    deleteNode(root->left);
    deleteNode(root->right);
    
}

template <typename T>
void inorderPrint(Node<T>* root)
{
    if(!root)
    {
        return;
    }
    inorderPrint(root->left);
    std::cout << root->data<<" ";
    inorderPrint(root->right);
    
}
// zad 1
template <typename T>
void InvertTree(Node<T>* &root)
{
    if(!root)
    {
        return;
    }

    Node<T>* temp = root->left;
    root->left = root->right;
    root->right = temp;
    InvertTree(root->left);
    InvertTree(root->right);
}
// zad 2 
template <typename T>
std::vector<std::vector<T>> getLevels(Node<T>* root)
{
    std::vector<std::vector<T>> res;
    if(!root)
    {
        return res;
    }
    std::queue<Node<T>*> q;
    q.push(root);
    q.push(NULL);

    std::vector<T> curr_level;

    while(q.size()>1)
    {
        Node<T>* temp = q.front();
        q.pop();
        if(!temp)
        {
            q.push(NULL);
            res.push_back(curr_level);
            curr_level.clear();
        }
        else
        {
            if(temp->left)
            {
                q.push(temp->left);
            }
            if(temp->right)
            {
                q.push(temp->right);
            }
            curr_level.push_back(temp->data);
        }
    }
    if(!curr_level.empty())
    {
        res.push_back(curr_level);
    }
    return res;
    
    
}
template <typename T>
std::vector<T> getLvl(Node<T>* root,int i)
{
    std::vector<std::vector<T>> lvls = getLevels(root);
    if(i>lvls.size()||i<0)
    {
        return {};
    }
    return lvls[i];
}
// zad 3
template <typename T>
bool smaller(Node<T>* root,Node<T>* root2)
{
    if(!root)
    {
        return false;
    }
    if(!root2)
    {
        return true;
    }
    return root->data == root2->data && smaller(root->left, root2->left) && smaller(root->right, root2->right);
}
// zad 4
template <typename T>
bool areEqual(Node<T>* root, Node<T>* root2)
{
    if(!root&&!root2)
    {
        return true;
    }
    if(!root||!root2)
    {
        return false;
    }
    return root->data == root2->data && areEqual(root->left, root2->left) && areEqual(root->right, root2->right);
}
// zad 5
int maxPathSum(Node<int>* root)
{
    if(!root)
    {
        return 0;
    }
    return root->data + std::max(maxPathSum(root->left), maxPathSum(root->right));
}
// zad 6
template <typename T>
void AllPaths(Node<T>* root, std::vector<std::vector<T>> &res, std::vector<T> curr)
{
    if(!root)
    {
        return;
    }
    if(!root->left&&!root->right)
    {
        curr.push_back(root->data);
        res.push_back(curr);
    }
    else
    {
        curr.push_back(root->data);
    }
    AllPaths(root->left,res,curr);
    AllPaths(root->right, res, curr);
}
// Zad 7
template <typename T>
std::vector<T> getLongest(Node<T>* root)
{
    std::vector<std::vector<T>> paths;
    AllPaths(root, paths, {});
    
    std::vector<T> res;
    for(std::vector<T> i:paths)
    {
        if(i.size()>res.size())
        {
            res = i;
        }
    }
    return res;
}

void serialize_help(Node<std::string>* root,std::ostringstream & out)
{
    if(!root)
    {
        out<<"";
    }
    else
    {
        
    serialize_help(root->left,out);
    out << "(";
    out << root->data<<" ";
    out << ")";
    serialize_help(root->right, out);
  
    }
}

std::string serialize(Node<std::string>* root)
{
    std::ostringstream out;
    serialize_help(root, out);
    return out.str();
}

double eval(Node<std::string>* root)
{
    if(!root)
    {
        return 0;
    }
    if(!root->left &&!root->right)
    {
        return std::stod(root->data);
    }
    double Lefts = eval(root->left);
    double Rights = eval(root->right);
    
    if(root->data == "+")
    {
        return Lefts + Rights;
    }
    if(root->data=="-")
    {
        return Lefts - Rights;
    }
    if(root->data=="*")
    {
        return Lefts * Rights;
    }
    return Lefts / Rights;
}
int main()
{
    /*Node<int>* root = new Node<int>(2);
    Node<int>* rootL = new Node<int>(1);
    Node<int>* rootR = new Node<int>(3);
    Node<int>* rootLL = new Node<int>(5);
    Node<int>* rootLR = new Node<int>(6);
    Node<int>* rootRL = new Node<int>(7);
    Node<int>* rootRR = new Node<int>(8);
    Node<int>* rootRRR = new Node <int>(10);
    root->left = rootL;
    root->right = rootR;
    rootL->left = rootLL;
    rootL->right = rootLR;
    rootR->left = rootRL;
    rootR->right = rootRR;
    rootRR->right = rootRRR;

    Node<int>* root2 = new Node<int>(2);
    Node<int>* rootL2 = new Node<int>(1);
    Node<int>* rootR2 = new Node<int>(3);
    root2->left = rootL2;
    root2->right = rootR2;
    inorderPrint(root);
    InvertTree(root);
    std::cout << '\n';
    inorderPrint(root);
    std::vector<int> t = getLvl(root, 2);
    std::cout << '\n';
    for(int i:t)
    {
        std::cout << i << " ";
    }
    InvertTree(root2);
    std::cout << '\n';
    std::cout << maxPathSum(root);
    deleteNode(root);
    std::cout << '\n';
    std::vector<int> lp = getLongest(root);
    for (int i : lp)
    {
        std::cout << i << " ";
    }
    */
    Node<std::string>* root = new Node<std::string>("+");
    Node<std::string>* rootL = new Node<std::string>("20");
    Node<std::string>* rootR = new Node<std::string>("*");
    Node<std::string>* rootRL = new Node<std::string>("17");
    Node<std::string>* rootRR = new Node<std::string>("/");
    Node<std::string>* rootRRL = new Node<std::string>("7");
    Node<std::string>* rootRRR = new Node<std::string>("5");
    root->left = rootL;
    root->right = rootR;
    rootR->left = rootRL;
    rootR->right = rootRR;
    rootRR->right = rootRRR;
    rootRR->left = rootRRL;
    std::cout<<serialize(root);
    std::cout << eval(root);
    deleteNode(root);
}
