#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#define ALLOCATION_ERROR "\r\nDoslo je do greske prilikom alokacije memorije!"
#define EMPTY_LIST "\r\nLista je prazna!"
#define FILE_OPEN_ERROR "\r\nDoslo je do greske prilikom otvaranja datoteke!"
#define STRING_MAX_LENGTH 50
#define FILENAME "studenti2702.txt"
#define RAND_MIN 1
#define RAND_MAX 3

typedef struct _cvor* Position;
typedef struct _cvor {
	int orderNum;
	int brojac = 0;
	char sifra[STRING_MAX_LENGTH];
	char ime[STRING_MAX_LENGTH];
	char prezime[STRING_MAX_LENGTH];
	Position next;
}Cvor;

int ReadFromFile(Position head);
int PushElementInList(Position head, Position temp);
int FindSpotForSortedInput(Position head, Position temp);
Position CreateNewElement();
int GetRandomNumber();
int PrintList(Position head);
int DeleteAll(Position head);

int main() {
	Cvor head;
	char c = 0;
	head.next = NULL;
	srand((unsigned)time(NULL));

	ReadFromFile(&head);
	PrintList(head.next);

	scanf(" %c", &c);
	return 0;
}

int ReadFromFile(Position head) {
	FILE *fp;
	Position temp;
	char buffer[STRING_MAX_LENGTH];
	fp = fopen(FILENAME, "r");
	if (fp == NULL)
		printf(FILE_OPEN_ERROR);
	else
	{
		while (!feof(fp))
		{
			temp = CreateNewElement();
			if (temp == NULL)
				printf(ALLOCATION_ERROR);
			else
			{
				if (fgets(buffer,STRING_MAX_LENGTH,fp)!=NULL)
				{
					sscanf(buffer, " %s %s %s", temp->sifra, temp->ime, temp->prezime);
					FindSpotForSortedInput(head, temp);
				}
			}
		}
		fclose(fp);
	}
	return 0;
}

int PushElementInList(Position head, Position temp) {
	temp->next = head->next;
	head->next = temp;
	return 0;
}

int FindSpotForSortedInput(Position head, Position temp) {
	while (head->next != NULL && head->next->orderNum > temp->orderNum)
		head = head->next;
	if ((head->next != NULL) && (head->next->orderNum == temp->orderNum) && (_strcmpi(head->next->sifra, temp->sifra) == 0))
	{
		if (head->next->brojac < 0)
			head->next->brojac = 2;
		else
			head->next->brojac++;
	}
	else
		PushElementInList(head, temp);
	return 0;
}

Position CreateNewElement() {
	Position temp;
	temp = (Position)malloc(sizeof(Cvor));
	if (temp == NULL)
		printf(ALLOCATION_ERROR);
	else
	{
		temp->orderNum = GetRandomNumber();
		temp->next = NULL;
	}
	return temp;
}

int GetRandomNumber() {
	int broj = (rand() % (RAND_MAX - RAND_MIN + 1) + RAND_MIN);
	return broj;
}

int PrintList(Position head) {
	if (head == NULL)
		printf(EMPTY_LIST);
	else
	{
		while (head!=NULL)
		{
			if (head->brojac > 0)
				printf(" %s %s %s     prioritet: %d      brojac: %d\r\n", head->sifra, head->ime, head->prezime, head->orderNum, head->brojac);
			else
				printf(" %s %s %s     prioritet: %d\r\n", head->sifra, head->ime, head->prezime, head->orderNum);
			head = head->next;
		}
	}
	return 0;
}

int DeleteAll(Position head) {
	Position temp;
	printf("\r\nBrisanje liste...");
	while (head->next!=NULL)
	{
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
	printf("\r\nLista uspjesno izbrisana!\r\n");
	return 0;
}
