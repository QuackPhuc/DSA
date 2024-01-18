#include <iostream>
#include <queue>
using namespace std;

struct Node
{
	int data;
	struct Node *left;
	struct Node *right;

	Node() : data(NULL), left(nullptr), right(nullptr){};
	Node(int data) : data(data), left(nullptr), right(nullptr){};
	Node(int data, Node *left, Node *right) : data(data), left(left), right(right){};

	bool operator>(Node other) { return data > other.data; }
	bool operator<(Node other) { return data < other.data; }
	bool operator>=(Node other) { return data >= other.data; }
	bool operator<=(Node other) { return data <= other.data; }
};

int max(int a, int b) {
	if (a > b) return a;
	return b;
}

int height(Node* node) {
	if(!node) return 0;
	return max(height(node->left),height(node->right)) + 1;
}

void inOrder(Node *node, std::ostream &stream)
{
	if (node)
	{
		inOrder(node->left, stream);
		stream << node->data << " ";
		inOrder(node->right, stream);
	}
}

void inOrder(Node* root) {
	if (root) {
		inOrder(root->left);
		cout << root->data << " ";
		inOrder(root->right);
	}
}

void preOrder(Node* root) {
	if (root) {
		cout << root->data << " ";
		preOrder(root->left);
		preOrder(root->right);
	}
}

void postOrder(Node* root) {
	if (root) {
		postOrder(root->left);
		postOrder(root->right);
		cout << root->data << " ";
	}
}

void levelOrder(Node *root) {
	if (!root) return;
	queue<Node *> nodeQueue;
	nodeQueue.push(root);
	while (!nodeQueue.empty())
	{
		int levelSize = nodeQueue.size();
		for (int i = 0; i < levelSize; ++i)
		{
			Node *current = nodeQueue.front();
			nodeQueue.pop();
			cout << current->data << " ";
			if (current->left)
				nodeQueue.push(current->left);
			if (current->right)
				nodeQueue.push(current->right);
		}
		cout << endl;
	}
}
/*
void nodeInLevel(Node* root, int level) {
	if (root) {
		if (level == 1) {
			cout << root->data << " ";
		}
		nodeInLevel(root->left, level - 1);
		nodeInLevel(root->right, level - 1);
	}
}

void levelOrder(Node* root) {
	int h = height(root);
	for (int i = 1; i <= h; i++) {
		nodeInLevel(root, i);
		cout << endl;
	}
}
*/

Node* dfsSearch(Node* root, int x) {
	if (root == NULL) return NULL;
	if (root->data == x) return root;
	Node* left = dfsSearch(root->left, x), * right = dfsSearch(root->right, x);
	if (left) return left;
	if (right) return right;
	return NULL;
}

Node* bfsSearch(Node* root, int key) {
	queue<Node*> q;
	q.push(root);
	while (!q.empty()) {
		Node* node = q.front();
		if (node->data == key)
			return node;
		if (node->left)
			q.push(node->left);
		if (node->right)
			q.push(node->right);
		q.pop();
	}
	return NULL;
}

Node* fatherNode(Node* root, Node* node) {
	queue<Node*> q;
	if (root == node) return NULL;
	q.push(root);
	while (!q.empty()) {
		Node* top = q.front();
		if (top == NULL)
			return NULL;
		if (top->left == node)
			return top;
		if (top->right == node)
			return top;
		if (top->left)
			q.push(top->left);
		if (top->right)
			q.push(top->right);
		q.pop();
	}
	return NULL;
}

Node* subtreeFirst(Node* node) {
	if (node->left) return subtreeFirst(node->left);
	return node;
}

Node* subtreeLast(Node* node) {
	if (node->right) return subtreeLast(node->right);
	return node;
}

Node* successor(Node* root, Node* node) {
	//Return node after this node in in-order traversal
	if (node->right) return subtreeFirst(node->right);
	Node* fNode = fatherNode(root, node);
	while (node != subtreeLast(fNode->left)) {
		fNode = fatherNode(root, fNode);
	}
	return fNode;
}

Node* predecessor(Node* root, Node* node) {
	//Return node before this node in in-order traversal
	if (node->left) return subtreeLast(node->left);
	Node* fNode = fatherNode(root, node);
	while (node != subtreeFirst(fNode->right)) {
		fNode = fatherNode(root, fNode);
	}
	return fNode;
}

void insertAfter(Node* root, Node* bNode, Node* node) {
	//insert node after bNode
	if (!(bNode->right)) {
		bNode->right = node;
		return;
	}
	subtreeFirst(bNode->right)->left = node;
}

void insertBefore(Node* root, Node* aNode, Node* node) {
	//insert node before aNode
	if (!(aNode->left)) {
		aNode->left = node;
		return;
	}
	subtreeLast(aNode->left)->right = node;
}

void build(Node*& root, int array[], int start, int end) {
	if (start > end) return;
	if (!root) root = new Node();
	int mid = (start + end) / 2;
	root->data = array[mid];
	build(root->left, array, start, mid - 1);
	build(root->right, array, mid + 1, end);
}