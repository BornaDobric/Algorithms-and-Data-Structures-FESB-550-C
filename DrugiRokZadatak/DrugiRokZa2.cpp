#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#define STRING_MAX_LENGTH 50
#define ALLOCATION_ERROR "\r\nDoslo je do greske prilikom alokacije memorije!"
#define EMPTY_LIST "\r\nLista je prazna!"
#define RAND_MIN 10
#define RAND_MAX 20

typedef struct _cvor* Position;
typedef struct _cvor {
	int element;
	Position next;
}Cvor;

int PrintList(Position head);
int GetRandomNumber();
int PushElement(Position head);
Position CreateNewElement(int broj);
float CalculateAverage(Position head);
int DeleteElementsAboveAverage(Position head, float prosjek);
int DeleteAll(Position head);

int main(int argc, char* argv[]) {
	Cvor head;
	float prosjek = 0;
	head.next = NULL;
	srand((unsigned)time(NULL));
	for (int i = 0; i < 20; i++) {
		PushElement(&head);
	}
	PrintList(head.next);
	prosjek = CalculateAverage(&head);
	printf("\r\nProsjek je: %0.2f\r\n", prosjek);
	DeleteElementsAboveAverage(&head, prosjek);
	PrintList(head.next);
	DeleteAll(&head);
	return 0;
}
float CalculateAverage(Position head) {
	float prosjek = 0;
	int sum = 0;
	while (head->next!=NULL)
	{
		sum += head->next->element;
		head = head->next;
	}
	prosjek = ((float)sum / (float)20);
	return prosjek;
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
int PushElement(Position head) {
	Position temp;
	int broj = GetRandomNumber();
	temp = CreateNewElement(broj);
	if (temp == NULL)
		printf(ALLOCATION_ERROR);
	else
	{
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