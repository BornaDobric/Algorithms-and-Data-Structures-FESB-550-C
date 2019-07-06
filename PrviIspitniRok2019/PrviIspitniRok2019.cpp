#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#define ALLOCATION_ERROR "\r\nDoslo je do greske prilikom alokacije memorije!"
#define EMPTY_LIST "\r\nLista je prazna!"
#define FILE_OPEN_ERROR "\r\nDoslo je do greske prilikom otvaranja datoteke."
#define STRING_MAX_LENGTH 50
#define FILENAME "file.txt"
#define RAND_MIN 1
#define RAND_MAX 5

typedef struct _cvor* Position;
typedef struct _cvor {
	int brojIndexa;
	int orderNum;
	char ime[STRING_MAX_LENGTH];
	char prezime[STRING_MAX_LENGTH];
	Position next;
}Cvor;

int ReadFromFile(Position head);
int PushElementInList(Position head, Position temp);
int FindSpotForSortedInput(Position head, Position temp);
Position CreateNewElement();
int MakeNewListWithSortedInput(Position head, Position lista);
int GetRandomNumber();
int PrintList(Position head);
int DeleteAll(Position head);

int main(int argc, char *argv[]) {
	Cvor head;
	Cvor lista;
	char c = 0;
	srand((unsigned)time(NULL));
	head.next = NULL;
	lista.next = NULL;

	ReadFromFile(&head);
	PrintList(head.next);

	printf("\r\n---------------------------\r\nNova lista:\r\n");
	MakeNewListWithSortedInput(&head, &lista);
	PrintList(lista.next);
	scanf(" %c", &c);
	return 0;
}

int MakeNewListWithSortedInput(Position head, Position lista) {
	Position temp;
	while (head->next != NULL)
	{
		temp = CreateNewElement();
		if (temp == NULL)
			printf(ALLOCATION_ERROR);
		else
		{
			strcpy(temp->ime, head->next->ime);
			strcpy(temp->prezime, head->next->prezime);
			temp->brojIndexa = head->next->brojIndexa;
			temp->orderNum = head->next->orderNum;
			FindSpotForSortedInput(lista, temp);
			head = head->next;
		}
	}
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
					sscanf(buffer, " %d %s %s", &temp->brojIndexa, temp->ime, temp->prezime);
					PushElementInList(head, temp);
					head = head->next;
				}
			}
		}
		fclose(fp);
	}
	return 0;
}

int GetRandomNumber() {
	int broj = (rand() % (RAND_MAX - RAND_MIN + 1) + RAND_MIN);
	return broj;
}

int FindSpotForSortedInput(Position head, Position temp) {
	while (head->next != NULL && _strcmpi(head->next->prezime, temp->prezime) < 0)
		head = head->next;
	PushElementInList(head, temp);
	return 0;
}

int PushElementInList(Position head, Position temp) {
	temp->next = head->next;
	head->next = temp;
	return 0;
}

Position CreateNewElement() {
	Position temp;
	temp = (Position)malloc(sizeof(Cvor));
	if (temp == NULL)
		return NULL;
	else
	{
		temp->orderNum = GetRandomNumber();
		temp->next = NULL;
	}
	return temp;
}

int PrintList(Position head) {
	if (head == NULL)
		printf(EMPTY_LIST);
	else
	{
		while (head!=NULL)
		{
			printf(" %s %s %d %d\r\n", head->ime, head->prezime, head->brojIndexa, head->orderNum);
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
