#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#define ALLOCATION_ERROR "\r\nDoslo je do greske prilikom otvaranja datoteke!"
#define EMPTY_LIST "\r\nLista je prazna!"
#define PUSHED_ELEMENT "\r\nPushed element: %d\r\n"
#define POPPED_ELEMENT "\r\nPopped element: %d\r\n"
#define RAND_MIN 10
#define RAND_MAX 100

typedef struct _cvor* Position;
typedef struct _cvor {
	int element;
	Position next;
}Cvor;

int PrintMenu();
int PushElement(Position head, int counter);
int GetRandomNumber();
Position CreateNewElement(int broj);
int PopElement(Position head, int counter);
int PrintList(Position head);
int DeleteAll(Position head);

int main(int argc, char *argv[]) {
	Cvor stack;
	stack.next = NULL;
	char izbor = 0;
	int brojac = 0;
	int maxNumberOfElements = 0;
	while (maxNumberOfElements<5)
	{
		printf("\r\nOdaberite velicinu stoga <5-20>: ");
		scanf(" %d", &maxNumberOfElements);
		if (maxNumberOfElements < 5 || maxNumberOfElements > 20) {
			printf("\r\nPogresan odabir <%d>.\r\nPokusajte ponovno!\r\n", maxNumberOfElements);
			maxNumberOfElements = 0;
		}
	}
	srand((unsigned)time(NULL));
	while (izbor!='k' && izbor!='K')
	{
		PrintMenu();
		scanf(" %c", &izbor);
		switch (izbor)
		{
		case '1':
			if (brojac < maxNumberOfElements)
				brojac = PushElement(&stack, brojac);
			else
				printf("\r\nStog je pun!\r\n");
			PrintList(stack.next);
			break;
		case '2':
			if (brojac > 0)
				brojac = PopElement(&stack, brojac);
			PrintList(stack.next);
			break;
		case '3':
			PrintList(stack.next);
			break;
		case 'k':
		case 'K':
			printf("\r\nIzlaz iz programa!\r\n");
			break;
		default:
			printf("\r\nPogresan odabir <%c>.\r\nPokusajte ponovno!\r\n", izbor);
			break;
		}
	}
	DeleteAll(&stack);
	return 0;
}
int PrintMenu() {
	printf("\r\n1.Push stack.");
	printf("\r\n2.Pop stack.");
	printf("\r\n3.Print stack.");
	printf("\r\nK.Kraj programa.");
	printf("\r\nVas odabir: ");
	return 0;
}
int PushElement(Position head, int counter) {
	Position temp;
	int broj = GetRandomNumber();
	temp = CreateNewElement(broj);
	if (temp == NULL)
		printf(ALLOCATION_ERROR);
	else
	{
		temp->next = head->next;
		head->next = temp;
		counter++;
	}
	printf(PUSHED_ELEMENT, broj);
	return counter;
}
int GetRandomNumber() {
	int broj = (rand() % (RAND_MAX - RAND_MIN + 1) + RAND_MIN);
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
		temp->next = NULL;
	}
	return temp;
}
int PopElement(Position head, int counter) {
	Position temp;
	temp = head->next;
	if (temp == NULL)
		printf(EMPTY_LIST);
	else
	{
		printf(POPPED_ELEMENT, temp->element);
		head->next = temp->next;
		free(temp);
		counter--;
	}
	return counter;
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