// TreeExcercises.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include <string>
#include <queue>


struct Node
{
    char data;
    Node* left, * right;
    Node(char data)
    {
        this->data = data;
        left = nullptr;
        right = nullptr;
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

void inorder(Node* curr)
{
    if (!curr)
    {
        return;
    }
    inorder(curr->left);
    std::cout << curr->data;
    inorder(curr->right);
}


int get_height(int len)
{
    return ceil (log2(len));
}

void get_empty_row(Node* &root)
{
    if(!root)
    {
        return;
    }
    if(!root->left&&!root->right)
    {
        root->left = new Node('/');
        root->right = new Node('/');
        return;
    }
    get_empty_row(root->left);
    get_empty_row(root->right);
}

Node* get_empty_tree(int h)
{
    Node* res = new Node('/');
    for(int i = 1;i<h;i++)
    {
        get_empty_row(res);
    }
    return res;
}

void levelOrderInsert(Node* &root, char val)
{
    if(!root)
    {
        root = new Node(val);
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
            temp->left = new Node(val);
            return;
        }
        if(temp->right)
        {
            q.push(temp->right);
        }
        else
        {
            temp->right = new Node(val);
            return;
        }
    }
}

void levelOrderPrint(Node* root)
{
    if(!root)
    {
        return;
    }
    std::queue<Node*> q;
    q.push(root);
    q.push(NULL);
    while (q.size()>1)
    {
        Node* temp = q.front();
        q.pop();
        if (!temp)
        {
            q.push(NULL);
            std::cout << std::endl;
        }
        else
        {
            if (temp->left)
            {
                q.push(temp->left);
            }
            if (temp->right)
            {
                q.push(temp->right);
            }
            std::cout << temp->data<<" ";
        }
    }
}

Node* sol(std::string str)
{
    int height = get_height(str.length());
    Node* res = get_empty_tree(height);
    for(int i = 0;i<str.length();i++)
    {
        levelOrderInsert(res, str[i]);
    }
    return res;
}
int main()
{
    Node* root = sol("Hello!");
    levelOrderPrint(root);
    deleteNode(root);
}
    