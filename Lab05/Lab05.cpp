#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define STRING_MAX_SIZE (50)

typedef struct _cvor* Position;
typedef struct _cvor {
	int element;
	Position next;
}Cvor;

int ReadFromFile(Position head);
int Push(Position head, int broj);
Position CreateElement(int broj);
int GetUnija(Position lista1, Position lista2, Position unija);
int GetPresjek(Position lista1, Position lista2, Position presjek);
int PrintList(Position head);
int DeleteAll(Position head);

int main(int argc, char *argv[]) {
	Cvor lista1;
	Cvor lista2;
	Cvor unija;
	Cvor presjek;

	lista1.next = NULL;
	lista2.next = NULL;
	unija.next = NULL;
	presjek.next = NULL;

	ReadFromFile(&lista1);
	ReadFromFile(&lista2);

	printf("\r\nLista 1: \r\n");
	PrintList(lista1.next);
	printf("\r\nLista 2: \r\n");
	PrintList(lista2.next);

	GetUnija(&lista1, &lista2, &unija);
	GetPresjek(&lista1, &lista2, &presjek);

	printf("\r\nUnija: \r\n");
	PrintList(unija.next);
	printf("\r\nPresjek: \r\n");
	PrintList(presjek.next);

	DeleteAll(&lista1);
	DeleteAll(&lista2);
	DeleteAll(&unija);
	DeleteAll(&presjek);

	return 0;
}
int ReadFromFile(Position head) {
	FILE *fp;
	char fileName[STRING_MAX_SIZE];
	int buffer;
	printf("\r\nUnesite ime datoteke za citanje liste: \r\n");
	scanf(" %s", fileName);
	fp = fopen(fileName, "r");
	if (fp == NULL)
		printf("\r\nDoslo je do greske prilikom otvaranja datoteke!\r\n");
	else
	{
		while (!feof(fp))
		{
			fscanf(fp, " %d", &buffer);
			Push(head, buffer); //u buffer je spremljen int iz datoteke
		}
	}
	fclose(fp);
	return 0;
}
int Push(Position head, int broj) {
	Position newElement;
	newElement = CreateElement(broj);

	while (head->next != NULL) //dok nije kraj liste
		head = head->next; //iduci element
	newElement->next = head->next; //postavljanje elementa u listu
	head->next = newElement; //promjena pokazivaca
	return 0;
}
Position CreateElement(int broj) {
	Position temp;
	temp = (Position)malloc(sizeof(Cvor));
	if (temp == NULL)
		printf("\r\nDoslo je do greske prilikom alokacije memorije!\r\n");
	else
	{
		temp->element = broj; //spremanje procitanog broja u listu
		temp->next = NULL;
	}
	return temp;
}
int GetUnija(Position lista1, Position lista2, Position unija) {
	Position temp1;
	Position temp2;
	temp1 = lista1->next; //zbog lakseg snalazenja 
	temp2 = lista2->next;
	while (temp1!=NULL && temp2!=NULL) //dok nije kraj ni prve ni druge liste
	{
		if (temp1->element == temp2->element)
		{
			Push(unija, temp1->element); //ako su jednaki upisi u uniju bilo koji
			temp1 = temp1->next; //iduci element temp1 liste
			temp2 = temp2->next; //iduci element temp2 liste
		}
		else if (temp1->element > temp2->element)
		{
			Push(unija, temp2->element);
			temp2 = temp2->next; //iduci element temp2 liste
		}
		else
		{	//ako je el. prve liste manji od el. druge liste
			Push(unija, temp1->element);
			temp1 = temp1->next; //iduci element temp1 liste
		}
	}
	while (temp1!=NULL)
	{	//proc ostatak liste koji nisu isli kroz gornju uvjetnu while petlju i upisat u uniju elemente
		Push(unija, temp1->element);
		temp1 = temp1->next;
	}
	while (temp2 != NULL)
	{	//proc ostatak liste koji nisu isli kroz gornju uvjetnu while petlju i upisat u uniju elemente
		Push(unija, temp2->element);
		temp2 = temp2->next;
	}
	return 0;
}
int GetPresjek(Position lista1, Position lista2, Position presjek) {
	Position temp1;
	Position temp2;
	temp1 = lista1->next;
	temp2 = lista2->next;

	while (temp1->next!=NULL && temp2->next!=NULL)
	{
		if (temp1->element == temp2->element)
		{	//ako su jednaki pisi ih u presjek
			Push(presjek, temp1->element);
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		else if (temp1->element > temp2->element)
		{	//brokvaj
			temp2 = temp2->next;
		}
		else
		{	//brokvaj
			temp1 = temp1->next;
		}
	}
	return 0;
}
int PrintList(Position head) {
	while (head != NULL)
	{
		printf(" %d", head->element);
		head = head->next;
	}
	printf("\r\n");
	return 0;
}
int DeleteAll(Position head) {
	Position temp;
	while (head->next!=NULL)
	{
		temp = head->next; //klasika brisanje elemenata
		head->next = temp->next; //promjena pokazivaca
		free(temp); //oslobodi temp
	}
	return 0;
}
