#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#define ALLOCATION_ERROR "\r\nDoslo je do greske prilikom alokacije memorije"
#define RAND_MIN 10
#define RAND_MAX 100
#define EMPTY_LIST "\r\nLista je prazna!\r\n"
#define PUSHED_ELEMENT "\r\nPushed element: ( %d %d )\r\n"
#define POPPED_ELEMENT "\r\nPushed element: ( %d %d )\r\n"
#define PRIORITY_MIN 1
#define PRIORITY_MAX 5

typedef struct _cvor* Position;
typedef struct _cvor {
	int element;
	int priority;
	Position next;
}Cvor;

int PrintMenu();
int PushElement(Position head);
int GetRandomNumber(int min, int max);
Position CreateNewElement(int broj);
Position FindSpotByPriority(Position head, Position temp);
int PopElement(Position head);
int PrintList(Position head);
int DeleteAll(Position head);

int main(int argc, char *argv[]) {
	Cvor queue;
	char izbor = 0;
	queue.next = NULL;
	while (izbor!='k' && izbor!='K')
	{
		PrintMenu();
		scanf(" %c", &izbor);
		switch (izbor)
		{
		case '1':
			PushElement(&queue);
			PrintList(queue.next);
			break;
		case '2':
			PopElement(&queue);
			PrintList(queue.next);
			break;
		case '3':
			PrintList(queue.next);
			break;
		case 'k':
		case 'K':
			printf("\r\nIzlaz iz programa!\r\n");
			break;
		default:
			printf("\r\nPogresan unos <%c>.\r\nPokusajte ponovno!\r\n", izbor);
			break;
		}
	}
	DeleteAll(&queue);
	return 0;
}
int PrintMenu() {
	printf("\r\n1.Push queue.");
	printf("\r\n2.Pop queue.");
	printf("\r\n3.Print queue.");
	printf("\r\nK.Izlaz iz programa.");
	printf("\r\nVas odabir: ");
	return 0;
}
int PushElement(Position head) {
	Position temp;
	int broj = GetRandomNumber(RAND_MIN, RAND_MAX);
	temp = CreateNewElement(broj);
	if (temp == NULL)
		printf(ALLOCATION_ERROR);
	else
	{
		head = FindSpotByPriority(head, temp);
		temp->next = head->next;
		head->next = temp;
		printf(PUSHED_ELEMENT, temp->element, temp->priority);
	}
	return 0;
}
int GetRandomNumber(int min, int max) {
	int broj = (rand() % (max - min + 1) + min);
	return broj;
}
Position CreateNewElement(int broj) {
	Position temp;
	temp = (Position)malloc(sizeof(Cvor));
	if (temp == NULL)
		return NULL;
	else
	{
		temp->element = broj;
		temp->priority = GetRandomNumber(PRIORITY_MIN, PRIORITY_MAX);
		temp->next = NULL;
	}
	return temp;
}
Position FindSpotByPriority(Position head, Position temp) {
	while (head->next != NULL && head->next->priority >= temp->priority)
		head = head->next;
	return head;
}
int PopElement(Position head) {
	Position temp;
	temp = head->next;
	if (temp == NULL)
		printf(EMPTY_LIST);
	else
	{
		printf(POPPED_ELEMENT, temp->element, temp->priority);
		head->next = temp->next;
		free(temp);
	}
	printf("\r\nElement uspjesno izbrisan!\r\n");
	return 0;
}
int PrintList(Position head) {
	if (head == NULL)
		printf(EMPTY_LIST);
	else
	{
		while (head!=NULL)
		{
			printf(" %d %d\r\n", head->element, head->priority);
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