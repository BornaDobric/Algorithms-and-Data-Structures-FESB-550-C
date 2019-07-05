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
#define RAND_MIN 10
#define RAND_MAX 20

typedef struct _cvor* Position;
typedef struct _cvor {
	int brojIndexa;
	char ime[STRING_MAX_LENGTH];
	char prezime[STRING_MAX_LENGTH];
	int orderNum;
	Position next;
}Cvor;

int ReadFromList(Position head);
int PushElementInList(Position head, Position temp);
Position CreateNewElement();
int CreateNewList(Position head, Position lista);
int FindSpotForSortedInput(Position head, Position temp);
int PrintList(Position head);
int DeleteAll(Position head);
int GetRandomNumber();

int main(int argc, char *argv[]) {
	Cvor head;
	Cvor lista;
	char c = 0;
	head.next = NULL;
	lista.next = NULL;
	ReadFromList(&head);
	PrintList(head.next);
	printf("\r\nNova lista: \r\n");
	CreateNewList(&head, &lista);
	PrintList(lista.next);
	scanf(" %c", &c);
	return 0;
}

int CreateNewList(Position head, Position lista) {
	Position temp;
	while (head->next!=NULL)
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

int PushElementInList(Position head, Position temp) {
	temp->next = head->next;
	head->next = temp;
	return 0;
}

int FindSpotForSortedInput(Position head, Position temp) {
	while (head->next != NULL && _strcmpi(head->next->ime, temp->ime) > 0)
		head = head->next;
	PushElementInList(head, temp);
	return 0;
}

int ReadFromList(Position head) {
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
					FindSpotForSortedInput(head, temp);
				}
			}
		}
		fclose(fp);
	}
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
			printf(" %s %s redni broj: %d   orderNum: %d\r\n", head->ime, head->prezime, head->brojIndexa, head->orderNum);
			head = head->next;
		}
	}
	return 0;
}
