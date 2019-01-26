#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#define ALLOCATION_ERROR "\r\nDoslo je do greske prilikom aloakcije memorije!"
#define STRING_MAX_LENGHT 50

typedef struct _stablo* Stablo;
typedef struct _stablo {
	int data;
	Stablo left;
	Stablo right;
}Tree;

Stablo CreateNewNode(int data);
Stablo FindMin(Stablo root);
Stablo Search(Stablo root, int key);
Stablo InsertNode(Stablo root, int key);
Stablo DeleteNode(Stablo root, int key);
int InOrderTraversal(Stablo root);
int PreOrderTraversal(Stablo root);
int PostOrderTraversal(Stablo root);
int LeverOrderTraversal(Stablo root);
int PrintGivenLevel(Stablo root, int level);
int HeightOfTree(Stablo root);
int DeleteTree(Stablo root);

int main(int argc, char *argv[]) {
	Stablo root = NULL; //jer ce na pocetku imati samo root a ne i lijevo i desno stablo
	root = InsertNode(root, 20);
	InsertNode(root, 130);
	InsertNode(root, 110);
	InsertNode(root, 90);
	InsertNode(root, 70);
	InsertNode(root, 50);
	InsertNode(root, 190);

	printf("\r\nInorder traversal: \r\n");
	InOrderTraversal(root);
	printf("\r\nPreorder traversal: \r\n");
	PreOrderTraversal(root);
	printf("\r\nPostorder traversal: \r\n");
	PostOrderTraversal(root);
	printf("\r\nLevel order traversal: \r\n");
	LeverOrderTraversal(root);

	DeleteTree(root);
	printf("\r\nStablo uspjesno izbrisano!\r\n");
	return 0;
}
Stablo CreateNewNode(int data) {
	Stablo newNode;
	newNode = (Stablo)malloc(sizeof(Tree));
	if (newNode == NULL)
		printf(ALLOCATION_ERROR);
	else
	{
		newNode->data = data;
		newNode->left = NULL;
		newNode->right = NULL;
	}
	return newNode;
}
Stablo FindMin(Stablo root) {
	Stablo current = root;
	while (current->left != NULL) //trazi se najmanji element pa idemo u lijevo stablo
		current = current->left; //iduci element u lijevom stablu
	return current; //vrati poziciju najmanjeg elementa
}
Stablo Search(Stablo root, int key) {
	if (root == NULL || root->data == key)
		return root;
	if (root->data < key)
		return Search(root->right, key);
	return Search(root->left, key);
}
Stablo InsertNode(Stablo root, int key) {
	if (root == NULL)
		return CreateNewNode(key);
	if (key < root->data)
		root->left = InsertNode(root->left, key);
	else if (key > root->data)
		root->right = InsertNode(root->right, key);
	return root;
}
Stablo DeleteNode(Stablo root, int key) {
	if (root == NULL) //ako je stablo vec prazno
		return root;
	if (key < root->data)
		root->left = InsertNode(root->left, key); //trazi u lijevom stablu
	else if (key > root->data)
		root->right = InsertNode(root->right, key); //trazi u desnom stablu
	else //ako je kljuc jednak elementu
	{
		if (root->left==NULL) //ako je jedino dijete izbrisi ga i uzmi desni element
		{
			Stablo temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right==NULL) //ako je jedino dijete izbrisi ga i uzmi lijevi element
		{
			Stablo temp = root->left;
			free(root);
			return temp;
		}
		Stablo temp = FindMin(root->right); //pronadi najblizi veci broj od onog koji se brise
		root->data = temp->data;
		root->right = DeleteNode(root->right, temp->data);
	}
	return root;
}
int InOrderTraversal(Stablo root) {
	if (root!=NULL)
	{
		InOrderTraversal(root->left); //rekurzivni poziv funkcije sa lijevim stablom
		printf(" %d\r\n", root->data); //ispis elementa
		InOrderTraversal(root->right); //rekurzivni poziv funkcije sa desnim stablom
	}
	return 0;
}
int PreOrderTraversal(Stablo root) {
	if (root != NULL)
	{
		printf(" %d\r\n", root->data); //ispis elementa
		InOrderTraversal(root->left); //rekurzivni poziv funkcije sa lijevim stablom
		InOrderTraversal(root->right); //rekurzivni poziv funkcije sa desnim stablom
	}
	return 0;
}
int PostOrderTraversal(Stablo root) {
	if (root != NULL)
	{
		InOrderTraversal(root->left); //rekurzivni poziv funkcije sa lijevim stablom
		InOrderTraversal(root->right); //rekurzivni poziv funkcije sa desnim stablom
		printf(" %d\r\n", root->data); //ispis elementa
	}
	return 0;
}
int HeightOfTree(Stablo root) {
	if (root == NULL)
		return 0;
	int leftHeight = HeightOfTree(root->left); //rekurzivni poziv funkcije sa lijevim stablom
	int rightHeight = HeightOfTree(root->right); //rekurzivni poziv funkcije sa desnim stablom
	if (leftHeight > rightHeight) //vrati vecu dubinu stabla
		return leftHeight + 1;
	return rightHeight + 1; //+1 jer je dubina praznog stabla -1 a roota 0
}
int PrintGivenLevel(Stablo root, int level) {
	if (root == NULL)
		return 0;
	if (level == 0) //to je onda root element
		printf(" %d\r\n", root->data);
	else if (level>0)
	{
		PrintGivenLevel(root->left, level - 1); //rekurzija
		PrintGivenLevel(root->right, level - 1); //rekurzija
	}
	return 0;
}
int LeverOrderTraversal(Stablo root) {
	int height = HeightOfTree(root);
	for (int i = 0; i < height; i++) {
		PrintGivenLevel(root, i); //i je level koji cemo ispisivati
	}
	return 0;
}
int DeleteTree(Stablo root) {
	if (root == NULL)
		return 0;
	DeleteTree(root->left); //zapravo se radi postorder traversal, brisi lijevo stablo
	DeleteTree(root->right); //zapravo se radi postorder traversal, brisi desno stablo
	printf("\r\nDeleting node: %d\r\n", root->data);
	free(root); //brisi root element
	return 0;
}
