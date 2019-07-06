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
#define FILENAME "drzave.txt"
#define RAND_MIN 1
#define RAND_MAX 5

typedef struct _cvor* Position;
typedef struct _cvor {
	int element;
	Position next;
}Cvor;

int PushElementInList(Position head);
int GetRandomNumber();
Position CreateNewElement(int broj);
int CountElementsInList(Position head);
int DeleteElementsAboveAverage(Position head, float prosjek);
float GetAverage(Position head, int brojac);
int PrintList(Position head);
int DeleteAll(Position head);

int main(int argc, char *argv[]) {
	Cvor head;
	char c = 0;
	int brojac = 0;
	float prosjek = 0;
	head.next = NULL;
	srand((unsigned)time(NULL));

	for (int i = 0; i < 10; i++) {
		PushElementInList(&head);
	}

	PrintList(head.next);

	brojac = CountElementsInList(&head);
	printf("\r\n\r\nBroj elemenata u listi je: %d\r\n", brojac);

	prosjek = GetAverage(&head, brojac);
	printf("\r\n\r\nProsjek elemenata u listi je: %0.2f\r\n", prosjek);

	DeleteElementsAboveAverage(&head, prosjek);
	printf("\r\n\r\nLista nakon brisanja elemenata većih od prosjeka: \r\n");
	PrintList(head.next);

	scanf(" %c", &c);
	return 0;
}

int DeleteElementsAboveAverage(Position head, float prosjek) {
	Position temp;
	while (head->next!=NULL)
	{
		if (head->next->element > prosjek)
		{
			temp = head->next;
			head->next = temp->next;
			free(temp);
		}
		else
			head = head->next;
	}
	return 0;
}

float GetAverage(Position head, int brojac) {
	float prosjek = 0;
	int sum = 0;
	while (head->next!=NULL)
	{
		sum += head->next->element;
		head = head->next;
	}
	prosjek = (float)sum / brojac;
	return prosjek;
}

int CountElementsInList(Position head) {
	int brojac = 0;
	while (head->next!=NULL)
	{
		brojac++;
		head = head->next;
	}
	return brojac;
}

int PushElementInList(Position head) {
	Position temp;
	int broj = GetRandomNumber();
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

Position CreateNewElement(int broj) {
	Position temp;
	temp = (Position)malloc(sizeof(Cvor));
	if (temp == NULL)
		return NULL;
	else
	{
		temp->element = broj;
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
