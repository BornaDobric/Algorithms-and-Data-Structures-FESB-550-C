#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#define STRING_MAX_LENGHT 50
#define ALLOCATION_ERROR "\r\nDoslo je do greske prilikom alokacije memorije!"

typedef struct _stablo* Stablo;
typedef struct _stablo {
	int element;
	Stablo left; //u lijevom stablu su manji elementi od roota
	Stablo right; //u desnom stablu su veci elementi od roota
}Tree;

Stablo CreateNode(int data);
Stablo FindMin(Stablo root);
Stablo Search(Stablo root, int data);
Stablo InsertNode(Stablo root, int key);
Stablo DeleteNode(Stablo root, int key);
int InorderTraversalAkaPrintTree(Stablo root);

int main() {
	Stablo root = NULL;
	root = InsertNode(root, 50); //prvi element u stablu pa ga moramo spremiti u root
	InsertNode(root, 70);
	InsertNode(root, 20);
	InsertNode(root, 40);
	InsertNode(root, 30);
	InsertNode(root, 60);
	InsertNode(root, 60);
	InsertNode(root, 110);
	InsertNode(root, 150);
	InsertNode(root, 10);
	InsertNode(root, 80);

	printf("\r\nInorder traversal of tree: \r\n");
	InorderTraversalAkaPrintTree(root);

	printf("\r\nDelete 20: ");
	root = DeleteNode(root, 20);
	printf("\r\nInorder traversal of modified tree: \r\n");
	InorderTraversalAkaPrintTree(root);

	printf("\r\nDelete 80: ");
	root = DeleteNode(root, 80);
	printf("\r\nInorder traversal of modified tree: \r\n");
	InorderTraversalAkaPrintTree(root);

	printf("\r\nDelete 40: ");
	root = DeleteNode(root, 40);
	printf("\r\nInorder traversal of modified tree: \r\n");
	InorderTraversalAkaPrintTree(root);
	return 0;
}
Stablo CreateNode(int data) {
	Stablo newNode;
	newNode = (Stablo)malloc(sizeof(Tree));
	if (newNode == NULL)
		printf(ALLOCATION_ERROR);
	else
	{
		newNode->element = data;
		newNode->left = NULL; //trenutno prazno
		newNode->right = NULL; //trenutno prazno
	}
	return newNode;
}
int InorderTraversalAkaPrintTree(Stablo root) {
	if (root!=NULL)
	{
		InorderTraversalAkaPrintTree(root->left); //rekurzivna funkcija, saljemo left granu
		printf(" %d\r\n", root->element); //print element
		InorderTraversalAkaPrintTree(root->right); //rekurzivna funkcija, saljemo left granu
	}
	return 0;
}
Stablo Search(Stablo root, int key) {
	if (root == NULL || root->element == key) //ako je stablo prazno ili root element jednak kljucu kojeg trazimo
		return root; 
	if (root->element < key) //ako je element u rootu manji od kljuca
		return Search(root->right, key); //rekurzivna funkcija, salje se right jer se trazi veci
	return Search(root->left, key); //inace salji lijevi
}
Stablo InsertNode(Stablo root, int key) {
	if (root == NULL) //ako je prvi element koji upisujemo u stablo
		return CreateNode(key);
	if (key<root->element) //ako je kljuc manji od elementa upisanog u root
		root->left = InsertNode(root->left, key); //rekurzivni poziv funkcije sa slanjem lijevog stabla
	else if (key>root->element) //inace
		root->right = InsertNode(root->right, key); //salji desnu stablo u rekurzivnu funkciju
	return root; //vrati izmijenjeni root
}
Stablo FindMin(Stablo root) {
	Stablo current = root;
	while (current->left != NULL) //idemo u lijevo stablo jer se trazi najmanji element
		current = current->left;
	return current;
}
Stablo DeleteNode(Stablo root, int key) {
	if (root == NULL)
		return root;
	if (key < root->element)
		root->left = DeleteNode(root->left, key);
	else if (key>root->element)
		root->right = DeleteNode(root->right, key);
	else
	{
		if (root->left==NULL)
		{
			Stablo temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right==NULL)
		{
			Stablo temp = root->left;
			free(root);
			return temp;
		}
		Stablo temp = FindMin(root->right);
		root->element = temp->element;
		root->right = DeleteNode(root->right, temp->element);
	}
	return root;
}