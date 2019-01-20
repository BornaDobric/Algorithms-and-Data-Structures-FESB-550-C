#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#include<math.h>
#define STRING_MAX_LENGHT 50
#define ALLOCATION_ERROR "\r\nDoslo je do greske prilikom alokacije memorije!"
#define EMPTY_LIST "\r\nLista je prazna!"
#define FILE_OPEN_ERROR "\r\nDoslo je do greske prilikom otvaranja datoteke <%s>!"
#define FILE_NAME "drzave.txt"

typedef struct _state* Position;
typedef struct _state {
	char stateName[STRING_MAX_LENGHT];
	Position next;
}State;

int PrintMenu();
int PrintStateName(Position head);
Position FindPreviousState(Position head, char *stateName);
int DeleteState(Position head);
int ReadFromFile(Position head);
int PushElement(Position head, Position temp);
int CountStatesInList(Position head);
Position FindEvery10thElement(Position head);
int PopEvery10thElement(Position head, int nthElement);
int PrintList(Position head);
int FindPlaceForSortedInput(Position head, Position temp);
int DeleteAll(Position head);

int main(int argc, char *argv[]) {
	State head;
	Position bufferPosition;
	char stateName[STRING_MAX_LENGHT];
	char izbor = 0;
	int brojac = 0;
	int nthElement = 3;
	head.next = NULL;
	ReadFromFile(&head);
	while (izbor!='k' && izbor!='K')
	{
		PrintMenu();
		scanf(" %c", &izbor);
		switch (izbor)
		{
		case '1':
			PrintList(head.next);
			break;
		case '2':
			printf("\r\nUnesite ime drzave koju trazite: ");
			scanf(" %s", stateName);
			bufferPosition = FindPreviousState(&head, stateName);
			if (bufferPosition == NULL)
				printf("\r\nDrzava <%s> koju trazite nije upisana u listu!\r\n", stateName);
			else
				PrintStateName(bufferPosition->next);
			break;
		case '3':
			printf("\r\nUnesite ime drzave koju trazite: ");
			scanf(" %s", stateName);
			bufferPosition = FindPreviousState(&head, stateName);
			if (bufferPosition == NULL)
				printf("\r\nDrzava <%s> koju trazite nije upisana u listu!\r\n", stateName);
			else
			{
				DeleteState(bufferPosition);
				PrintList(head.next);
			}
			break;
		case '4':
			brojac = CountStatesInList(&head);
			printf("\r\nBroj elemenata u listi: %d\r\n", brojac);
			PopEvery10thElement(&head, nthElement);
			break;
		case 'k':
		case 'K':
			printf("\r\nIzlaz iz programa!\r\n");
			break;
		default:
			printf("\r\nPogresan izbor <%c>! Pokusajte ponovno!\r\n", izbor);
			break;
		}
	}
	DeleteAll(&head);
	printf("\r\n");
	return 0;
}
int PrintMenu() {
	printf("\r\n1.Ispis liste.");
	printf("\r\n2.Pronadi drzavu.");
	printf("\r\n3.Izbrisi drzavu.");
	printf("\r\n4.Izbrisi svaku desetu drzavu.");
	printf("\r\nK.Kraj programa.");
	printf("\r\nVas odabir: ");
	return 0;
}
int PrintStateName(Position head) {
	printf(" %s\r\n", head->stateName);
	return 0;
}
Position FindPreviousState(Position head, char *stateName) {
	while (head->next != NULL && strcmpi(head->next->stateName, stateName) != 0)
		head = head->next;
	if (head->next == NULL)
		return NULL;
	return head;
}
int DeleteState(Position head) {
	Position temp;
	temp = head->next;
	head->next = temp->next;
	printf("\r\nPopped state: %s\r\n", temp->stateName);
	free(temp);
	return 0;
}
int ReadFromFile(Position head) {
	FILE *fp;
	Position temp;
	fp = fopen(FILE_NAME, "r");
	if (fp == NULL)
		printf(FILE_OPEN_ERROR, FILE_NAME);
	else
	{
		while (!feof(fp))
		{
			temp = (Position)malloc(sizeof(State));
			if (temp == NULL)
				printf(ALLOCATION_ERROR);
			else
			{
				fscanf(fp, " %s", temp->stateName);
				FindPlaceForSortedInput(head, temp);
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
int CountStatesInList(Position head) {
	int brojac = 0;
	while (head->next!=NULL)
	{
		brojac++;
		head = head->next;
	}
	return brojac;
}
Position FindEvery10thElement(Position head) {
	int brojac = 0;
	while (head->next!=NULL)
	{
		brojac++;
		if (brojac == 10)
			return head;
		head = head->next;
	}
	return head;
}
int PopEvery10thElement(Position head, int nthElement) {
	Position tempState;
	int brojac = 0;
	if (head->next == NULL)
		printf(EMPTY_LIST);
	else
	{
		if (nthElement == 1) {
			DeleteAll(head);
			return NULL;
		}
		while (head->next!=NULL)
		{
			brojac++;
			if (brojac == 10 || brojac==20)
			{
				tempState = head->next;
				head->next = tempState->next;
				printf("\r\nPopped state: %s\r\n", tempState->stateName);
				free(tempState);
				printf("\r\nState deleted!\r\n");
				brojac = 1;
			}
			head = head->next;
		}
	}
	return 0;
}
int FindPlaceForSortedInput(Position head, Position temp) {
	while (head->next != NULL && strcmpi(head->next->stateName, temp->stateName) < 0)
		head = head->next;
	PushElement(head, temp);
	return 0;
}
int PrintList(Position head) {
	if (head == NULL)
		printf(EMPTY_LIST);
	else
	{
		while (head!=NULL)
		{
			printf(" %s\r\n", head->stateName);
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