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
#define FILENAME "studenti2702.txt"
#define RAND_MIN 1
#define RAND_MAX 2

typedef struct _cvor* Position;
typedef struct _cvor {
	int ocjena;
	float prosjek;
	char ime[STRING_MAX_LENGTH];
	char prezime[STRING_MAX_LENGTH];
	Position next;
}Cvor;

int ReadFromFile(Position head, const char *fileName);
int PushElementInList(Position head, Position temp);
int CreateNewListWithStudentsWhoPassedAllSubjects(Position lista, Position hrvatski, Position matematika, Position engleski);
Position CreateNewElement();
int PrintList(Position head);
int PrintNewList(Position head);
int DeleteAll(Position head);

int main(int argc, char *argv[]) {
	Cvor matematika;
	Cvor hrvatski;
	Cvor engleski;
	Cvor lista;
	char c = 0;
	matematika.next = NULL;
	hrvatski.next = NULL;
	engleski.next = NULL;
	lista.next = NULL;

	ReadFromFile(&hrvatski, "hrv.txt");
	PrintList(hrvatski.next);
	printf("\r\n-------------------------\r\n");

	ReadFromFile(&matematika, "mat.txt");
	PrintList(matematika.next);
	printf("\r\n-------------------------\r\n");

	ReadFromFile(&engleski, "eng.txt");
	PrintList(engleski.next);
	printf("\r\n-------------------------\r\n");
	printf("\r\n-------------------------\r\n");

	CreateNewListWithStudentsWhoPassedAllSubjects(&lista, &hrvatski, &matematika, &engleski);
	PrintNewList(lista.next);
	printf("\r\n-------------------------\r\n");

	DeleteAll(&hrvatski);
	DeleteAll(&matematika);
	DeleteAll(&engleski);

	scanf(" %c", &c);
	return 0;
}

int CreateNewListWithStudentsWhoPassedAllSubjects(Position lista, Position hrvatski, Position matematika, Position engleski) {
	Position temp;
	float prosjek;
	while (hrvatski->next!=NULL && matematika->next != NULL && engleski->next != NULL)
	{
		if (hrvatski->next->ocjena>1 && matematika->next->ocjena > 1 && engleski->next->ocjena > 1)
		{
			temp = CreateNewElement();
			if (temp == NULL)
				printf(ALLOCATION_ERROR);
			else
			{
				strcpy(temp->ime, hrvatski->next->ime);
				strcpy(temp->prezime, hrvatski->next->prezime);
				temp->prosjek = ((float)hrvatski->ocjena + engleski->ocjena + matematika->ocjena) / 3;
				PushElementInList(lista, temp);
			}
		}
		hrvatski = hrvatski->next;
		matematika = matematika->next;
		engleski = engleski->next;
	}
	return 0;
}

int ReadFromFile(Position head, const char *fileName) {
	FILE *fp;
	Position temp;
	char buffer[STRING_MAX_LENGTH];
	fp = fopen(fileName, "r");
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
					while (head->next != NULL)
						head = head->next;
					sscanf(buffer, " %s %s %d", temp->ime, temp->prezime, &temp->ocjena);
					PushElementInList(head, temp);
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

Position CreateNewElement() {
	Position temp;
	temp = (Position)malloc(sizeof(Cvor));
	if (temp == NULL)
		return NULL;
	else
		temp->next = NULL;
	return temp;
}

int PrintNewList(Position head) {
	if (head == NULL)
		printf(EMPTY_LIST);
	else
	{
		while (head != NULL)
		{
			printf(" %s %s %0.2f\r\n", head->ime, head->prezime, head->prosjek);
			head = head->next;
		}
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
			printf(" %s %s %d\r\n", head->ime, head->prezime, head->ocjena);
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
