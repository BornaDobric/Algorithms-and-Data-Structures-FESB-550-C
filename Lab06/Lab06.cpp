#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define STRING_MAX_LENGHT 50;
#define RANGE_MIN 10
#define RANGE_MAX 100

typedef struct _cvor* Position;
typedef struct _cvor {
	int element;
	Position next;
}Cvor;

void PrintMenu();
int PushStog(Position head);
int PushQueue(Position head);
int Pop(Position head);
int PrintList(Position head);
int DeleteAll(Position head);
int GetRandomNumber();
Position CreateNewElement(int broj);

int main(int argc, char *argv[]) {
	Cvor stog;
	Cvor red;
	char izbor = 0;

	stog.next = NULL;
	red.next = NULL;

	srand((unsigned)time(NULL));
	while (izbor != 'k' && izbor != 'K') //za kraj programa k ili K
	{
		PrintMenu();
		scanf(" %c", &izbor);
		printf("\r\n");
		switch (izbor)
		{
		case '1':
			PushStog(&stog);
			break;
		case '2':
			Pop(&stog);
			break;
		case '3':
			PrintList(stog.next);
			break;
		case '4':
			PushQueue(&red);
			break;
		case '5':
			Pop(&red);
			break;
		case '6':
			PrintList(red.next);
			break;
		default:
			printf("\r\nKrivi odabir<%c>!\r\n", izbor);
			break;
		}
	}
	DeleteAll(&stog);
	DeleteAll(&red);
	return 0;
}
void PrintMenu() {
	printf("\r\n##########################################\r\n");
	printf("\r\n#Push to stack ************\r\n");
	printf("\r\n#Pop from stack ************\r\n");
	printf("\r\n#Print stack ************\r\n");
	printf("\r\n#Push to queue ************\r\n");
	printf("\r\n#Pop from queue ************\r\n");
	printf("\r\n#Print queue ************\r\n");
	printf("\r\n##########################################\r\n");
	printf("\r\nUnesite odabir: \r\n");
}
int PushStog(Position head) { //zadnji koji je usa se prvi skida
	Position temp;
	int broj;
	broj = GetRandomNumber();
	temp = CreateNewElement(broj);
	if (temp == NULL)
		printf("\r\nDoslo je do greske prilikom alokacije memorije!\r\n");
	else
	{
		temp->next = head->next; //ubacivanje elementa
		head->next = temp;
	}
	printf("\r\nPushed number: %d\r\n", broj);
	return 0;
}
int PushQueue(Position head) { //prvi koji je usa se prvi skida
	Position temp;
	int broj;
	static Position lastElement = head; //zadnji element je head, static variables preserve their previous value in their previous scope and are not initialized again in the new scope
	broj = GetRandomNumber();
	temp = CreateNewElement(broj);
	if (temp == NULL)
		printf("\r\nDoslo je do greske prilikom alokacije memorije!\r\n");
	else
	{
		lastElement->next = temp; //promjena pokazivaca
		lastElement = temp; //novi zadnji element je temp koji je unesen
		printf("\r\nPushed number: %d\r\n", broj); 
	}
	return 0;
}
int Pop(Position head) {
	Position temp;
	temp = head->next; //klasika brisanje elemenata, oslobadanje memorije
	if (temp == NULL)
		printf("\r\nLista je prazna!\r\n");
	else
	{
		head->next = temp->next; head->next = temp->next; //promjena pokazivaca
		printf("\r\nPopped number: %d\r\n", temp->element);
		free(temp);
	}
	return 0;
}
int PrintList(Position head) {
	while (head != NULL) //dok nije kraj liste
	{
		printf("%d\r\n", head->element); //print element
		head = head->next; //iduci element
	}
	return 0;
}
int DeleteAll(Position head) {
	Position temp;
	while (head->next != NULL)
	{
		temp = head->next; //klasika brisanje elemenata
		head->next = temp->next; //promjena pokazivaca
		free(temp); //oslobodi temp
	}
	return 0;
}
int GetRandomNumber() {
	int broj;
	broj = (rand() % (RANGE_MAX - RANGE_MIN + 1) + RANGE_MIN); //rand klasika
	return broj;
}
Position CreateNewElement(int broj) {
	Position temp;
	temp = (Position)malloc(sizeof(Cvor));
	if (temp == NULL) //provjera nazad u funkciji
		return NULL;
	else
	{
		temp->element = broj; //upisi broj 
		temp->next = NULL;
	}
	return temp;
}
