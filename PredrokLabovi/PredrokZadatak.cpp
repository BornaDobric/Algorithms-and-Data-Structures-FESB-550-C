#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#define STRING_MAX_LENGTH 50
#define ALLOCATION_ERROR "\r\nDoslo je do greske prilikom alokacije memorije!"
#define EMPTY_LIST "\r\nLista je prazna!"
#define FILE_OPEN_ERROR "\r\nDOslo je do greske prilikom otvaranja datoteke!"

typedef struct _cvor* Position;
typedef struct _cvor {
	char ime[STRING_MAX_LENGTH];
	char prezime[STRING_MAX_LENGTH];
	int ocjenaP2;
	int ocjenaAisp;
	Position next;
}Cvor;

int ReadGradesFromP2(Position head, char *filename);
int ReadGradesFromAISP(Position head, char *filename);
Position CreateNewElement();
int PushNode(Position head, Position temp);
int PrintList(Position head);
int DeleteAll(Position head);

int main(int argc, char *argv[]) {
	Cvor head;
	head.next = NULL;
	ReadGradesFromP2(&head, "P2.txt");
	PrintList(head.next);
	ReadGradesFromAISP(&head, "aisp.txt");
	PrintList(head.next);
	DeleteAll(&head);
	return 0;
}
int ReadGradesFromP2(Position head, char *filename) {
	FILE *fp;
	Position temp;
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
			else {
				fscanf(fp, " %s %s %d", temp->ime, temp->prezime, &temp->ocjenaP2);
				PushNode(head, temp);
			}
		}
		fclose(fp);
	}
	return 0;
}
int ReadGradesFromAISP(Position head, char *filename) {
	FILE *fp;
	Position temp = head->next;
	Position newElement;
	char buffer[STRING_MAX_LENGTH];
	char blah[STRING_MAX_LENGTH];
	fp = fopen(filename, "r");
	if (fp == NULL)
		printf(FILE_OPEN_ERROR);
	else
	{
		while (!feof(fp))
		{
			fgets(buffer, STRING_MAX_LENGTH, fp);
			if (temp->ocjenaP2>1)
			{
				sscanf(buffer, " %s %s %d", blah, blah, &temp->ocjenaAisp);
			}
			else
			{
				newElement = CreateNewElement();
				PushNode(head, newElement);
			}
			head = head->next;
		}
		fclose(fp);
	}
	return 0;
}
int PushNode(Position head, Position temp) {
	temp->next = head->next;
	head->next = temp;
	return 0;
}
Position CreateNewElement() {
	Position temp;
	temp = (Position)malloc(sizeof(Cvor));
	if (temp == NULL)
		printf(ALLOCATION_ERROR);
	else
		temp->next = NULL;
	return temp;
}
int PrintList(Position head) {
	if (head == NULL)
		printf(EMPTY_LIST);
	else
	{
		while (head!=NULL)
		{
			if (head->ocjenaAisp >0 && head->ocjenaP2>0)
				printf("%s %s - p2:%d	aisp:%d\n", head->ime, head->prezime, head->ocjenaP2, head->ocjenaAisp);
			else if (head->ocjenaP2 >0)
				printf("%s %s - p2:%d	\n", head->ime, head->prezime, head->ocjenaP2);
			else if (head->ocjenaAisp >0)
				printf("%s %s - aisp:%d	\n", head->ime, head->prezime, head->ocjenaAisp);
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