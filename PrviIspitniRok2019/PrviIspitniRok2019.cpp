#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#define EMPTY_LIST "\r\nLista je prazna!"
#define ALLOCATION_ERROR "\r\nDoslo je do greske prilikom alokacije memorije!"
#define RAND_MIN 2
#define RAND_MAX 15
#define STRING_MAX_LENGTH 50

typedef struct _cvor* Position;
typedef struct _cvor {
	char ime[STRING_MAX_LENGTH];
	char prezime[STRING_MAX_LENGTH];
	int redniBroj;
	int randBroj;
	Position next;
}Cvor;

int PrintList(Position head);
Position CreateNewElement();
int DeleteAll(Position head);
int ReadFile(Position head);
int FindSpotForSortedInput(Position head, Position temp);
int MakeSecondList(Position head, Position lista);

int main() {
	Cvor head, lista;
	head.next = NULL;
	lista.next = NULL;
	srand((unsigned)time(NULL));
	ReadFile(&head);
	printf("\r\nLista 1:\r\n");
	PrintList(head.next);
	printf("\r\n\r\n");
	MakeSecondList(&head, &lista);
	printf("\r\nLista 2:\r\n");
	PrintList(lista.next);
	DeleteAll(&head);
	return 0;
}
int ReadFile(Position head) {
	Position temp, prethodni, sljedeci, pokHead;
	char buffer[STRING_MAX_LENGTH];
	FILE *fp;
	pokHead = head;
	fp = fopen("dat.txt", "r");
	if (fp == NULL)
		printf("\r\nDoslo je do greske prilikom otvaranja datoteke!\r\n");
	else
	{
		while (!feof(fp))
		{
			temp = CreateNewElement();
			if (fgets(buffer,STRING_MAX_LENGTH,fp)!=NULL)
			{
				sscanf(buffer, " %d %s %s", &temp->redniBroj, temp->ime, temp->prezime);
				printf("\r\nUcitan student: %d %s %s %d\r\n", temp->redniBroj, temp->ime, temp->prezime, temp->randBroj);
			}
			temp->next = head->next;
			head->next = temp;
		}
		fclose(fp);
	}
	return 0;
}
Position CreateNewElement() {
	Position temp;
	temp = (Position)malloc(sizeof(Cvor));
	if (temp == NULL)
		printf(ALLOCATION_ERROR);
	else
	{
		temp->randBroj = (rand() % ((RAND_MAX - RAND_MIN + 1) + 1));
		temp->next = NULL;
	}
	return temp;
}
int FindSpotForSortedInput(Position head, Position temp) {
	while (head->next!=NULL && strcmpi(head->next->prezime, temp->prezime) < 0)
		head = head->next;
	temp->next = head->next;
	head->next = temp;
	return 0;
}
int MakeSecondList(Position head, Position lista) {
	Position temp;
	while (head->next!=NULL)
	{
		temp = CreateNewElement();
		strcpy(temp->ime, head->next->ime);
		strcpy(temp->prezime, head->next->prezime);
		temp->redniBroj = head->next->redniBroj;
		temp->randBroj = head->next->randBroj;
		FindSpotForSortedInput(lista, temp);
		head = head->next;
	}
	return 0;
}
int PrintList(Position head) {
	if (head == NULL)
		printf(EMPTY_LIST);
	else
	{
		while (head!=NULL)
		{
			printf("Student: %d. %s %s i %d.\r\n", head->redniBroj, head->ime, head->prezime, head->randBroj);
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