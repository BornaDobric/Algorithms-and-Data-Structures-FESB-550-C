#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#define STRING_MAX_LENGHT 50

typedef struct _cvor* Position;
typedef struct _cvor {
	int element;
	Position next;
}Cvor;

int ReadFromFile(Position head);
int ReadString(Position head, char *buffer);
int PushStack(Position head, int broj);
int PopStack(Position head);
Position CreateNewElement(int broj);
int PrintStack(Position head);
int DeleteAll(Position head);

int main(int argc, char *argv[]) {
	Cvor stack;
	stack.next = NULL;
	ReadFromFile(&stack);
	DeleteAll(&stack);
	return 0;
}
int ReadFromFile(Position head) {
	FILE *fp;
	char fileName[STRING_MAX_LENGHT];
	char buffer[STRING_MAX_LENGHT];
	printf("Unesite naziv datoteke za citanje: ");
	scanf(" %s", fileName);
	fp = fopen(fileName, "r");
	if (fp == NULL)
		printf("\r\nDoslo je do greske prilikom otvaranja datoteke <%s>!\r\n",fileName);
	else
	{
		while (!feof(fp)) //dok nije kraj datoteke
		{
			fgets(buffer, STRING_MAX_LENGHT, fp); //citaj mi red iz datoteke u buffer
			ReadString(head, buffer); //proslijedi u funkciju buffer i stog
		}
	}
	fclose(fp); //zatvori datoteku
	return 0;
}
int ReadString(Position head, char *buffer) {
	int offset; //offset(%n) postavlja brojac ovisno o prethodno ispisanom broju znakova
	char znak;
	int znamenka;
	int operand1, operand2;
	while (sscanf(buffer,"%c %n",&znak,&offset)!=EOF) //EOF-end of file
	{
		if (isdigit(znak)) { //ako je znamenka
			znamenka = atoi(&znak); //pretvori znak u znamenku
			PushStack(head, znamenka); //upisi na stog znamenku
		}
		else
		{	//ako je procitan operator prvo skini dva operanda sa stoga
			operand1 = PopStack(head); //pop prvi element
			operand2 = PopStack(head); //pop drugi element
			switch (znak)
			{
			case '+':
				PushStack(head, operand2 + operand1);
				break;
			case '-':
				PushStack(head, operand2 - operand1);
				break;
			case '*':
				PushStack(head, operand2 * operand1);
				break;
			case '/':
				PushStack(head, operand2 / operand1);
				break;
			default:
				printf("\r\nGreska!\r\n");
				break;
			}
		}
		buffer += offset; //uvecaj za offset do iduceg znaka
	}
	printf("\r\nRezultat je: %d\r\n\r\n", PopStack(head)); //zadnji element koji je upisan na stog je rezultat i njega poppamo
	return 0;
}
int PushStack(Position head, int broj) {
	Position temp;
	temp = CreateNewElement(broj);
	if (temp == NULL)
		printf("\r\nDoslo je do greske prilikom alokacije memorije!\r\n");
	else
	{
		temp->next = head->next; //prebacivanje pokazivaca za upis elementa u listu
		head->next = temp;
	}
	printf("\r\nPushed number: %d\r\n", temp->element); //upisali smo broj
	return 0;
}
Position CreateNewElement(int broj) {
	Position temp;
	temp = (Position)malloc(sizeof(Cvor));
	if (temp == NULL)
		return NULL; //provjera greske u funkciji iz koje smo pozvali
	else
	{
		temp->element = broj; //upis broja u element
		temp->next = NULL; 
	}
	return temp;
}
int PopStack(Position head) {
	Position temp;
	temp = head->next;
	if (temp == NULL)
		printf("\r\nLista je prazna!\r\n");
	else
	{
		head->next = temp->next; //klasika za pop
		printf("\r\nPopped number: %d\r\n", temp->element); //poppali smo 
		free(temp); //oslobodi memoriju za poppani element
	}
	return 0;
}
int PrintStack(Position head) {
	while (head!=NULL) //dok nije kraj liste
	{
		printf("\r\n%d", head->element);
		head = head->next; //iduci element
	}
	return 0; //PrintStack ne triba uopce u ovon zadatku al neka stoji sad
}
int DeleteAll(Position head) {
	Position temp;
	temp = head->next;
	while (head->next!=NULL) //dok nije kraj liste
	{
		head->next = temp->next; //promjena pokazivaca
		free(temp); //oslobodi temp
	}
	return 0;
}