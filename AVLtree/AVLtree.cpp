#include<stdio.h>
#include<stdio.h>
#include<string>
#include<string.h>
#include<time.h>
#define STRING_MAX_LENGHT 50
#define ALLOCATION_ERROR "\r\nDoslo je do greske prilikom alokacije memorije!"

typedef struct _stablo* Stablo;
typedef struct _stablo {
	int key;
	int height;
	Stablo left;
	Stablo right;
}Tree;

int GetMax(int a, int b);
int GetHeight(Stablo root);
Stablo CreateNewNode(int key);
Stablo RightRotate(Stablo root);
Stablo LeftRotate(Stablo root);
Stablo InsertNode(Stablo root, int key);
Stablo DeleteNode(Stablo root, int key);
Stablo GetMin(Stablo root);
int GetBalance(Stablo root);
int PreOrderTraversal(Stablo root);

int main(int argc, char *argv[]) {
	Stablo root = NULL;

	root = InsertNode(root, 10);
	root = InsertNode(root, 20);
	root = InsertNode(root, 30);
	root = InsertNode(root, 40);
	root = InsertNode(root, 50);
	root = InsertNode(root, 25);

	printf("\r\nPreOrder traversal: \r\n");
	PreOrderTraversal(root);

	root = DeleteNode(root, 30);
	root = DeleteNode(root, 25);
	root = DeleteNode(root, 10);
	printf("\r\nPreOrder traversal after deletion: \r\n");
	PreOrderTraversal(root);

	return 0;
}
int GetMax(int a, int b) {
	if (a > b)
		return a;
	return b;
}
int GetHeight(Stablo root) {
	if (root == NULL)
		return 0;
	return root->height;
}
Stablo CreateNewNode(int key) {
	Stablo newNode;
	newNode = (Stablo)malloc(sizeof(Tree));
	if (newNode == NULL)
		printf(ALLOCATION_ERROR);
	else
	{
		newNode->key = key;
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->height = 1; //upisan je element u root pa je dubina stabla 1
	}
	return newNode;
}
Stablo RightRotate(Stablo y) {
	Stablo x = y->left;
	Stablo T2 = x->right;
	//rotacija
	x->right = y;
	y->left = T2;
	//update heights
	y->height = GetMax(GetHeight(y->left), GetHeight(y->right)) + 1;
	x->height = GetMax(GetHeight(x->left), GetHeight(x->right)) + 1;
	//return new root
	return x;
}
Stablo LeftRotate(Stablo x) {
	Stablo y = x->right;
	Stablo T2 = y->left;
	//rotacija
	y->left = x;
	x->right = T2;
	//update heights
	x->height = GetMax(GetHeight(x->left), GetHeight(x->right)) + 1;
	y->height = GetMax(GetHeight(y->left), GetHeight(y->right)) + 1;
	//return new root
	return y;
}
Stablo InsertNode(Stablo root, int key) {
	//perform normal BST insert
	if (root == NULL)
		return CreateNewNode(key);
	if (key < root->key)
		root->left = InsertNode(root->left, key);
	else if (key > root->key)
		root->right = InsertNode(root->right, key);
	else //jednaki kljucevi nisu dopusteni u BST
		return root;
	//update heigth
	root->height = 1 + GetMax(GetHeight(root->left),GetHeight(root->right)); //1 jer je root vec upisan
	int balance = GetBalance(root); //razlika u visini izmedu lijevog i desnog stabla, vazno da znamo je li stablo ostalo balansirano nakon umetanja el.
	//ako stablo nije balansirano moguca su 4 slucaja
	if (balance > 1 && key < root->left->key) //Left Left Case
		return RightRotate(root);
	if (balance < -1 && key > root->right->key) //Right Right Case
		return LeftRotate(root);
	if (balance > 1 && key > root->left->key) { //Left Right Case
		root->left = LeftRotate(root->left);
		return RightRotate(root);
	}
	if (balance < -1 && key < root->right->key) { //Right Left Case
		root->right = RightRotate(root->right);
		return LeftRotate(root);
	}
	return root; //nepromijenjeni pokazivac na root
}
Stablo GetMin(Stablo root) {
	Stablo current = root;
	while (current->left != NULL)
		current = current->left; //ajde skroz lijevo jer je tu najmanji element
	return current;
}
Stablo DeleteNode(Stablo root, int key) {
	//1. perform standard BST delete
	if (root == NULL)
		return root;
	// If the key to be deleted is smaller than the root's key, then it lies in left subtree 
	if (key < root->key)
		root->left = DeleteNode(root->left, key);
	// If the key to be deleted is greater than the root's key, then it lies in right subtree 
	else if (key>root->key)
		root->right = DeleteNode(root->right, key);
	// if key is same as root's key, then This is the node to be deleted 
	else
	{
		// node with only one child or no child 
		if ((root->left==NULL) || (root->right==NULL))
		{
			Stablo temp = root->left ? root->left : root->right;
			// No child case 
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else // One child case 
				*root = *temp; // Copy the contents of the non-empty child 
			free(temp);
		}
		else
		{
			// node with two children: Get the inorder successor (smallest in the right subtree) 
			Stablo temp = GetMin(root->right);
			root->key = temp->key; // Copy the inorder successor's data to this node 
			root->right = DeleteNode(root->right, temp->key); // Delete the inorder successor 
		}
	}
	if (root == NULL) // If the tree had only one node then return 
		return root;
	// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
	root->height = 1 + GetMax(GetHeight(root->left), GetHeight(root->right));
	// STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether this node became unbalanced) 
	int balance = GetBalance(root);
	// If this node becomes unbalanced, then there are 4 cases
	if (balance > 1 && GetBalance(root->left) >= 0)
		return RightRotate(root);
	if (balance < -1 && GetBalance(root->right) <= 0)
		return LeftRotate(root);
	if (balance>1 && GetBalance(root->left)<0)
	{
		root->left = LeftRotate(root->left);
		return RightRotate(root);
	}
	if (balance<-1 && GetBalance(root->right)>0)
	{
		root->right = RightRotate(root->right);
		return LeftRotate(root);
	}
	return root;
}
int GetBalance(Stablo root) {
	if (root == NULL)
		return 0;
	return GetHeight(root->left) - GetHeight(root->right);
}
int PreOrderTraversal(Stablo root) {
	if (root!=NULL)
	{
		printf(" %d\r\n", root->key);
		PreOrderTraversal(root->left);
		PreOrderTraversal(root->right);
	}
	return 0;
}