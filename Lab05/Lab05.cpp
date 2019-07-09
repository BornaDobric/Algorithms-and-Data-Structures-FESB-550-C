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

typedef struct _cvor* Position;
typedef struct _cvor {
	int element;
	Position next;
}Cvor;

int ReadFromFile(Position head, const char *filename);
int PushElementInList(Position head, int broj);
int GetUnija(Position unija, Position lista1, Position lista2);
int GetPresjek(Position presjek, Position lista1, Position lista2);
Position CreateNewElement(int broj);
int PrintList(Position head);
int DeleteAll(Position head);

int main(int argc, char *argv[]) {
	Cvor lista1;
	Cvor lista2;
	Cvor unija;
	Cvor presjek;
	char c = 0;
	lista1.next = NULL;
	lista2.next = NULL;
	unija.next = NULL;
	presjek.next = NULL;

	printf("\r\nLista 1: \r\n");
	ReadFromFile(&lista1, "lista1.txt");
	PrintList(lista1.next);
	printf("\r\n--------------------------\r\n");

	printf("\r\nLista 2: \r\n");
	ReadFromFile(&lista2, "lista2.txt");
	PrintList(lista2.next);
	printf("\r\n--------------------------\r\n");

	printf("\r\nUnija: \r\n");
	GetUnija(&unija, &lista1, &lista2);
	PrintList(unija.next);
	printf("\r\n--------------------------\r\n");

	printf("\r\nPresjek: \r\n");
	GetPresjek(&presjek, &lista1, &lista2);
	PrintList(presjek.next);
	printf("\r\n--------------------------\r\n");


	DeleteAll(&lista1);
	DeleteAll(&lista2);
	DeleteAll(&unija);
	DeleteAll(&presjek);
	scanf(" %c", &c);
	return 0;
}

int GetPresjek(Position presjek, Position lista1, Position lista2) {
	Position temp1;
	Position temp2;
	temp1 = lista1->next;
	temp2 = lista2->next;

	while (temp1->next != NULL && temp2->next != NULL)
	{
		if (temp1->element == temp2->element)
		{	//ako su jednaki pisi ih u presjek
			PushElementInList(presjek, temp1->element);
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		else if (temp1->element > temp2->element)
		{	//brokvaj
			temp2 = temp2->next;
		}
		else
		{	//brokvaj
			temp1 = temp1->next;
		}
	}
	return 0;
}

int GetUnija(Position unija, Position lista1, Position lista2) {
	Position temp1;
	Position temp2;
	temp1 = lista1->next;
	temp2 = lista2->next;
	while (temp1!=NULL && temp2!=NULL)
	{
		if (temp1->element == temp2->element)
		{
			PushElementInList(unija, temp1->element);
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		else if (temp1->element > temp2->element)
		{
			PushElementInList(unija, temp2->element);
			temp2 = temp2->next;
		}
		else
		{
			PushElementInList(unija, temp1->element);
			temp1 = temp1->next;
		}
	}
	while (temp1!=NULL)
	{
		PushElementInList(unija, temp1->element);
		temp1 = temp1->next;
	}
	while (temp2 != NULL)
	{
		PushElementInList(unija, temp2->element);
		temp2 = temp2->next;
	}
	return 0;
}

Position CreateNewElement(int broj) {
	Position temp;
	temp = (Position)malloc(sizeof(Cvor));
	if (temp == NULL)
		return NULL;
	else {
		temp->element = broj;
		temp->next = NULL;
	}
	return temp;
}

int PushElementInList(Position head, int broj) {
	Position temp;
	temp = CreateNewElement(broj);
	if (temp == NULL)
		printf(ALLOCATION_ERROR);
	else
	{
		while (head->next != NULL)
			head = head->next;
		temp->next = head->next;
		head->next = temp;
	}
	return 0;
}

int ReadFromFile(Position head, const char *filename) {
	FILE *fp;
	Position temp;
	char buffer[STRING_MAX_LENGTH];
	int broj = 0;
	fp = fopen(filename, "r");
	if (fp == NULL)
		printf(FILE_OPEN_ERROR);
	else
	{
		while (!feof(fp))
		{
			fscanf(fp, " %d", &broj);
			PushElementInList(head, broj);
		}
		fclose(fp);
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
			printf(" %d\r\n", head->element);
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
