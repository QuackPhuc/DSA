#include <iostream>
#include <queue>
using namespace std;
#define Build(root, array, size) build(root, array, 0, size - 1);
// Get Balance factor of node N
int getBalance(Node *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

// Recursive function to insert a key
// in the subtree rooted with node and
// returns the new root of the subtree.
Node *insert(Node *node, int key)
{
	/* 1. Perform the normal BST insertion */
	if (node == NULL)
		return (newNode(key));

	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);
	else // Equal keys are not allowed in BST
		return node;

	/* 2. Update height of this ancestor node */
	node->height = 1 + max(height(node->left),
						   height(node->right));

	/* 3. Get the balance factor of this ancestor
		node to check whether this node became
		unbalanced */
	int balance = getBalance(node);

	// If this node becomes unbalanced, then
	// there are 4 cases

	// Left Left Case
	if (balance > 1 && key < node->left->key)
		return rightRotate(node);

	// Right Right Case
	if (balance < -1 && key > node->right->key)
		return leftRotate(node);

	// Left Right Case
	if (balance > 1 && key > node->left->key)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// Right Left Case
	if (balance < -1 && key < node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	/* return the (unchanged) node pointer */
	return node;
}



struct Node {
	int data = NULL;
	Node* left = NULL, * right = NULL;
	int height = -1;

	Node(int key = NULL){
		data = key;
	}
};

void updateHeight(Node* node);

int height(Node* node) {
	if (!node) return 0;
	if (node->height < 0) 
	    updateHeight(node);
	return node->height;
}

void updateHeight(Node* node) {
	node->height = max(height(node->left),height(node->right)) + 1;
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

Node* leftRotate(Node* x) {
	Node* y = x->right;
	Node* T2 = y->left;
	// Perform rotate
	y->left = x;
	x->right = T2;
	// Update height
	updateHeight(x);
	updateHeight(y);
	// Return new root
	return y;
}

Node* rightRotate(Node* y) {
	Node* x = y->left;
	Node* T2 = x->right;
	// Perform rotation
	x->right = y;
	y->left = T2;
	// Update height
	updateHeight(y);
	updateHeight(x);
	// return new root
	return x;
}

Node* leftRightRotate(Node* x) {
	x->left = leftRotate(x->left);
	return rightRotate(x);
}

Node* rightLeftRotate(Node* x) {
	x->right = rightRotate(x->right);
	return leftRotate(x);
}

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

void insert(Node* &root, Node* node) {
	if (!root) root = node;
	else (height(root->left) <= height(root->right)) ? insert(root->left, node) : insert(root->right, node);

	updateHeight(root);
}

void deleteNode(Node*& root , int key) {
	Node* node = bfsSearch(root, key), * fNode, * tmp;
	//Cut the leaf
	if (!((node->left) || (node->right))) {
		fNode = fatherNode(root, node);
		if (fNode == NULL) {
			root = NULL;
			return;
		}
		if (fNode->left == node) {
			fNode->left = NULL;
			return;
		}
		fNode->right = NULL;
		return;
	}

	//swap with the predecessor and cut the leaf
	if (node->left) {
		tmp = subtreeLast(node->left);
		fNode = fatherNode(root, tmp);
		node->data = tmp->data;
		if (fNode->left == tmp) {
			fNode->left = NULL;
			return;
		}
		fNode->right = NULL;
		return;
	}

	//swap with the successor and cut the leaf
	tmp = subtreeFirst(node->right);
	fNode = fatherNode(root, tmp);
	node->data = tmp->data;
	if (fNode->left == tmp) {
		fNode->left = NULL;
		return;
	}
	fNode->right = NULL;
	return;
}

bool checkAVL(Node* root) {
	if (!root) return 1;
	if (height(root->left) < 0 || height(root->right) < 0) {
		updateHeight(root->left);
		updateHeight(root->right);
		updateHeight(root);
	}
	if (abs(height(root->left) - height(root->right)) > 1) return 0;
	return (checkAVL(root->left) && checkAVL(root->right));
}

void balance(Node* &root) {
	if (!root) return;
	if (abs(height(root->left) - height(root->right)) > 1){
		if (height(root->left) > height(root->right)) root = leftRightRotate(root);
	    else if(height(root->left) < height(root->right)) root = rightLeftRotate(root);
	}
	
	balance(root->left);
	balance(root->right);
}

void build(Node*& root, int array[], int start, int end) {
	if (start > end) return;
	if (!root) root = new Node();
	int mid = (start + end) / 2;
	root->data = array[mid];
	build(root->left, array, start, mid - 1);
	build(root->right, array, mid + 1, end);
}

struct AVLTree {
	Node* root;
	AVLTree() : root(nullptr) {}
	AVLTree(int array[], int size) {
		root = new Node();
		Build(root, array, size);
		if(!check()) Balance();
	}

	bool check(){
		return checkAVL(root);
	}

	void print(string order = "in"){
		if(order == "in") inOrder(root);
		else if(order == "post") postOrder(root);
		else if(order =="level") levelOrder(root);
		else preOrder(root);
		cout<<endl;
	}

	void UpdateHeight() {
	    queue<Node*> q;
	    q.push(root);
	    while (!q.empty()) {
		    Node* node = q.front();
		    if (node) updateHeight(node);
		    if (node->left)
		    	q.push(node->left);
		    if (node->right)
			    q.push(node->right);
		    q.pop();
	    }
	}

	void Balance(){
		balance(root);
	}

	Node* search(int key){
		return bfsSearch(root, key);
	}

	void insertNode(Node* node) {
		insert(root, node);
		UpdateHeight();
		Balance();
	}

	void remove(int key) {
		deleteNode(root, key);
		UpdateHeight();
		Balance();
	}
};

int main() {
	int array[10] = { 1,2,3,4,5,6,7,8,9,10 };
	AVLTree tree = AVLTree(array, 10);
	tree.print("level");
	Node* n = new Node(20);
	tree.insertNode(n);
	tree.print("level");
	tree.remove(3);
	tree.print("level");
}
/**/