#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#define STRING_MAX_LENGHT 50
#define FILE_OPEN_ERROR "\r\nDoslo je do greske prilikom otvaranja datoteke <%s>!"
#define ALLOCATION_ERROR "\r\nDoslo je do greske prilikom alokacije memorije!"
#define EMPTY_LIST "\r\nLista je prazna!"
#define FILE_NAME "drzave.txt"

typedef struct _grad* PositionGrad;
typedef struct _grad {
	char nazivGrada[STRING_MAX_LENGHT];
	PositionGrad next;
}Grad;

typedef struct _drzava* PositionDrzava;
typedef struct _drzava {
	char nazivDrzave[STRING_MAX_LENGHT];
	PositionDrzava nextDrzava;
	PositionGrad nextGrad;
}Drzava;

int ReadFromFile(PositionDrzava head);
int InsertElementInList(PositionDrzava head, PositionDrzava tempDrzava);
int FindPlaceForSortedInput(PositionDrzava head, PositionDrzava tempDrzava);
int PrintList(PositionDrzava head);
int DeleteAll(PositionDrzava head);

int main(int argc, char *argv[]) {
	Drzava drzava;
	Grad grad;
	drzava.nextDrzava = NULL;
	grad.next = NULL;

	ReadFromFile(&drzava);
	PrintList(drzava.nextDrzava);
	printf("\r\n");
	DeleteAll(&drzava);
	return 0;
}
int ReadFromFile(PositionDrzava head) {
	FILE *fp;
	PositionDrzava tempDrzava;
	char buffer[STRING_MAX_LENGHT];
	fp = fopen(FILE_NAME, "r");
	if (fp == NULL)
		printf(FILE_OPEN_ERROR);
	else
	{
		while (!feof(fp))
		{
			tempDrzava = (PositionDrzava)malloc(sizeof(Drzava));
			if (tempDrzava == NULL)
				printf(ALLOCATION_ERROR);
			else
			{
				fscanf(fp, " %s", tempDrzava->nazivDrzave);
				FindPlaceForSortedInput(head, tempDrzava);
			}
		}
		fclose(fp);
	}
	return 0;
}
int InsertElementInList(PositionDrzava head, PositionDrzava tempDrzava) {
	tempDrzava->nextDrzava = head->nextDrzava;
	head->nextDrzava = tempDrzava;
	return 0;
}
int FindPlaceForSortedInput(PositionDrzava head, PositionDrzava tempDrzava) {
	while (head->nextDrzava != NULL && strcmpi(head->nextDrzava->nazivDrzave, tempDrzava->nazivDrzave) < 0)
		head = head->nextDrzava;
	InsertElementInList(head, tempDrzava);
	return 0;
}
int PrintList(PositionDrzava head) {
	if (head == NULL)
		printf(EMPTY_LIST);
	else
	{
		while (head!=NULL)
		{
			printf(" %s\r\n", head->nazivDrzave);
			head = head->nextDrzava;
		}
	}
	return 0;
}
int DeleteAll(PositionDrzava head) {
	PositionDrzava temp;
	printf("\r\nBrisanje liste...");
	while (head->nextDrzava!=NULL)
	{
		temp = head->nextDrzava;
		head->nextDrzava = temp->nextDrzava;
		free(temp);
	}
	printf("\r\nLista uspjesno izbrisana!\r\n");
	return 0;
}
