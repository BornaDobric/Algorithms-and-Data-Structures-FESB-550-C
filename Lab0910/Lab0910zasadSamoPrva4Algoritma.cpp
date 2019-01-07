#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#include<windows.h>
#define STRING_MAX_LENGHT 50

int PrintArray(int *niz, int lenght);
int CallByNumberOfElements(int broj);
int CopyNiz(int *, int *, int lenght);
int GenerateNiz(int *A, int broj);
int ExchangeSort(int *niz, int lenght);
int SelectionSort(int *niz, int lenght);
int InsertionSort(int *niz, int lenght);
int BubbleSort(int *niz, int lenght);
int ShellSort(int *, int);
int QuickSort(int *, int , int);
int Partition(int *, int, int);

int main(int argc, char *argv[]) {
	CallByNumberOfElements(100); //salje se broj elemenata
	printf("\r\n\r\n");
	CallByNumberOfElements(1000);
	printf("\r\n\r\n");
	CallByNumberOfElements(10000);
	printf("\r\n\r\n");
	CallByNumberOfElements(100000);
	printf("\r\n\r\n");
	return 0;
}
int PrintArray(int *niz, int lenght) {
	for (int i = 0; i < lenght; i++) {
		printf(" %d", niz[i]);
	}
	return 0;
}
int CallByNumberOfElements(int broj) {
	DWORD startTime; //WORD is an unsigned 16bit integer
	DWORD endTime; //DWORD is an unsigned 32bit integer
	int *nizA;
	int *nizB;

	printf("\r\nNiz od %d elemenata: ", broj);
	nizA = (int*)malloc(sizeof(int)*broj); //dinamicki alociraj memoriju za niz
	GenerateNiz(nizA, broj);

	nizB = (int*)malloc(sizeof(int)*broj); //dinamicki alociraj memoriju za niz
	CopyNiz(nizA, nizB, broj); //kopija niza A  u niz B
	startTime = GetTickCount(); //GetTickCount() function returns the number of milliseconds that elapsed since the system start
	ExchangeSort(nizB, broj);
	endTime = GetTickCount();
	printf("\r\nExchangeSort: %d\r\n", (int)(endTime - startTime)); //razlika izmedu vremena pocetka i kraja sortiranja
	//PrintArray(nizB, broj);
	free(nizB); //oslobodi memoriju

	nizB = (int*)malloc(sizeof(int)*broj);
	CopyNiz(nizA, nizB, broj);
	startTime = GetTickCount();
	SelectionSort(nizB, broj);
	endTime = GetTickCount();
	printf("\r\nSelectionSort: %d\r\n", (int)(endTime - startTime));
	//PrintArray(nizB, broj);
	free(nizB);
	
	nizB = (int*)malloc(sizeof(int)*broj);
	CopyNiz(nizA, nizB, broj);
	startTime = GetTickCount();
	InsertionSort(nizB, broj);
	endTime = GetTickCount();
	printf("\r\nInsertionSort: %d\r\n", (int)(endTime - startTime));
	//PrintArray(nizB, broj);
	free(nizB);

	nizB = (int*)malloc(sizeof(int)*broj);
	CopyNiz(nizA, nizB, broj);
	startTime = GetTickCount();
	BubbleSort(nizB, broj);
	endTime = GetTickCount();
	printf("\r\nBubbleSort: %d\r\n", (int)(endTime - startTime));
	//PrintArray(nizB, broj);
	free(nizB); 

	/*nizB = (int*)malloc(sizeof(int)*broj);
	CopyNiz(nizA, nizB, broj);
	startTime = GetTickCount();
	ShellSort(nizB, broj);
	endTime = GetTickCount();
	printf("\r\nShellSort: %d\r\n", (int)(endTime - startTime));
	PrintArray(nizB, broj);
	free(nizB);

	nizB = (int*)malloc(sizeof(int)*broj);
	CopyNiz(nizA, nizB, broj);
	startTime = GetTickCount();
	QuickSort(nizB, 0, broj);
	endTime = GetTickCount();
	printf("\r\nQuickSort: %d\r\n", (int)(endTime - startTime));
	PrintArray(nizB, broj);
	free(nizB);
	*/
	return 0;
}
int CopyNiz(int *A, int *B, int broj) {
	for (int i = 0; i < broj; i++)
		B[i] = A[i]; //spremaj element niza A u niz B
	return 0;
}
int GenerateNiz(int *A, int broj) {
	srand((unsigned)time(NULL)); //za random broj
	for (int i = 0; i < broj; i++)
		A[i] = rand(); //dodijeli random broj citavom nizu
	return 0;
}
int ExchangeSort(int *niz, int lenght) {
	int i, j;
	int temp; //sadrzavat ce trenutnu varijablu
	for (i = 0; i < lenght - 1; i++) { //dvi petlje za usporedivanje usporednih vrijednosti
		for (j = (i + 1); j < lenght; j++) {
			if (niz[i]>niz[j]) //descending order
			{
				temp = niz[i];
				niz[i] = niz[j]; //swap
				niz[j] = temp;
			}
		}
	}
	return 0;
}
int SelectionSort(int *niz, int lenght) { //selection sort algorithm sorts an array by repeatedly finding the minimum element (considering ascending order) from unsorted part and putting it at the beginning
	int i, j, first, temp;
	for (i = 0; i <lenght-1; i++) {
		first = i;
		for (j = first+1; j <lenght; j++) {
			if (niz[j] < niz[first])
				first = j;
		}
		temp = niz[first];
		niz[first] = niz[i];
		niz[i] = temp;
	}
	return 0;
}
int InsertionSort(int *niz, int lenght) {
	int i, j, key;
	for (j = 1; j < lenght; j++)    // Start with 1 (not 0)
	{
		key = niz[j];
		for (i = j - 1; (i >= 0) && (niz[i] > key); i--)   // Smaller values move up
		{
			niz[i + 1] = niz[i];
		}
		niz[i + 1] = key;    //Put key into its proper location
	}
	return 0;
}
int BubbleSort(int *niz, int lenght) {
	int i, j, flag = 1;    // set flag to 1 to start first pass
	int temp;             // holding variable
	for (i = 1; (i <= lenght) && flag; i++)
	{
		flag = 0;
		for (j = 0; j < (lenght - 1); j++)
		{
			if (niz[j + 1] < niz[j])      // ascending order simply changes to <
			{
				temp = niz[j];             // swap elements
				niz[j] = niz[j + 1];
				niz[j + 1] = temp;
				flag = 1;               // indicates that a swap occurred.
			}
		}
	}
	return 0;
}
int ShellSort(int *, int) {

	return 0;
}
int QuickSort(int *, int, int) {

	return 0;
}
int Partition(int *, int, int) {

	return 0;
}