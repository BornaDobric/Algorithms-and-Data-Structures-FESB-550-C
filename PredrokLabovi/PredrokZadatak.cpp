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
	int ocjenaP2;
	int ocjenaAISP;
	char ime[STRING_MAX_LENGTH];
	char prezime[STRING_MAX_LENGTH];
	Position next;
}Cvor;

int ReadFromFile(Position head, const char *filename);
int ReadFromAISP(Position head, const char *filename);
int PushElement(Position head, Position temp);
Position CreateNewElement();
int FindSpot(Position head, Position temp);
int PrintList(Position head);
int DeleteAll(Position head);

int main(int argc, char *argv[]) {
	Cvor head;
	char c = 0;
	head.next = NULL;
	ReadFromFile(&head, "P2.txt");
	PrintList(head.next);
	printf("\r\n---------------------\r\n");
	ReadFromAISP(&head, "aisp.txt");
	PrintList(head.next);
	DeleteAll(&head);
	scanf(" %c", &c);
	return 0;
}

int ReadFromAISP(Position head, const char *filename) {
	FILE *fp;
	Position temp;
	char buffer[STRING_MAX_LENGTH];
	fp = fopen(filename, "r");
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
				if (fgets(buffer, STRING_MAX_LENGTH, fp) != NULL)
				{
					sscanf(buffer, " %s %s %d", temp->ime, temp->prezime, &temp->ocjenaAISP);
					FindSpot(head, temp);
				}
			}
		}
		fclose(fp);
	}
	return 0;
}

int FindSpot(Position head, Position temp) {
	while (head->next != NULL && _strcmpi(head->next->prezime, temp->prezime) != 0)
		head = head->next;
	if (head->next != NULL && head->next->ocjenaP2 > 1)
		head->next->ocjenaAISP = temp->ocjenaAISP;
	else
		PushElement(head, temp);
	return 0;
}

int ReadFromFile(Position head, const char *filename) {
	FILE *fp;
	Position temp;
	char buffer[STRING_MAX_LENGTH];
	fp = fopen(filename, "r");
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
				if (fgets(buffer, STRING_MAX_LENGTH, fp) != NULL)
				{
					while (head->next != NULL)
						head = head->next;
					sscanf(buffer, " %s %s %d", temp->ime, temp->prezime, &temp->ocjenaP2);
					PushElement(head, temp);
				}
			}
		}
		fclose(fp);
	}
	return 0;
}

int PushElement(Position head, Position temp) {
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
			if (head->ocjenaP2 > 1 && head->ocjenaAISP > 0)
				printf(" %s %s    ocjena P2: %d    ocjena AISP: %d\r\n", head->ime, head->prezime, head->ocjenaP2, head->ocjenaAISP);
			else if (head->ocjenaP2 > 0)
				printf(" %s %s    ocjena P2: %d\r\n", head->ime, head->prezime, head->ocjenaP2);
			else
				printf(" %s %s    ocjena AISP: %d\r\n", head->ime, head->prezime, head->ocjenaAISP);
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
	printf("\r\nLista je uspjesno izbrisana!\r\n");
	return 0;
}
