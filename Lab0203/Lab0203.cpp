#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#define STRING_MAX_LENGHT 50
#define EMPTY_LIST "\r\nLista je prazna!"
#define ALLOCATION_ERROR "\r\nDoslo je do greske prilikom alokacije memorije!"
#define FILE_OPEN_ERROR "\r\nDoslo je do greske prilikom otvaranja datoteke <%s>!"
#define WRONG_INPUT "\r\nPogresan unos <%c>!\r\nPokusajte ponovno!"

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
int Insert(Position head, StudentPodaci studentPodaci);
int PrintList(Position head);
int PrintElement(Position head);
int InsertOnEnd(Position head, StudentPodaci studentPodaci);
Position FindPreviousElement(Position head, char *prezime);
int DeleteElement(Position head);
int InsertBefore(Position head, StudentPodaci studentPodaci);
int InsertAfter(Position head, StudentPodaci studentPodaci);
int SortList(Position head);
int PrintListToFile(Position head);
int ReadListFromFile(Position);
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
			bufferStudent = GetStudentDataFromConsole();
			InsertOnEnd(&head, bufferStudent);
			break;
		case '4':
			printf("\r\nUneiste ime studenta kojeg trazite: ");
			scanf(" %s", prezime);
			bufferPosition = FindPreviousElement(&head, prezime);
			if (bufferPosition == NULL)
				printf("\r\nStudent kojeg trazite nije upisan u listu!");
			else
				PrintElement(bufferPosition->next);
			break;
		case '5':
			printf("\r\nUneiste ime studenta kojeg trazite: ");
			scanf(" %s", prezime);
			bufferPosition = FindPreviousElement(&head, prezime);
			if (bufferPosition == NULL)
				printf("\r\nStudent kojeg trazite nije upisan u listu!");
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
		case '8':
			SortList(&head);
			PrintList(head.next);
			break;
		case '9':
			PrintListToFile(&head);
			break;
		case 'A':
			ReadListFromFile(&head);
			PrintList(head.next);
			break;
		case 'k':
		case 'K':
			printf("\r\nIzlaz iz programa!\r\n");
			break;
		default:
			printf(WRONG_INPUT, izbor);
			break;
		}
	}
	DeleteAll(&head);
	return 0;
}
int PrintMenu() {
	printf("\r\n1.Ubacivanje elementa na pocetak liste.");
	printf("\r\n2.Ispis liste.");
	printf("\r\n3.Ubacivanje elementa na kraj liste.");
	printf("\r\n4.Pronadi element po prezimenu.");
	printf("\r\n5.Izbrisi element po prezimenu.");
	printf("\r\n6.Ubacivanje elementa ispred elementa.");
	printf("\r\n7.Ubacivanje elementa nakon elementa.");
	printf("\r\n8.Sortiraj listu.");
	printf("\r\n9.Upisivanje liste u datoteku.");
	printf("\r\nA.Citanje liste iz datoteke.");
	printf("\r\nK.Kraj programa.");
	printf("\r\nVas odabir: ");
	return 0;
}
StudentPodaci GetStudentDataFromConsole() {
	StudentPodaci tempData;
	printf("\r\nUnesite ime, prezime i godinu rodenja studenta: ");
	scanf(" %s %s %d", tempData.ime, tempData.prezime, &tempData.godinaRodenja);
	return tempData;
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
	}
	return 0;
}
int PrintList(Position head) {
	if (head == NULL)
		printf(EMPTY_LIST);
	else
	{
		while (head!=NULL)
		{
			printf(" %s %s %d\r\n", head->ime, head->prezime, head->godinaRodenja);
			head = head->next;
		}
	}
	return 0;
}
int PrintElement(Position head) {
	printf(" %s %s %d\r\n", head->ime, head->prezime, head->godinaRodenja);
	return 0;
}
int InsertOnEnd(Position head, StudentPodaci studentPodaci) {
	while (head->next != NULL)
		head = head->next;
	Insert(head, studentPodaci);
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
	temp = head->next;
	printf("\r\nIz liste se brise: %s %s %d", temp->ime, temp->prezime, temp->godinaRodenja);
	head->next = temp->next;
	free(temp);
	printf("\r\nElement uspjenso izbrisan iz liste!\r\n");
	return 0;
}
int InsertBefore(Position head, StudentPodaci studentPodaci) {
	Position prev;
	char prezime[STRING_MAX_LENGHT];
	printf("\r\nUnesite prezime studenta ispred kojeg upisujete element: ");
	scanf(" %s", prezime);
	prev = FindPreviousElement(head, prezime);
	if (prev == NULL)
		printf("\r\nStudent kojeg trazite nije upisan u listu!\r\n");
	else
		Insert(prev, studentPodaci);
	return 0;
}
int InsertAfter(Position head, StudentPodaci studentPodaci) {
	Position prev;
	char prezime[STRING_MAX_LENGHT];
	printf("\r\nUnesite prezime studenta ispred kojeg upisujete element: ");
	scanf(" %s", prezime);
	prev = FindPreviousElement(head, prezime);
	if (prev == NULL)
		printf("\r\nStudent kojeg trazite nije upisan u listu!\r\n");
	else
		Insert(prev->next, studentPodaci);
	return 0;
}
int SortList(Position head) {
	Position end = NULL, i, j, prev_j, temp;
	while (head->next != end)
	{
		i = head;
		prev_j = i->next;
		j = prev_j->next;

		while (j != end)
		{
			if (strcmpi(prev_j->prezime, j->prezime) > 0)
			{
				prev_j->next = j->next;
				i->next = j;
				j->next = prev_j;
			}
			else
				i = prev_j;
			prev_j = j;
			j = j->next;
		}
		end = prev_j;
	}
	return 0;
}
int PrintListToFile(Position head) {
	FILE *fp;
	char fileName[STRING_MAX_LENGHT];
	printf("\r\nUnesite naziv datoteke za pisanje: ");
	scanf(" %s", fileName);
	fp = fopen(fileName, "w");
	if (fp == NULL)
		printf(FILE_OPEN_ERROR, fileName);
	else
	{
		while (head != NULL)
		{
			fprintf(fp, " %s %s %d\r\n", head->ime, head->prezime, head->godinaRodenja);
			head = head->next;
		}
		fclose(fp);
	}
	return 0;
}
int ReadListFromFile(Position head) {
	FILE *fp;
	Position temp;
	char fileName[STRING_MAX_LENGHT];
	char buffer[STRING_MAX_LENGHT];
	printf("\r\nUnesite naziv datoteke za citanje: ");
	scanf(" %s", fileName);
	fp = fopen(fileName, "r");
	if (fp == NULL)
		printf(FILE_OPEN_ERROR, fileName);
	else
	{
		while (!feof(fp))
		{
			temp = (Position)malloc(sizeof(Student));
			if (temp == NULL)
				printf(ALLOCATION_ERROR);
			else
			{
				if (fgets(buffer, STRING_MAX_LENGHT, fp) !=NULL)
				{
					sscanf(buffer, "%s %s %d", temp->ime, temp->prezime, &temp->godinaRodenja);
					temp->next = head->next;
					head->next = temp;
					head = head->next;
				}
			}
		}
		fclose(fp);
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
	printf("\r\nLista uspjesno izbrisana!");
	return 0;
}
