#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<string>
#define STRING_MAX_LENGHT 50;
#define RANGE_MIN 10
#define RANGE_MAX 100

typedef struct _cvor* Position;
typedef struct _cvor {
	int element;
	Position next;
}Cvor;

void PrintMenu();
int PushStog(Position head, int brojac);
int PopStog(Position head, int brojac);
int PrintStog(Position head, int brojac);
int DeleteAll(Position head);
int GetRandomNumber();
Position CreateNewElement(int broj);

int main(int argc, char *argv[]) {
	Cvor stog;
	stog.next = NULL;
	char izbor = 0;
	int maxBrojEl = 0;
	int n = 0;
	while (maxBrojEl<5)
	{
		printf("\r\nUnesite velicinu stoga <5-20>: ");
		scanf(" %d", &maxBrojEl); //max broj elemenata koje mozemo spremit u listu
		if (maxBrojEl<5 || maxBrojEl>20)
		{
			maxBrojEl = 0; //ako ne zadovoljava unesi ponovno
			printf("\r\nPogresan unos!\r\n");
		}
	}
	srand((unsigned)time(NULL));
	while (izbor != 'k')
	{
		PrintMenu();
		scanf(" %c", &izbor);
		switch (izbor)
		{
		case '1':
			if (n < maxBrojEl) //n ce bit brojac elemenata u listi
				n = PushStog(&stog, n); //upisuj na stog dok je n<maxBrojEl
			else
				printf("\r\nStog je popunjen!\r\n");
			PrintStog(stog.next, n);
			break;
		case '2':
			if (n > 0)
				n = PopStog(&stog, n); //moguce skidanje dok ima elemenata na stogu
			PrintStog(stog.next, n);
			break;
		case 'k':
			printf("\r\nKraj programa!\r\n");
			break;
		default:
			printf("\r\nPogresan izbor!\r\nPokusajte ponovno.\r\n");
			break;
		}
	}
	DeleteAll(&stog);
	return 0;
}
void PrintMenu() {
	printf("\r\n\t******************************************\r\n");
	printf("\r\n\t***********   IZBORNIK   *****************\r\n");
	printf("\r\n\t******************************************\r\n");
	printf("\r\n\t1.\tPush na stog\r\n");
	printf("\r\n\t2.\tPop sa stoga\r\n");
	printf("\r\n\tk.\tKraj programa\r\n");
	printf("\r\n\tIzbor: ");
}
int GetRandomNumber() {
	int broj = (rand() % (RANGE_MAX - RANGE_MIN + 1) + RANGE_MIN); //random number
	return broj;
}
int PushStog(Position head, int brojac) { //zadnji koji je usa se prvi skida
	Position temp;
	static Position lastElement;
	int broj = GetRandomNumber();
	temp = CreateNewElement(broj);
	if (temp == NULL)
		printf("\r\nDoslo je do greske prilikom alokacije memorije!\r\n");
	else
	{
		printf("\r\nPushed number: %d\r\n", broj);
		temp->next = head->next; //ubacivanje elementa u listu
		head->next = temp;
		brojac++; //ako je ubacen el. u listu digni brojac
	}
	return brojac;
}
int PopStog(Position head, int brojac) {
	Position temp;
	temp = head->next; //klasika brisanje elemenata, oslobadanje memorije
	if (temp == NULL)
		printf("\r\nLista je prazna!\r\n");
	else
	{
		head->next = temp->next; //promjena pokazivaca
		printf("\r\nPopped number: %d\r\n", temp->element);
		free(temp);
		brojac--; //ako se poppalo el. smanji brojac
	}
	return brojac;
}
Position CreateNewElement(int broj) {
	Position temp;
	temp = (Position)malloc(sizeof(Cvor));
	if (temp == NULL)
		return NULL;
	else
	{
		temp->element = broj; //upisi broj  u element liste
		temp->next = NULL;
	}
	return temp;
}
int PrintStog(Position head, int brojac) {
	printf("\r\nU listi se nalazi %d elemenata.\r\n", brojac);
	while (brojac>0) //dok nije kraj liste
	{
		printf("%d\r\n", head->element); //print element
		head = head->next; //iduci element
		brojac--; //smanjuj brojac kako se ispisuju elementi
	}
	return 0;
}
int DeleteAll(Position head) {
	Position temp;
	while (head->next != NULL)
	{	//klasika brisanje elemenata
		temp = head->next;
		head->next = temp->next; //promjena pokazivaca
		free(temp); //oslobodi temp
	}
	return 0;
}