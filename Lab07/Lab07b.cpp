#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#define STRING_MAX_LENGHT 50
#define RANGE_MIN 10
#define RANGE_MAX 100
#define RANGE_PRIORITY_MIN 1
#define RANGE_PRIORITY_MAX 5

typedef struct _cvor* Position;
typedef struct _cvor {
	int element;
	int priority;
	Position next;
}Cvor;

void PrintMenu();
int PushRed(Position head);
int PopRed(Position head);
int PrintRed(Position head);
int DeleteAll(Position head);
int GetRandomNumber(int min, int max);
Position CreateNewElement(Position, int broj);

int main(int argc, char *argv[]) {
	Cvor red;
	red.next = NULL;
	char izbor = 0;
	srand((unsigned)time(NULL));
	while (izbor!='k' && izbor!='K')
	{
		PrintMenu();
		scanf(" %c", &izbor);
		switch (izbor)
		{
		case '1':
			PushRed(&red);
			PrintRed(red.next);
			break;
		case '2':
			PopRed(&red);
			PrintRed(red.next);
			break;
		case 'K':
		case 'k':
			printf("\r\nIzlaz iz programa!\r\n");
			break;
		default:
			printf("\r\nPogresan izbor!\r\npokusajte ponovno.\r\n");
			break;
		}
	}
	DeleteAll(&red);
	return 0;
}
void PrintMenu() {
	printf("\r\n\t******************************************\r\n");
	printf("\r\n\t***********   IZBORNIK   *****************\r\n");
	printf("\r\n\t******************************************\r\n");
	printf("\r\n\t1.\tPush na red\r\n");
	printf("\r\n\t2.\tPop sa reda\r\n");
	printf("\r\n\tk.\tKraj programa\r\n");
	printf("\r\n\tIzbor: ");
}
int PushRed(Position head) {
	Position temp;
	int broj = GetRandomNumber(RANGE_MIN, RANGE_MAX);
	temp = CreateNewElement(head,broj);
	if (temp == NULL)
		printf("\r\nDoslo je do greske prilikom alokacije memorije!\r\n");
	else
	{
		printf("\r\nNa listu se sprema: ( %d %d)", temp->element, temp->priority);
		while (head->next != NULL && head->next->priority >= temp->priority) //dok nije kraj liste i dok iduci element ima veci ili jednak prioritet od elementa koji se upisuje
			head = head->next; //iduci element
		temp->next = head->next; //prebacivanje pokazivaca
		head->next = temp;
	}
	return 0;
}
int PopRed(Position head) {
	Position temp;
	if (head->next!=NULL)
	{
		temp = head->next;
		printf("\r\nSa reda se skida ( %d %d )\r\n", temp->element, temp->priority);
		head->next = temp->next;
		free(temp);
	}
	else
		printf("\r\nLista je prazna!\r\n\r\n");
	return 0;
}
int PrintRed(Position head) {
	printf("\r\nU listi se nalaze: \r\n");
	while (head!=NULL)
	{
		printf("\r\n( %d %d )", head->element, head->priority); //ispisi element i prioritet
		head = head->next; //iduci element
	}
	return 0;
}
int DeleteAll(Position head) {
	Position temp;
	while (head->next!=NULL)
	{	//klasika brisanje elemenata
		temp = head->next;
		head->next = temp->next; //promjena pokazivaca
		free(temp); //oslobodi temp
	}
	return 0;
}
int GetRandomNumber(int min, int max) {
	int broj = (rand() % (max - min + 1) + min); //klasika rand broj
	return broj;
}
Position CreateNewElement(Position, int broj) {
	Position temp;
	temp = (Position)malloc(sizeof(Cvor));
	if (temp == NULL)
		return NULL;
	else
	{
		temp->element = broj;
		temp->priority = GetRandomNumber(RANGE_PRIORITY_MIN, RANGE_PRIORITY_MAX);
		temp->next = NULL;
	}
	return temp;
}