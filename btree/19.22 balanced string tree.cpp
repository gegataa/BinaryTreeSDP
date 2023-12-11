#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>

struct Node
{
    std::string data;
    Node* left;
    Node* right;
    Node(std::string data)
    {
        this->data = data;
        left = nullptr;
        right = nullptr;
    }
    Node()
    {
        left = nullptr;
        right = nullptr;
    }
};

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

std::vector<std::string> get_strings(Node* root)
{
    std::vector<std::string> res;
    if(!root)
    {
        return res;
    }

    std::queue<Node*> q;
    q.push(root);
    q.push(NULL);

    std::string curr;
    while(q.size()>1)
    {
        Node* temp = q.front();
        q.pop();
        if(!temp)
        {
            q.push(NULL);
            res.push_back(curr);
            curr.clear();
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
            curr.append(temp->data);
        }
    
    }
    res.push_back(curr);
    return res;
}

std::vector<std::string> split_strings(std::string str, int parts)
{
    std::vector<std::string> res;
    double part_len = ceil(str.length() / (double)parts);
    while(part_len<str.length())
    {
        res.push_back(str.substr(0, part_len));
        str.erase(0, part_len);
    }
   if(!str.empty())
   {
       res.push_back(str);
   }
   return res;
}

void level_order_insert(Node* &root, std::string str)
{
    if(!root)
    {
        return;
    }

    std::queue<Node*> q;
    q.push(root);

    while(!q.empty())
    {
        Node* temp = q.front();
        q.pop();
        if(temp->left)
        {
            q.push(temp->left);
        }
        else
        {
            temp->left = new Node(str);
            return;
        }

        if (temp->right)
        {
            q.push(temp->right);
            
        }
        else
        {
            temp->right = new Node(str);
            return;
        }

    }
}

void level_order_print(Node* root)
{
    if(!root)
    {
        return;
    }

    std::queue<Node*> q;
    q.push(root);
    q.push(NULL);

    while(q.size()>1)
    {
        Node* temp = q.front();
        q.pop();
        if(!temp)
        {
            q.push(NULL);
            std::cout << '\n';
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
            std::cout << temp->data<<" ";
        }
    }
}

Node* solution(Node* root)
{
    std::vector<std::string> strings = get_strings(root);
    Node* res = new Node(strings[0]);
    for(int i = 1;i<strings.size();i++)
    {
        std::vector<std::string> split_string = split_strings(strings[i], pow(2, i));
        for(std::string s:split_string)
        {
            level_order_insert(res, s);
        }
    }
    return res;
}
int main()
{
    Node* root = new Node("this is a tree");
    Node* rootL = new Node("which has");
    Node* rootR = new Node("strings");
    Node* rootLL = new Node("on its");
    Node* rootLR = new Node("nodes");
    Node* rootRR = new Node("and");
    Node* rootLLL = new Node("your task");
    Node* rootLRL = new Node("is to have");
    Node* rootRRL = new Node("fun with it");
    root->left = rootL;
    root->right = rootR;
    rootL->left = rootLL;
    rootL->right = rootLR;
    rootR->right = rootRR;
    rootLL->left = rootLLL;
    rootLR->left = rootLRL;
    rootRR->left = rootRRL;
    Node* sol_test = solution(root);
    level_order_print(sol_test);
    //std::vector<std::string> t = split_string_into_parts("on itsnodesand", 4);
    //for(std::string st:t)
    //{
     //   std::cout << st << "\n";
    //}
   

}