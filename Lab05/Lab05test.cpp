#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<concrt.h>
#define MIN_VELICINA_CLANA (0)
#define MAX_VELICINA_CLANA (9)

typedef struct _cvor* Position;
typedef struct _cvor {
	int element;
	Position next;
}Cvor;

void FreeAlocatedData(Position head);
int popuniListu(Position head);
void IspisListe(Position head);
int napraviUniju(Position prvaLista, Position drugaLista, Position unija);
int napraviUniju(Position prvaLista, Position drugaLista, Position presjek);
int GenerirajSlucajniBroj(int min, int max);
int DodajSortirano(Position head, Position newItem);
Position KreirajCvor(int element);
int DodajIzaTrenutnog(Position lista, Position newItem);

int main(int argc, char *argv[]) {
	Cvor prvaLista;
	Cvor drugaLista;
	Cvor unija;
	Cvor presjek;

	prvaLista.next = NULL;
	drugaLista.next = NULL;
	unija.next = NULL;
	presjek.next = NULL;

	FreeAlocatedData(&prvaLista);
	FreeAlocatedData(&drugaLista);
	FreeAlocatedData(&unija);
	FreeAlocatedData(&presjek);
	return 0;
}
void FreeAlocatedData(Position head) {
	Position temp;
	temp = (Position)malloc(sizeof(Cvor));
	while (head->next != NULL)
	{
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
}
int popuniListu(Position head) {

	return 0;
}
void IspisListe(Position head) {

}
int napraviUniju(Position prvaLista, Position drugaLista, Position unija) {

	return 0;
}
int GenerirajSlucajniBroj(int min, int max) {

	return 0;
}
int DodajSortirano(Position head, Position newItem) {

	return 0;
}
Position KreirajCvor(int element) {
	Position newItem;
	newItem = (Position)malloc(sizeof(Cvor));
	if (newItem == NULL)
		printf("\r\nDoslo je do greske prilikom alokacije memorije!\r\n");
	else
	{

	}
	return newItem;
}
int DodajIzaTrenutnog(Position lista, Position newItem) {

	return 0;
}