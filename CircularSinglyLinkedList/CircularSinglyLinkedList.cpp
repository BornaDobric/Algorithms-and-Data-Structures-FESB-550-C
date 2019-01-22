#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#define STRING_MAX_LENGHT 50
#define ALLOCATION_ERROR "\r\nDoslo je do greske prilikom alokacije memorije!"
#define EMPTY_LIST "\r\nLista je prazna!\r\n"
#define INPUT_ERROR "\r\nPogresan unos <%c>! Pokusajte ponovno.\r\n"
#define NO_STUDENT_IN_FILE "\r\nStudent kojeg trazite nije upisan u listu!"

typedef struct _student* Position;
typedef struct _student {
	int godinaRodenja;
	char ime[STRING_MAX_LENGHT];
	char prezime[STRING_MAX_LENGHT];
	Position next;
}Student;

typedef struct _studentPodaci {
	int godinaRodenja;
	char ime[STRING_MAX_LENGHT];
	char prezime[STRING_MAX_LENGHT];
}StudentPodaci;

int PrintMenu();
StudentPodaci GetStudentDataFromConsole();
int InsertOnBeggining(Position head, StudentPodaci studentPodaci);
int PrintList(Position head);
int PrintElement(Position head);
int InsertOnEnd(Position head, StudentPodaci studentPodaci);
Position FindPreviousElement(Position head, char *prezime);
int DeleteElement(Position head);
int InsertBefore(Position head, StudentPodaci studentPodaci);
int InsertAfter(Position head, StudentPodaci studentPodaci);
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
			InsertOnBeggining(&head, bufferStudent);
			break;
		case '2':
			PrintList(head.next);
			break;
		case '3':
			bufferStudent = GetStudentDataFromConsole();
			InsertOnEnd(&head, bufferStudent);
			break;
		case '4':
			printf("\r\nUnesite prezime student akojeg trazite u listi: ");
			scanf(" %s", prezime);
			bufferPosition = FindPreviousElement(&head, prezime);
			if (bufferPosition == NULL)
				printf(NO_STUDENT_IN_FILE);
			else
				PrintElement(bufferPosition->next);
			break;
		case '5':
			printf("\r\nUnesite prezime student akojeg trazite u listi: ");
			scanf(" %s", prezime);
			bufferPosition = FindPreviousElement(&head, prezime);
			if (bufferPosition == NULL)
				printf(NO_STUDENT_IN_FILE);
			else
			{
				DeleteElement(bufferPosition);
				PrintList(head.next);
			}
			break;
		case '6':
			bufferStudent = GetStudentDataFromConsole();
			InsertBefore(&head, bufferStudent);
			break;
		case '7':
			bufferStudent = GetStudentDataFromConsole();
			InsertAfter(&head, bufferStudent);
			break;
		case 'k':
		case 'K':
			printf("\r\nIzlaz iz programa!\r\n");
			break;
		default:
			printf(INPUT_ERROR, izbor);
			break;
		}
	}
	DeleteAll(&head);
	PrintList(head.next);
	return 0;
}
int PrintMenu() {
	printf("\r\n1.Unos elementa na pocetak liste.");
	printf("\r\n2.Ispis liste.");
	printf("\r\n3.Unos elementa na kraj liste.");
	printf("\r\n4.Pronadi element po prezimenu.");
	printf("\r\n5.Izbrisi element po prezimenu.");
	printf("\r\n6.Unos ispred elementa trazenog po prezimenu.");
	printf("\r\n7.Unos nakon elementa trazenog po prezimenu.");
	printf("\r\nK.Kraj programa");
	printf("\r\nVas odabir: ");
	return 0;
}
StudentPodaci GetStudentDataFromConsole() {
	StudentPodaci tempData;
	printf("\r\nUnesite ime, prezime i godinu rodenja studenta: ");
	scanf(" %s %s %d", tempData.ime, tempData.prezime, &tempData.godinaRodenja);
	return tempData;
}
int InsertOnBeggining(Position head, StudentPodaci studentPodaci) {
	Position temp, first, last;
	first = head->next;
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
			temp->next = temp; //prvi je element upisan u listu pa ce pokazivat sam na sebe
			head->next = temp; //head ce pokazivat na njega kao prvi clan, a ne na NULL kao na pocetku
		}
		else
		{
			while (first->next!=head->next) //dok je iduci element razlicit od prvog elementa liste
				first = first->next; // iduci element
			last = first; //last je jednak zadnjem koji izade iz petlje, taj je element zadnji i pokazuje na prvi element u listi
			temp->next = last->next; //temp ce pokazivat na onaj na koji je zadnji element pokazivao
			last->next = temp; //zadnji ce sad pokazivat na temp
			head->next = temp; //temp postaje prvi element u listi
		}
	}
	return 0;
}
int PrintList(Position head) {
	Position temp;
	temp = head;
	if (head == NULL)
		printf(EMPTY_LIST);
	else
	{
		do
		{
			printf(" %s %s %d\r\n", temp->ime, temp->prezime, temp->godinaRodenja);
			temp = temp->next;
		} while (temp!=head);
	}
	return 0;
}
int PrintElement(Position head) {
	printf(" %s %s %d\r\n", head->ime, head->prezime, head->godinaRodenja);
	return 0;
}
int InsertOnEnd(Position head, StudentPodaci studentPodaci) {
	Position temp, first, last;
	first = head->next;
	temp = (Position)malloc(sizeof(Student));
	if (temp == NULL)
		printf(ALLOCATION_ERROR);
	else
	{
		strcpy(temp->ime, studentPodaci.ime);
		strcpy(temp->prezime, studentPodaci.prezime);
		temp->godinaRodenja = studentPodaci.godinaRodenja;

		if (head->next == NULL)
		{
			temp->next = temp; //prvi je element upisan u listu pa ce pokazivat sam na sebe
			head->next = temp; //head ce pokazivat na njega kao prvi clan, a ne na NULL kao na pocetku
		}
		else
		{
			while (first->next != head->next) //dok je iduci element razlicit od prvog elementa liste
				first = first->next; // iduci element
			last = first; //last je jednak zadnjem koji izade iz petlje, taj je element zadnji i pokazuje na prvi element u listi
			temp->next = last->next; //temp pokazuje na ono sto je pokazivao zadnji element u listi odnosno na prvi element u listi
			last->next = temp; //trenutni zadnji pokazuje na dodani temp
			last = temp; //temp postaje zadnji element u listi tj. last
		}
	}
	return 0;
}
Position FindPreviousElement(Position head, char *prezime) {
	while (head->next != NULL && strcmpi(head->next->prezime, prezime) != 0)
		head = head->next;
	if (head->next == NULL)
		return NULL;
	return head;
}
int DeleteElement(Position head) {
	Position temp;
	temp = head->next; //pokazivac na iduci element jer smo mi poslali u funkciju prethodni element
	if (temp->next == temp) { //ako je element koji se brise jedini u preostali u listi
		printf("\r\nIz liste se brise: %s %s %d\r\n", temp->ime, temp->prezime, temp->godinaRodenja);
		free(temp);
		printf("\r\nStudent uspjesno izbrisan!\r\n");
		head->next = NULL; //lista ce biti prazna - head->next ce pokazivati na NULL
	}
	else
	{	//klasika brisanje
		temp = head->next;
		head->next = temp->next;
		printf("\r\nIz liste se brise: %s %s %d\r\n", temp->ime, temp->prezime, temp->godinaRodenja);
		free(temp);
		printf("\r\nStudent uspjesno izbrisan!\r\n");
	}
	return 0;
}
int InsertBefore(Position head, StudentPodaci studentPodaci) {
	Position temp, first, last;
	Position prev;
	char prezime[STRING_MAX_LENGHT];
	printf("\r\nUnesite prezime studenta ispred kojeg upisujete: ");
	scanf(" %s", prezime);
	first = head->next;
	temp = (Position)malloc(sizeof(Student));
	if (temp == NULL)
		printf(ALLOCATION_ERROR);
	else
	{
		prev = FindPreviousElement(head, prezime);
		if (prev == NULL)
			printf(NO_STUDENT_IN_FILE);
		else
		{
			strcpy(temp->ime, studentPodaci.ime);
			strcpy(temp->prezime, studentPodaci.prezime);
			temp->godinaRodenja = studentPodaci.godinaRodenja;
			
			while (first->next != head->next) //dok je iduci element razlicit od prvog elementa liste
				first = first->next; // iduci element
			last = first; //last je jednak zadnjem koji izade iz petlje, taj je element zadnji i pokazuje na prvi element u listi

			temp->next = prev->next;
			prev->next = temp;
			if (prev == head)
			{
				temp->next = last->next;
				last->next = temp;
				head->next = temp;
			}
		}
	}
	return 0;
}
int InsertAfter(Position head, StudentPodaci studentPodaci) {
	Position temp, first, last;
	Position prev;
	char prezime[STRING_MAX_LENGHT];
	printf("\r\nUnesite prezime studenta ispred kojeg upisujete: ");
	scanf(" %s", prezime);
	first = head->next;
	temp = (Position)malloc(sizeof(Student));
	if (temp == NULL)
		printf(ALLOCATION_ERROR);
	else
	{
		prev = FindPreviousElement(head, prezime);
		if (prev == NULL)
			printf(NO_STUDENT_IN_FILE);
		else
		{
			strcpy(temp->ime, studentPodaci.ime);
			strcpy(temp->prezime, studentPodaci.prezime);
			temp->godinaRodenja = studentPodaci.godinaRodenja;

			while (first->next != head->next) //dok je iduci element razlicit od prvog elementa liste
				first = first->next; // iduci element
			last = first; //last je jednak zadnjem koji izade iz petlje, taj je element zadnji i pokazuje na prvi element u listi

			temp->next = prev->next->next;
			prev->next->next = temp;
			if (prev->next->next==first)
			{
				temp->next = last->next;
				last->next = temp;
				last = temp;
			}
		}
	}
	return 0;
}
int DeleteAll(Position head) {
	Position temp, first;
	first = head->next;
	printf("\r\nBrisanje cijele liste...");
	while (first->next != head->next)
	{
		temp = first->next;
		first->next = temp->next;
		free(temp);
	}
	free(head->next);
	head->next = NULL;
	printf("\r\nLista uspjesno izbrisana!\r\n");
	return 0;
}