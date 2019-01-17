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
int InsertBefore(Position head, Position toInsertBefore, StudentPodaci studentPodaci);
int InsertAfter(Position head, Position toInsertAfter, StudentPodaci studentPodaci);
Position FindElement(Position head, char *prezime);
int PrintElement(Position p);
int DeleteElement(Position head, Position toDelete);
int DeleteAll(Position head);

int main(int argc, char *argv[]) {
	Student head;
	StudentPodaci bufferStudent;
	Position bufferPosition;
	char izbor = 0;
	char prezime[STRING_MAX_LENGHT];
	head.next = NULL;
	while (izbor != 'k' && izbor != 'K')
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
			bufferStudent = GetStudentDataFromConsole();
			InsertOnEnd(&head, bufferStudent);
			break;
		case '4':
			printf("\r\nUnesite prezime osobe koju trazite: ");
			scanf(" %s", prezime);
			bufferPosition = FindElement(&head, prezime);
			if (bufferPosition == NULL)
				printf("\r\nStudent ne postoji u listi!\r\n");
			else
				PrintElement(bufferPosition);
			break;
		case '5':
			printf("\r\nUnesite prezime osobe koju brisete iz liste: ");
			scanf(" %s", prezime);
			bufferPosition = FindElement(&head, prezime);
			if (bufferPosition==NULL)
				printf("\r\nStudent <%s> nije upisan u listu!\r\n", prezime);
			else
			{
				DeleteElement(&head, bufferPosition);
				PrintList(head.next);
			}
			break;
		case '6':
			bufferStudent = GetStudentDataFromConsole();
			printf("\r\nUnesite prezime: ");
			scanf(" %s", prezime);
			bufferPosition = FindElement(&head, prezime);
			if (bufferPosition == NULL)
				printf("\r\nStudent <%s> nije upisan u listu!\r\n", prezime);
			else
			{
				InsertBefore(&head, bufferPosition, bufferStudent);
				PrintList(head.next);
			}
			break;
		case '7':
			bufferStudent = GetStudentDataFromConsole();
			printf("\r\nUnesite prezime: ");
			scanf(" %s", prezime);
			bufferPosition = FindElement(&head, prezime);
			if (bufferPosition == NULL)
				printf("\r\nStudent <%s> nije upisan u listu!\r\n", prezime);
			else
			{
				InsertAfter(bufferPosition, &head, bufferStudent);
				PrintList(head.next);
			}
			break;
		case 'k':
		case 'K':
			printf("\r\nIzlaz iz programa.\r\n");
			break;
		default:
			printf("\r\nPogresan odabir <%c>!\r\nPokusajte ponovno!\r\n", izbor);
			break;
		}
	}
	DeleteAll(&head);
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
	Position temp;
	temp = (Position)malloc(sizeof(Student));
	if (temp == NULL)
		printf(ALLOCATION_ERROR);
	else
	{
		strcpy(temp->ime, studentPodaci.ime);
		strcpy(temp->prezime, studentPodaci.prezime);
		temp->godinaRodenja = studentPodaci.godinaRodenja;

		if (head->next==NULL)
		{
			temp->next = head->next;
			head->next = temp;
			temp->prev = NULL;
		}
		else
		{
			while (head->next != NULL)
				head = head->next;
			temp->next = head->next;
			head->next = temp;
			temp->prev = head;
		}
	}
	return 0;
}
int PrintList(Position head) {
	Position lastElement;
	if (head == NULL)
		printf(EMPTY_LIST);
	else
	{
		printf("\r\nProlazak kroz listu od pocetka do kraja: \r\n");
		while (head != NULL)
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
	}
	return 0;
}
int InsertBefore(Position head, Position toInsertBefore, StudentPodaci studentPodaci) {
	Position temp;
	temp = (Position)malloc(sizeof(Student));
	if (temp == NULL)
		printf(ALLOCATION_ERROR);
	else
	{
		strcpy(temp->ime, studentPodaci.ime);
		strcpy(temp->prezime, studentPodaci.prezime);
		temp->godinaRodenja = studentPodaci.godinaRodenja;

		temp->prev = toInsertBefore->prev;
		toInsertBefore->prev = temp;
		temp->next = toInsertBefore;
		if (temp->prev != NULL)
			temp->prev->next = temp;
		else
			head->next = temp;
	}
	return 0;
}
int InsertAfter(Position toInsertAfter, Position head, StudentPodaci studentPodaci) {
	Position temp;
	temp = (Position)malloc(sizeof(Student));
	if (temp == NULL)
		printf(ALLOCATION_ERROR);
	else
	{
		strcpy(temp->ime, studentPodaci.ime);
		strcpy(temp->prezime, studentPodaci.prezime);
		temp->godinaRodenja = studentPodaci.godinaRodenja;

		temp->next = toInsertAfter->next;
		toInsertAfter->next = temp;
		temp->prev = toInsertAfter;
		if (temp->next != NULL)
			temp->next->prev = temp;
	}
	return 0;
}
Position FindElement(Position head, char *prezime) {
	while (head != NULL && strcmpi(head->prezime, prezime) != 0)
		head = head->next;
	return head;
}
int PrintElement(Position p) {
	printf(" %s %s %d\r\n", p->ime, p->prezime, p->godinaRodenja);
	return 0;
}
int DeleteElement(Position head, Position toDelete) {
	printf("\r\nIz liste se brise: %s %s %d", toDelete->ime, toDelete->prezime, toDelete->godinaRodenja);
	if (head->next == toDelete)
		head->next = toDelete->next;
	if (toDelete->next != NULL)
		toDelete->next->prev = toDelete->prev;
	if (toDelete->prev != NULL)
		toDelete->prev->next = toDelete->next;
	free(toDelete);
	printf("\r\nElement uspjesno izbrisan!\r\n");
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