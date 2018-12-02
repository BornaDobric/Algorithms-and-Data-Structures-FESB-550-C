#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define STRING_MAX_LENGHT (50)

typedef struct _osoba* Position;

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

int Insert(Position head, StudentPodaci studentPodaci);
int InsertEnd(Position position, StudentPodaci studentPodaci);
void IspisListe(Position head);
int DeleteElement(Position position);
Position FindPreviousElement(Position head, char *prezime);

int InsertBefore(Position position, StudentPodaci studentPodaci);
int InsertAfter(Position position, StudentPodaci studentPodaci);
int IspisIzbornika();
void PrintElement(Position position);
StudentPodaci GetStudentDataFromConsole();
void FreeAlocatedData(Position head,StudentPodaci studentPodaci);
void SortList(Position head);
void PrintListToFile(Position P);
void ReadListFromFile(Position P);

int main() {
	Student head;
	StudentPodaci bufferStudent;
	Position bufferPosition;
	char izbor = 0;
	char prezime[STRING_MAX_LENGHT];

	head.next = NULL; //lista je prazna
	while ((izbor != 'k') && (izbor != 'K'))
	{
		IspisIzbornika();
		scanf(" %c", &izbor);
		switch (izbor)
		{
		case '1':
			bufferStudent = GetStudentDataFromConsole(); 
			Insert(&head, bufferStudent);
			break;
		case '2':
			IspisListe(&head);
			break;
		case '3':
			bufferStudent = GetStudentDataFromConsole();
			InsertEnd(&head, bufferStudent);
			break;
		case '4':
			printf("\r\nUnesite prezime koje trazite: ");
			scanf(" %s", prezime);
			bufferPosition = FindPreviousElement(&head, prezime); //bufferPosition cuva pokazivac na iduci element
			if (bufferPosition==NULL)
				printf("\r\nElement ne postoji u listi!\r\n");
			else
				PrintElement(bufferPosition->next);
			break;
		case '5':
			printf("\r\nUnesite prezime koje trazite: ");
			scanf(" %s", prezime);
			bufferPosition = FindPreviousElement(&head, prezime);
			if (bufferPosition == NULL)
				printf("\r\nElement ne postoji u listi!\r\n");
			else
			{
				DeleteElement(bufferPosition); //salje se bufferPosition, a ne bufferPosition->next sta pokazuje na elemnt nakon za ispis
				IspisListe(&head);
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
			IspisListe(&head);
			break;
		case '9':
			PrintListToFile(&head);
			break;
		case 'A':
			ReadListFromFile(&head);
			IspisListe(head.next);
			break;
		default:
			printf("\r\nPogresan izbor <%c>!\r\nPokusajte ponovno.\r\n", izbor);
			break;
		}
	}
	//FreeAlocatedData(&head,bufferStudent); ERROR sa heapon!?
}
int Insert(Position head, StudentPodaci studentPodaci) {
	Position temp;
	temp = (Position)malloc(sizeof(StudentPodaci));
	if (temp == NULL)
		printf("\r\nDoslo je do greske prilikom alokacije memorije!\r\n");
	else
	{
		strcpy(temp->ime, studentPodaci.ime); //kopiranje podataka u temp
		strcpy(temp->prezime, studentPodaci.prezime);
		temp->godinaRodenja = studentPodaci.godinaRodenja;

		temp->next = head->next; //promjena pokazivaca
		head->next = temp; //promjena pokazivaca
	}

	return 0;
}
int InsertEnd(Position position, StudentPodaci studentPodaci) {
	while (position->next != NULL) //prolazak do kraja liste, prije NULLa
		position = position->next;
	Position temp;
	temp = (Position)malloc(sizeof(StudentPodaci));
	if (temp == NULL)
		printf("\r\nDoslo je do greske prilikom alokacije memorije!\r\n");
	else
	{
		strcpy(temp->ime, studentPodaci.ime); //kopiranje podataka u temp
		strcpy(temp->prezime, studentPodaci.prezime);
		temp->godinaRodenja = studentPodaci.godinaRodenja;

		temp->next = position->next; //promjena pokazivaca
		position->next = temp;
	}
	return 0;
}
void IspisListe(Position head) {
	if (head->next == NULL)
		printf("\r\nLista je prazna!\r\n");
	else
	{
		printf("\r\nU listi se nalaze: \r\n");
		while (head->next != NULL)
		{
			printf(" %s %s %d", head->next->ime, head->next->prezime, head->next->godinaRodenja);
			head = head->next; //sljedeci element
			printf("\r\n");
		}
	}
}
int DeleteElement(Position position) {
	Position temp;
	temp = (Position)malloc(sizeof(StudentPodaci));
	temp = position->next; //temp drzi element koji brisemo
	if (temp!=NULL)
	{
		position->next = temp->next; //promjena pokazivaca
		printf("\nIz liste se brise: %s %s %d\n\n", temp->ime, temp->prezime, temp->godinaRodenja);
	}
	//free(temp); ERROR sa heapon!?
	printf("\r\nUspjesno obrisano!\r\n"); //izbacuje HEAP ERROR!?
	return 0;
}
Position FindPreviousElement(Position position, char *prezime) {
	Position temp;
	while ((position->next != NULL) && (strcmpi(position->next->prezime, prezime)!=0)) //dok element nije kraj liste ili dok element nije trazeno prezime
		position = position->next; //iduci element
	if (position->next == NULL)
		position = NULL; //element ne postoji u listi 
	return position;
}
int InsertBefore(Position position, StudentPodaci studentPodaci) {
	Position prev;
	char prezime[STRING_MAX_LENGHT];
	printf("\r\nUnesite prezime: \r\n");
	scanf(" %s", prezime);
	prev = (Position)malloc(sizeof(StudentPodaci));
	if (prev == NULL)
		printf("\r\nDoslo je do greske prilikom alokacije memorije!\r\n");
	else
	{
		prev = FindPreviousElement(position, prezime); //trazenje prethodnog elementa
		if (prev == NULL)
			printf("\r\nElement nije pronaden!\r\n");
		else
			Insert(prev, studentPodaci); //Insert() funkcija ce implementirat ostatak, kod se poklapa, prev se salje
	}
	return 0;
}
int InsertAfter(Position position, StudentPodaci studentPodaci) {
	Position prev;
	char prezime[STRING_MAX_LENGHT];
	printf("\r\nUnesite prezime: \r\n");
	scanf(" %s", prezime);
	prev = (Position)malloc(sizeof(StudentPodaci));
	if (prev == NULL)
		printf("\r\nDoslo je do greske prilikom alokacije memorije!\r\n");
	else
	{
		prev = FindPreviousElement(position, prezime); //trazenje prethodnog elementa
		if (prev == NULL)
			printf("\r\nElement nije pronaden!\r\n");
		else
			Insert(prev->next, studentPodaci); //Insert() funkcija ce implementirat ostatak, kod se poklapa, temp->next se salje
	}
	return 0;
}
int IspisIzbornika() {
	printf("\r\n\r\n");
	printf("\t1. Unos elementa u listu\r\n");
	printf("\t2. Ispis liste\r\n");
	printf("\t3. Unos na kraj\r\n");
	printf("\t4. Pronadji po prezimenu\r\n");
	printf("\t5. Izbrisi po prezimenu\r\n");
	printf("\t6. Unos ispred elementa\r\n");
	printf("\t7. Unos nakon elementa\r\n");
	printf("\t8. Sortiraj listu po prezimenima\r\n");
	printf("\t9. Upisi listu u datoteku\r\n");
	printf("\tA. Citaj listu iz datoteke\r\n");
	printf("\tK. Izlaz iz programa\r\n");
	printf("\r\n\tIzbor : ");
	return 0;
}
void PrintElement(Position position) {
	printf("\r\n%s %s %d\r\n", position->ime, position->prezime, position->godinaRodenja);
}
StudentPodaci GetStudentDataFromConsole() {
	StudentPodaci tempPodaci;
	printf("\r\nUnesite ime, prezime i godinu rodenja: \r\n");
	scanf(" %s %s %d", tempPodaci.ime, tempPodaci.prezime, &tempPodaci.godinaRodenja);
	return tempPodaci;
}
void FreeAlocatedData(Position head, StudentPodaci studentPodaci) {
	Position temp;
	temp = (Position)malloc(sizeof(StudentPodaci));
	while (head->next!=NULL)
	{
		temp = head->next; // pomicanje pokazivaca na iduci element, cuvamo u temp
		head->next = temp->next;
		free(temp);
	}
}
void SortList(Position head) {
	Position end = NULL, i, j, prev_j, temp;
	while (head->next!=end) //end je NULL, dok nije kraj liste
	{
		i = head;
		prev_j = i->next;
		j = prev_j->next;

		while (j!=end)
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
}
void PrintListToFile(Position head) {
	FILE *fp;
	char fileName[STRING_MAX_LENGHT];
	head = head->next; //jer inace ulazi samo head na kojen nema elementa nego pokazuje pocetak liste
	printf("\r\nUnesite naziv datoteke za pisanje: \r\n");
	scanf(" %s", fileName);
	fp = fopen(fileName, "w"); //otvori dat za pisanje
	if (fp == NULL)
		printf("\r\nDoslo je do greske prilikom otvaranja datoteke <%s> za pisanje!\r\n", fileName);
	else
	{
		while (head!=NULL) //dok nije kraj liste
		{
			fprintf(fp, "\r\n%s %s %d\r\n", head->ime, head->prezime, head->godinaRodenja); //pisi elemente u dat
			head = head->next; //pokazivac na iduci
		}
		fclose(fp);
	}
}
void ReadListFromFile(Position head) {
	FILE *fp;
	char fileName[STRING_MAX_LENGHT];
	Position temp;
	printf("\r\nUnesite ime datoteke za citanje liste: \r\n");
	scanf(" %s", fileName);
	fp = fopen(fileName, "r"); //otvori dat za citanje
	if (fp==NULL)
		printf("\r\nDoslo je do greske prilikom otvaranja datoteke <%s> za pisanje!\r\n", fileName);
	else
	{
		while (!feof(fp)) //dok nije kraj datoteke
		{
			temp = (Position)malloc(sizeof(StudentPodaci));
			if (temp == NULL)
				printf("\r\nDoslo je do greske prilikom alokacije memorije!\r\n");
			else
			{
				fscanf(fp," %s %s %d", temp->ime, temp->prezime, &temp->godinaRodenja); //ucitaj podatke u temp
				temp->next = head->next; // promjena pokazivaca na iduci element
				head->next = temp;
			}
		}
		fclose(fp); //zatvaranje dat
	}
}
