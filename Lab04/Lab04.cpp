#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_POLINOM_SIZE (50)

typedef struct _cvor* Position;
typedef struct _cvor {
	int eksponent;
	int koeficijent;
	Position next;
}Cvor;

int ProcitajDatoteke(char*imeDatoteke, Position pp, Position dp);
int UcitajPolinomIzStringa(char*ulazniString, Position trenutniCvor);
int DodajUListuSortirano(Position trenutniCvor, int koeficijent, int eksponent);
int KreirajCvorIDodajIzaTrenutnog(Position trenutniCvor, int koeficijent, int eksponent);
int DodajIzaTrenutnog(Position noviCvor, Position trenutniCvor);
void IspisiPolinom(char*opis, Position trenutniCvor);
int ZbrojiPolinome(Position pp, Position dp, Position sumaPolinoma);
int PomnoziPolinome(Position pp, Position dp, Position umnozakPolinoma);
void DealocirajMemoriju(Position trenutniCvor);
int main() {
	Cvor pp, dp; //pp-prvi polinom, dp-drugi polinom
	Cvor sumaPolinoma, umnozakPolinoma;
	pp.next = NULL;
	dp.next = NULL;
	sumaPolinoma.next = NULL;
	umnozakPolinoma.next = NULL;

	ProcitajDatoteke("Polinomi.txt", &pp, &dp);
	IspisiPolinom("\r\nPrvi polinom", pp.next);
	IspisiPolinom("\r\nDrugi polinom", dp.next);

	ZbrojiPolinome(&pp, &dp, &sumaPolinoma);
	IspisiPolinom("\r\nSuma polinoma", sumaPolinoma.next);
	PomnoziPolinome(&pp, &dp, &umnozakPolinoma);
	IspisiPolinom("\r\nUmnozak polinoma", umnozakPolinoma.next);

	DealocirajMemoriju(&pp);
	DealocirajMemoriju(&dp);
	DealocirajMemoriju(&sumaPolinoma);
	DealocirajMemoriju(&umnozakPolinoma);
	return 0;
}
int ProcitajDatoteke(char*imeDatoteke, Position pp, Position dp) {
	FILE *fp;
	char buffer[MAX_POLINOM_SIZE];
	fp = fopen(imeDatoteke, "r");
	if (fp == NULL)
		printf("\r\nDoslo je do greske prilikom alokacije memorije!\r\n");
	else
	{
		fgets(buffer, MAX_POLINOM_SIZE, fp); //citaj mi red iz datoteke u buffer
		UcitajPolinomIzStringa(buffer, pp); //proslijedi u funkciju buffer i prvi polinom

		fgets(buffer, MAX_POLINOM_SIZE, fp); //citaj mi red iz datoteke u buffer
		UcitajPolinomIzStringa(buffer, dp); //proslijedi u funkciju buffer i drugi polinom
	}
	return 0;
}
int UcitajPolinomIzStringa(char*ulazniString, Position trenutniCvor) {
	int koeficijent, eksponent, offset; //offset(%n) postavlja brojac ovisno o prethodno ispisanom broju znakova
	while (sscanf(ulazniString," %d %d %n",&koeficijent,&eksponent,&offset)!=EOF) //The C library function sscanf reads formatted input from a string.
	{	//EOF-end of file
		DodajUListuSortirano(trenutniCvor, koeficijent, eksponent);
		ulazniString += offset; //uvecaj za offset kako bi se citao iduci element polinoma
	}
	return 0;
}
int DodajUListuSortirano(Position trenutniCvor, int koeficijent, int eksponent) { //(trenutniCvor->next != NULL)- kako prolazi ovo ako je u mainu postavljeno da je .next=NULL; a nije se nista upisivalo u element
	while (trenutniCvor->next != NULL && trenutniCvor->next->eksponent > eksponent) //dok nije kraj liste i dok je eksponent iduceg elementa veci od eksponenta iz stringa, trazi najvecu potenciju
		trenutniCvor = trenutniCvor->next; //promjena pokazivaca na iduci element
	if (trenutniCvor->next != NULL && trenutniCvor->next->eksponent == eksponent) //ako nije kraj liste i ako je eksponent iduceg elementa jednak eksponentu iz stringa
		trenutniCvor->next->koeficijent += koeficijent; //uvecaj koeficijent iduceg elementa za koeficijent iz stringa
	else
		KreirajCvorIDodajIzaTrenutnog(trenutniCvor, koeficijent, eksponent);
	return 0;
}
int KreirajCvorIDodajIzaTrenutnog(Position trenutniCvor, int koeficijent, int eksponent) {
	Position temp;
	temp = (Position)malloc(sizeof(Cvor));
	if (temp == NULL)
		printf("\r\nDoslo je do greske prilikom alokacije memorije!\r\n");
	else
	{
		temp->koeficijent = koeficijent;
		temp->eksponent = eksponent;
		DodajIzaTrenutnog(temp, trenutniCvor);
	}
	return 0;
}
int DodajIzaTrenutnog(Position noviCvor, Position trenutniCvor) {
	noviCvor->next = trenutniCvor->next;
	trenutniCvor->next = noviCvor;
	return 0;
}
void IspisiPolinom(char*opis, Position trenutniCvor) {
	bool first = true; //prvi element
	printf("%s=", opis);
	while (trenutniCvor!=NULL) //dok nije kraj liste
	{
		if (first==true)
		{	//masu matematickih ishoda koje triba pokrit
			if (trenutniCvor->koeficijent == 1 && trenutniCvor->eksponent == 0)
				printf("1");
			if (trenutniCvor->koeficijent==-1 && trenutniCvor->eksponent==0)
				printf("-1");
			if (trenutniCvor->koeficijent == 1 && trenutniCvor->eksponent > 0)
				printf("x^%d", trenutniCvor->eksponent);
			if (trenutniCvor->koeficijent==1 && trenutniCvor->eksponent<0)
				printf("x^(%d)", trenutniCvor->eksponent);
			if (trenutniCvor->koeficijent>0 && trenutniCvor->koeficijent!=1 && trenutniCvor->eksponent>0)
				printf("%dx^%d", trenutniCvor->koeficijent,trenutniCvor->eksponent);
			if (trenutniCvor->koeficijent<0 && trenutniCvor->koeficijent!=-1 && trenutniCvor->eksponent>0)
				printf("-%dx^%d", (-1)*trenutniCvor->koeficijent, trenutniCvor->eksponent);
			if (trenutniCvor->koeficijent>0 && trenutniCvor->koeficijent!=1 && trenutniCvor->eksponent<0)
				printf("%dx^(%d)", trenutniCvor->koeficijent,trenutniCvor->eksponent);
			if (trenutniCvor->koeficijent < 0 && trenutniCvor->koeficijent != -1 && trenutniCvor->eksponent < 0)
				printf("-%dx(%d)", (-1)*trenutniCvor->koeficijent, trenutniCvor->eksponent);

			first = false; //vise nije prvi element
		}
		else
		{   //masu matematickih uvjeta samo vise nije prvi element pa se dodaju matematicke operacije
			if (trenutniCvor->koeficijent == 1 && trenutniCvor->eksponent == 0)
				printf(" + 1");
			if (trenutniCvor->koeficijent == -1 && trenutniCvor->eksponent == 0)
				printf(" - 1");
			if (trenutniCvor->koeficijent == 1 && trenutniCvor->eksponent > 0)
				printf(" + x^%d", trenutniCvor->eksponent);
			if (trenutniCvor->koeficijent == 1 && trenutniCvor->eksponent<0)
				printf(" + x^(%d)", trenutniCvor->eksponent);
			if (trenutniCvor->koeficijent>0 && trenutniCvor->koeficijent != 1 && trenutniCvor->eksponent>0)
				printf(" + %dx^%d", trenutniCvor->koeficijent, trenutniCvor->eksponent);
			if (trenutniCvor->koeficijent<0 && trenutniCvor->koeficijent != -1 && trenutniCvor->eksponent>0)
				printf(" - %dx^%d", (-1)*trenutniCvor->koeficijent, trenutniCvor->eksponent);
			if (trenutniCvor->koeficijent>0 && trenutniCvor->koeficijent != 1 && trenutniCvor->eksponent<0)
				printf(" + %dx^(%d)", trenutniCvor->koeficijent, trenutniCvor->eksponent);
			if (trenutniCvor->koeficijent < 0 && trenutniCvor->koeficijent != -1 && trenutniCvor->eksponent < 0)
				printf(" - %dx(%d)", (-1)*trenutniCvor->koeficijent, trenutniCvor->eksponent);
		}
		trenutniCvor = trenutniCvor->next; //iduci element
	}
	printf("\r\n");
}
int ZbrojiPolinome(Position pp, Position dp, Position sumaPolinoma) {
	Position temp;
	pp = pp->next; //pokazivac na iduci element jer prvi ne sadrzi nista
	dp = dp->next; //pokazivac na iduci element jer prvi ne sadrzi nista
	while (pp!=NULL&&dp!=NULL)
	{
		if (pp->eksponent>dp->eksponent) //ako je eksponent pp veci od eks. dp
		{
			DodajUListuSortirano(sumaPolinoma, pp->koeficijent, pp->eksponent); //salji pp
			pp = pp->next; //iduci element
		}
		else if (pp->eksponent<dp->eksponent) //ako je eksponent pp manji od eks. dp
		{
			DodajUListuSortirano(sumaPolinoma, dp->koeficijent, dp->eksponent); //salji dp
			dp = dp->next; //iduci element
		}
		else
		{	//ako su eksponenti jedanki
			DodajUListuSortirano(sumaPolinoma, pp->koeficijent + dp->koeficijent, dp->eksponent); //zbroji baze elemenata sa istim eksponentom
			pp = pp->next; //iduci element
			dp = dp->next; //iduci element
		}
	}
	if (pp == NULL) //ako je zadnji element pp
		temp = dp;
	else
		temp = pp;

	while (temp!=NULL) //ako je osta koji element do kraja polinoma
	{
		DodajUListuSortirano(sumaPolinoma, temp->koeficijent, temp->eksponent);
		temp = temp->next; //iduci element
	} 
	return 0;
}
int PomnoziPolinome(Position pp, Position dp, Position umnozakPolinoma) {
	Position pocetakDrugogPolinoma = dp->next;
	pp = pp->next;
	dp = dp->next;
	while (pp!=NULL)
	{
		while (dp!=NULL)
		{
			DodajUListuSortirano(umnozakPolinoma, pp->koeficijent*dp->koeficijent, pp->eksponent + dp->eksponent); //mnozi koef. i zbroji eksp.
			dp = dp->next; //iduci element drugog polinoma
		}
		pp = pp->next; //iduci element prvog polinoma
		dp = pocetakDrugogPolinoma; //opet obavlja sve isto samo je pocetak dp sad iduci element
	}
	return 0;
}
void DealocirajMemoriju(Position trenutniCvor) {
	Position temp;
	temp = (Position)malloc(sizeof(Cvor));
	while (trenutniCvor->next!=NULL)
	{
		temp = trenutniCvor->next; //pomicanje pokazivaca na iduci element, cuvamo u temp
		trenutniCvor->next = temp->next;
		free(temp);
	}
}
