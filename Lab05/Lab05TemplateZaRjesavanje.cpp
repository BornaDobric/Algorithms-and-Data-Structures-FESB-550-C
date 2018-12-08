#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include <concrt.h>
#define MINIMALNA_VELICINA_CLANA (0)
#define MAKSIMALNA_VELICINA_CLANA (9)

typedef struct _cvor* Position;
typedef struct _cvor
{
	int broj;
	Position next;
}Cvor;

void FreeAlocatedData(Position);
int PopuniListu(Position);
void IspisListe(Position);

int NapraviUniju(Position prvaLista, Position drugaLista, Position unija);
int NapraviPresjek(Position prvaLista, Position drugaLista, Position presjek);
int GenerirajSlucajniBroj(int min, int max);
int DodajSortirano(Position, Position);
Position KreirajCvor(int);
int DodajIzaTrenutnog(Position lista, Position newItem);

int main(int argc, char *argv[])
{
	Cvor prvaLista;
	Cvor drugaLista;
	Cvor unija;
	Cvor presjek;

	prvaLista.next = NULL;
	drugaLista.next = NULL;
	unija.next = NULL;
	presjek.next = NULL;

	/*NADOPUNITI*/

	FreeAlocatedData(&prvaLista);
	FreeAlocatedData(&drugaLista);
	FreeAlocatedData(&unija);
	FreeAlocatedData(&presjek);

	return 0;
}

int PopuniListu(Position head)
{
	return 0;
}
void IspisListe(Position position)
{
	while (position != NULL)
	{
		printf("%d ", position->broj);
		position = position->next;
	}
	printf("\n");
}
int GenerirajSlucajniBroj(int min, int max)
{
	return 0;
}
Position KreirajCvor(int broj)
{
	return  NULL;
}
int DodajIzaTrenutnog(Position lista, Position newItem)
{
		return -1;
}

int DodajSortirano(Position head, Position newItem)
{
	return -1;
}
int NapraviUniju(Position prvaLista, Position drugaLista, Position unija)
{
	
	return 0;
}
void FreeAlocatedData(Position)
{
	
}
int NapraviPresjek(Position prvaLista, Position drugaLista, Position presjek)
{
	
	return 0;
}
