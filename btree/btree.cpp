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

	Node(const T& data, Node<T>* left, Node<T>* right)
	{
		this->data = data;
		this->left = left;
		this->right = right;
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

	void cleanup(Node<T>* root)
	{
		if (!root)
		{
			return;
		}
		cleanup(root->left);
		cleanup(root->right);
		delete root;
	}

	int height(const Node<T>* root)
	{
		if (!root)
		{
			return 0;
		}

		return 1 + std::max(height(root->left), height(root->right));
	}

	int leaves(const Node<T>* root)
	{
		if (!root)
		{
			return 0;
		}

		if (!root->left && !root->right)
		{
			return 1;
		}

		return leaves(root->left) + leaves(root->right);
	}

	void print(const Node<T>* root)
	{
		if (!root)
		{
			return;
		}

		print(root->left);
		std::cout << root->data;
		print(root->right);
	}

	T left_most(const Node<T>* root)
	{
		Node<T>* temp = root;
		while (temp->left && temp->right)
		{
			if (!temp->left)
			{
				temp->right;
			}
			else
			{
				temp = temp->left;
			}
		}
		return temp->data;
	}

	T minval(const Node<T>* root)
	{
		if (!root->left && !root->right)
		{
			return root->data;
		}

		if (!root->right) // nq dqsno
		{
			return std::min(root->data, minval(root->left));
		}

		if (!root->left)
		{
			return std::min(root->data, minval(root->right));
		}

		return std::min(root->data, std::min(minval(root->right), minval(root->left)));
	}

	Node<T>* copy(Node<T>* other)
	{
		if(!root)
		{
			return nullptr;
		}
		
		return new Node<T>*(other->data, copy(other->left), copy(other->right));
	}

	void add(Node<T>* root, const T data,std::string path)
	{
		if(!root)
		{
			if(path.empty())
			{
				root = new Node<T>(data);
			}
			else
			{
				throw "Out of tree bounds";
			}
			return
		}

		if(path.empty())
		{
			root->data = data;
		}

		if(path[0]=='L')
		{
			add(root->left, data, path.size() - 1);
			return;
		}

		if (path[0] == 'R')
		{
			add(root->right, data, path.size() - 1);
			return;
		}
	}

public:
	BinaryTree()
	{
		root = nullptr;
	}
	BinaryTree(const BinaryTree<T>& other)
	{
		cleanup(root);
		root = nullptr;
		copy(other);
	}
	BinaryTree& operator= (const BinaryTree<T>& other)
	{
		if(this!=other)
		{
			cleanup(root);
			root = copy(other.root);
		}
		return *this;

	}
	bool member(const T& data)
	{
		return member(root, data);
	}

	int height()
	{
		return height(root);
	}

	int leaves()
	{
		return leaves(root);
	}

	void print()
	{
		print(root);
		std::cout << '\n';
	}

	T left_most()
	{
		return left_most(root);
	}

	T min()
	{
		return minval(root);
	}
	
	void add(const T value,std::string path)
	{
		add(root, value, path);
	}

	~BinaryTree()
	{
		cleanup(root);
	}
};


int main()
{

}

