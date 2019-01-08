#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#define N 100
#define MIN_SIZE 100
#define MAX_SIZE 1000

int ZamjenaElemenata(int *niz, int minInd, int i);
int GetIndMinClan(int *niz, int i);
int PretraziIUmetniPoPotrebi(int *niz);
int KopirajNiz(int *nizA,int *nizB, int nizSize);
int ExchangeSort(int *niz, int size);
int SelectionSort(int *niz, int size);
int InsertionSort(int *niz, int size);
int BubbleSort(int *niz, int size);
int PrintNiz(int* niz, int size);

int main(int argc, char *argv[]) {
	int nizA[N];
	int nizB[N];
	srand((unsigned)time(NULL));
	for (int i = 0; i < N; i++) {
		nizA[i] = (rand() % (MAX_SIZE - MIN_SIZE + 1) + MIN_SIZE);
	}
	KopirajNiz(nizA, nizB, N);
	ExchangeSort(nizB, N);
	PrintNiz(nizB, N);
	return 0;
}
int PrintNiz(int* niz, int size) {
	for (int i = 0; i < size; i++) {
		printf(" %d", niz[i]);
	}
	return 0;
}
int ZamjenaElemenata(int *niz, int minInd, int i) {
	int temp;
	temp = niz[minInd];
	niz[minInd] = niz[i];
	niz[i] = temp;
	return 0;
}
int GetIndMinClan(int *niz, int i) {
	int minClan;
	for (int j = 0; j < i; j++) {
		if (niz[i] > niz[i + 1])
			minClan = niz[i];
	}
	return minClan;
}
int PretraziIUmetniPoPotrebi(int *niz) {

	return 0;
}
int KopirajNiz(int *nizA, int *nizB, int nizSize) {
	for (int i = 0; i < N; i++) {
		nizB[i] = nizA[i];
	}
	return 0;
}
int ExchangeSort(int *niz, int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if (niz[j]<niz[i])
			{
				ZamjenaElemenata(niz, i, j);
			}
		}
	}
	return 0;
}
int SelectionSort(int *niz, int size) {

	return 0;
}
int InsertionSort(int *niz, int size) {

	return 0;
}
int BubbleSort(int *niz, int size) {

	return 0;
}
