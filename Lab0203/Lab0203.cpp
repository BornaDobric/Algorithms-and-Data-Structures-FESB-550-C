#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#define STRING_MAX_LENGHT 50

typedef struct _osoba*Position;
typedef struct _osoba {
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
StudentPodaci GetStudentData();
int Insert(Position head, StudentPodaci studentPodaci);
int InsertOnEnd(Position head, StudentPodaci studentPodaci);
int PrintList(Position head);
int PrintElement(Position head);
Position FindPrevious(Position head, char *prezime);
int DeleteElement(Position position);
int DeleteAll(Position head);

int InsertBefore(Position head, StudentPodaci studentPodaci);
int InsertAfter(Position head, StudentPodaci studentPodaci);
int ReadListFromFile(Position head);
int PrintListToFile(Position head);
int Sort(Position head);

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
			bufferStudent = GetStudentData();
			Insert(&head, bufferStudent);
			break;
		case '2':
			PrintList(head.next);
			break;
		case '3':
			bufferStudent = GetStudentData();
			InsertOnEnd(&head, bufferStudent);
			break;
		case '4':
			printf("\r\nUnesite prezime studenta kojeg trazite: ");
			scanf(" %s", prezime);
			bufferPosition = FindPrevious(&head, prezime);
			if (bufferPosition == NULL)
				printf("\r\nElement ne postoji u listi!\r\n");
			else
				PrintElement(bufferPosition->next);
			break;
		case '5':
			printf("\r\nUnesite prezime studenta kojeg trazite: ");
			scanf(" %s", prezime);
			bufferPosition = FindPrevious(&head, prezime);
			if (bufferPosition == NULL)
				printf("\r\nElement ne postoji u listi!\r\n");
			else
			{
				DeleteElement(bufferPosition);
				PrintList(head.next);
			}
			break;
		case '6':
			bufferStudent = GetStudentData();
			InsertBefore(&head, bufferStudent);
			break;
		case '7':
			bufferStudent = GetStudentData();
			InsertAfter(&head, bufferStudent);
			break;
		case '8':
			PrintListToFile(head.next);
			break;
		case '9':
			ReadListFromFile(&head);
			PrintList(head.next);
			break;
		case 'A':
			Sort(&head);
			PrintList(head.next);
			break;
		case 'k':
		case 'K':
			printf("\r\nIzlaz iz programa!\r\n");
			break;
		default:
			printf("\r\nPogresan odabir!\r\nPokusajte ponovno!\r\n");
			break;
		}
	}
	DeleteAll(&head);
	PrintList(head.next);
	return 0;
}
int PrintMenu() {
	printf("\r\n1. Ubacivanje elementa na pocetak liste.");
	printf("\r\n2. Ispis elementa.");
	printf("\r\n3. Ubacivanje elementa na kraj liste.");
	printf("\r\n4. Pronadi po prezimenu.");
	printf("\r\n5. Izbrisi po prezimenu.");
	printf("\r\n6. Ubacivanje ispred elementa.");
	printf("\r\n7. Ubacivanje izad elementa.");
	printf("\r\n8. Upis liste u datoteku.");
	printf("\r\n9. Citanje liste iz datoteke.");
	printf("\r\nA. Sortiraj.");
	printf("\r\nK. Izlaz iz programa.");
	printf("\r\nVas odabir: \r\n");
	return 0;
}
int Insert(Position head, StudentPodaci studentPodaci) {
	Position temp;
	temp = (Position)malloc(sizeof(Student));
	if (temp == NULL)
		printf("\r\nDoslo je do greske prilikom alokacije memorije!\r\n");
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
		printf("\r\nLista je prazna!\r\n");
	else
	{
		while (head != NULL)
		{
			printf(" %s %s %d\r\n", head->ime, head->prezime, head->godinaRodenja);
			head = head->next;
		}
	}
	return 0;
}
int PrintElement(Position head) {
	printf("\r\n%s %s %d\r\n", head->ime, head->prezime, head->godinaRodenja);
	return 0;
}
int InsertOnEnd(Position head, StudentPodaci studentPodaci) {
	while (head->next != NULL)
		head = head->next;
	Insert(head, studentPodaci);
	return 0;
}
StudentPodaci GetStudentData() {
	StudentPodaci tempPodaci;
	printf("\r\nUnesite ime, prezime i godinu rodenja studenta: ");
	scanf(" %s %s %d", tempPodaci.ime, tempPodaci.prezime, &tempPodaci.godinaRodenja);
	return tempPodaci;
}
int DeleteAll(Position head) {
	Position temp;
	while (head->next!=NULL)
	{
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
	return 0;
}
Position FindPrevious(Position position, char *prezime) {
	while (position->next != NULL && strcmpi(position->next->prezime, prezime) != 0)
		position = position->next;
	if (position->next == NULL)
		return NULL;
	return position;
}
int DeleteElement(Position position) {
	Position temp;
	temp = position->next;
	if (temp!=NULL)
	{
		position->next = temp->next;
		printf("\r\nIz liste se brise: %s %s %d\r\n", temp->ime, temp->prezime, temp->godinaRodenja);
		free(temp);
	}
	printf("\r\nUspjesno obrisano!\r\n");
	return 0;
}
int InsertBefore(Position head, StudentPodaci studentPodaci) {
	Position prev;
	char prezime[STRING_MAX_LENGHT];
	printf("\r\nUnesite prezime: ");
	scanf(" %s", prezime);
	prev = (Position)malloc(sizeof(Student));
	if (prev == NULL)
		printf("\r\nDoslo je do greske prilikom alokacije memorije!\r\n");
	else
	{
		prev = FindPrevious(head, prezime);
		if (prev == NULL)
			printf("\r\nElement ne postoji u listi!\r\n");
		else
			Insert(prev, studentPodaci);
	}
	return 0;
}
int InsertAfter(Position head, StudentPodaci studentPodaci) {
	Position prev;
	char prezime[STRING_MAX_LENGHT];
	printf("\r\nUnesite prezime: ");
	scanf(" %s", prezime);
	prev = (Position)malloc(sizeof(Student));
	if (prev == NULL)
		printf("\r\nDoslo je do greske prilikom alokacije memorije!\r\n");
	else
	{
		prev = FindPrevious(head, prezime);
		if (prev == NULL)
			printf("\r\nElement ne postoji u listi!\r\n");
		else
			Insert(prev->next, studentPodaci);
	}
	return 0;
}
int ReadListFromFile(Position head) {
	FILE *fp;
	Position temp;
	char fileName[STRING_MAX_LENGHT];
	
	printf("\r\nUnesite ime datoteke za citanje: ");
	scanf(" %s", fileName);
	fp = fopen(fileName, "r");
	if (fp == NULL)
		printf("\r\nDoslo je do greske prilikom otvaranja datoteke!\r\n");
	else
	{
		while (!feof(fp))
		{
			temp = (Position)malloc(sizeof(Student));
			if (temp == NULL)
				printf("\r\nDoslo je do greske prilikom alokacije memorije!\r\n");
			fscanf(fp, " %s %s %d", temp->ime, temp->prezime, &temp->godinaRodenja);
			temp->next = head->next;
			head->next = temp;
			head = head->next;
		}
		fclose(fp);
	}
	return 0;
}
int PrintListToFile(Position head) {
	FILE *fp;
	Position temp;
	char fileName[STRING_MAX_LENGHT];
	temp = (Position)malloc(sizeof(Student));
	if (temp == NULL)
		printf("\r\nDoslo je do greske prilikom alokacije memorije!\r\n");
	printf("\r\nUnesite ime datoteke za pisanje: ");
	scanf(" %s", fileName);
	fp = fopen(fileName, "w");
	if (fp == NULL)
		printf("\r\nDoslo je do greske prilikom otvaranja datoteke!\r\n");
	else
	{
		while (head!=NULL)
		{
			fprintf(fp, " %s %s %d\r\n", head->ime, head->prezime, head->godinaRodenja);
			head = head->next;
		}
		fclose(fp);
	}
	return 0;
}
int Sort(Position head) {
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
