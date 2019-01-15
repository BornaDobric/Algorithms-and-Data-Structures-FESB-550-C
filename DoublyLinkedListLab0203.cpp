#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#define ALLOCATION_ERROR "\r\nDoslo je do greske prilikom alokacije memorije!"
#define EMPTY_LIST "\r\nLista je prazna!"
#define NEW_LINE "\r\n"
#define STRING_MAX_LENGHT 50

typedef struct _student* Position;
typedef struct _student {
	int godinaRodenja;
	char ime[STRING_MAX_LENGHT];
	char prezime[STRING_MAX_LENGHT];
	Position next;
	Position prev;
}Student;

typedef struct _studentPodaci {
	int godinaRodenja;
	char ime[STRING_MAX_LENGHT];
	char prezime[STRING_MAX_LENGHT];
}StudentPodaci;

int PrintMenu();
StudentPodaci GetStudentDataFromConsole();
int Insert(Position head, StudentPodaci studentPodaci);
int InsertOnEnd(Position head, StudentPodaci studentPodaci);
int PrintList(Position head);
int InsertBefore(Position head, StudentPodaci studentPodaci);
int InsertAfter(Position head, StudentPodaci studentPodaci);
Position FindPreviousElement(Position head, char *prezime);
int DeleteElement(Position p, char *prezime);
int DeleteAll(Position head);

int main(int argc, char *argv[]) {
	Student head;
	StudentPodaci bufferStudent;
	Position bufferPosition;
	char izbor = 0;
	char prezime[STRING_MAX_LENGHT];
	head.next = NULL;
	while (izbor!='k' && izbor!='K')
	{
		PrintMenu();
		scanf(" %c", &izbor);
		switch (izbor)
		{
		case '1':
			bufferStudent = GetStudentDataFromConsole();
			Insert(&head, bufferStudent);
			break;
		case '2':
			PrintList(head.next);
			break;
		case '3':
		case '4':
		case '5':
			printf("\r\nUnesite prezime osobe koju brisete iz liste: ");
			scanf(" %s", prezime);
			DeleteElement(&head, prezime);
			break;
		case '6':
		case '7':
		case 'k':
		case 'K':
			printf("\r\nIzlaz iz programa.\r\n");
			break;
		default:
			printf("\r\nPogresan odabir <%c>!\r\nPokusajte ponovno!\r\n", izbor);
			break;
		}
	}
	return 0;
}
int PrintMenu() {
	printf("\r\n1.Umetni element na pocetak liste.");
	printf("\r\n2.Ispisi listu.");
	printf("\r\n3.Umetni element na kraj liste.");
	printf("\r\n4.Pronadi element po prezimenu.");
	printf("\r\n5.Izbrisi element po prezimenu.");
	printf("\r\n6.Umetni element prije nekog elementa.");
	printf("\r\n7.Umetni element nakon nekog elementa.");
	printf("\r\nK.Kraj programa.");
	printf("\r\nVas odabir: ");
	return 0;
}
StudentPodaci GetStudentDataFromConsole() {
	StudentPodaci tempPodaci;
	printf("\r\nUnesite ime, prezime i godinu rodenja studenta: ");
	scanf(" %s %s %d", tempPodaci.ime, tempPodaci.prezime, &tempPodaci.godinaRodenja);
	return tempPodaci;
}
int Insert(Position head, StudentPodaci studentPodaci) {
	Position temp;
	temp = (Position)malloc(sizeof(Student));
	if (temp == NULL)
		printf(ALLOCATION_ERROR);
	else
	{
		strcpy(temp->ime, studentPodaci.ime);
		strcpy(temp->prezime, studentPodaci.prezime);
		temp->godinaRodenja = studentPodaci.godinaRodenja;

		temp->next = head->next;
		head->next = temp;
		temp->prev = NULL;
		if (temp->next != NULL)
			temp->next->prev = temp;
	}
	return 0;
}
int InsertOnEnd(Position head, StudentPodaci studentPodaci) {

	return 0;
}
int PrintList(Position head) {
	Position lastElement;
	printf("\r\nProlazak kroz listu od pocetka do kraja: \r\n");
	while (head!=NULL)
	{
		printf(" %s %s %d\r\n", head->ime, head->prezime, head->godinaRodenja);
		lastElement = head;
		head = head->next;
	}
	printf("\r\nProlazak kroz listu od kraja do pocetka: \r\n");
	while (lastElement != NULL)
	{
		printf(" %s %s %d\r\n", lastElement->ime, lastElement->prezime, lastElement->godinaRodenja);
		lastElement = lastElement->prev;
	}
	return 0;
}
int InsertBefore(Position head, StudentPodaci studentPodaci) {

	return 0;
}
int InsertAfter(Position head, StudentPodaci studentPodaci) {

	return 0;
}
Position FindPreviousElement(Position head, char *prezime) {
	Position temp;
	
	return temp;
}
int DeleteElement(Position head, char *prezime) {
	while (head->next != NULL && strcmpi(head->next->prezime, prezime) != 0)
		head = head->next;
	head->prev->next = head->next;
	head->next->prev = head->prev;
	if (head->prev==NULL)
	{
		head->prev->next = head->next;
		head->next->prev = NULL;
	}
	printf("\r\nIz liste se brise: %s %s %d", head->ime, head->prezime, head->godinaRodenja);
	free(head);
	return 0;
}
int DeleteAll(Position head) {

	return 0;
}