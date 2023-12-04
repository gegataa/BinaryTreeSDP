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
	
	void print_help(const Node<T>* root)
	{
		if (!root)
		{
			return;
		}

		print_help(root->left);
		std::cout << root->data<<" ";
		print_help(root->right);
	}

	T left_most(Node<T>* root)
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

	void add_help(Node<T>* &root, const T data,std::string path)
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
			return;
		}

		if(path.empty())
		{
			root->data = data;
		}

		if(path[0]=='L')
		{
			add_help(root->left, data, path.substr(1, path.size() - 1));
			return;
		}

		if (path[0] == 'R')
		{
			add_help(root->right, data, path.substr(1, path.size() - 1));
			return;
		}
	}

	int level(Node<T>* root, T data, int curr_lvl)
	{
		if(!root)
		{
			return = -1;
		}

		if (root->data == data) 
		{
			return curr_lvl;
		}

		int leftL = level(root->left, data, curr_lvl + 1);
		if(leftL>0)
		{
			return leftL;
		}

		return level(root->right, data, curr_lvl + 1);
	}

	std::vector<T> levelItems(Node<T>* root, int lvl)
	{
		if(!root)
		{
			return std::vector<T>();
		}

		if(lvl==1)
		{
			return std::vector<T>({ root->data });
		}

		std::vector<T> lefts = levelItems(root->left, lvl - 1);
		std::vector<T> right = levelItems(root->right, lvl - 1);

		lefts.insert(lefts.end(), right.begin(), right.end());
		return lefts;
	}
	
	bool equal(Node<T>* tree_1, Node<T>* tree_2)
	{
		if(!tree_1&&!tree_2)
		{
			return true;
		}

		if(!tree_1)
		{
			return false;
		}

		if(!tree_2)
		{
			return false;
		}

		return tree_1->data==tree_2->data&&equal(tree_1->left,tree_2->left)&& equal(tree_1->right, tree_2->right)
	}

	bool isSubTree(Node<T>* tree_1, Node<T>* tree_2)
	{
		if(!tree_2)
		{
			return true;
		}

		if(!first)
		{
			return false;
		}

		if(equal(tree_1,tree_2))
		{
			return true;
		}

		return isSubTree(tree_1->left, tree_2->left) || isSubTree(tree_1->right, tree_2->right)
	}
	Node<T>* lca(Node<T>* root, Node<T>* first, Node<T>* second)
	{
		if(!root)
		{
			return nullptr;
		}
		if(root ==first)
		{
			return root
		}
		if(root==second)
		{
			return root;
		}
		Node<T>* Llca = lca(root->left, first, second);
		Node<T>* Rlca = lca(root->right, first, second);

		if(Llca&&Rlca)
		{
			return root;
		}

		return Llca ? Llca : Rlca;	
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
		print_help(root);
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
		add_help(root, value, path);
	}

	bool isSubTree(const BinaryTree<T>& other)
	{
		return isSubTree(root, other.root);
	}
	
	std::vector<T> levelItems(int lvl)
	{
		return levelItems(root,lvl)
	}



	~BinaryTree()
	{
		cleanup(root);
	}
};


int main()
{
	BinaryTree<int> test;
	test.add(1, "");
	test.add(2, "L");
	test.add(3, "R");
	test.print();
	BinaryTree<int> copy_test = test;
	copy_test.print();
	
	
}

