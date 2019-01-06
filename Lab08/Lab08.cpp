#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#define STRING_MAX_LENGHT 50

typedef struct _cvor* Position;
typedef struct _cvor {
	int element;
	Position next;
}Cvor;

int ReadFromFile(Position head);
int ReadString(Position head, char *buffer);
int PushStack(Position head, int broj);
Position CreateNewElement(int broj);
int PopStack(Position head);
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
	printf("\r\nUnesite naziv datoteke za citanje: ");
	scanf(" %s", fileName);
	fp = fopen(fileName, "r");
	if (fp == NULL)
		printf("\r\nDoslo je do greske prilikom alokacije memorije!\r\n");
	else
	{
		while (!feof(fp))
		{
			fgets(buffer, STRING_MAX_LENGHT, fp);
			ReadString(head, buffer);
		}
	}
	fclose(fp);
	return 0;
}
int ReadString(Position head, char *buffer) {
	int offset, znamenka;
	int operand1, operand2;
	char znak;
	int rezultat;
	while (sscanf(buffer, " %c %n",&znak,&offset)!=EOF)
	{
		if (isdigit(znak))
		{
			znamenka = atoi(&znak);
			PushStack(head, znamenka);
		}
		else
		{
			operand1 = PopStack(head);
			operand2 = PopStack(head);
			switch (znak)
			{
			case '+':
				PushStack(head, operand1 + operand2);
				break;
			case '-':
				PushStack(head, operand1 - operand2);
				break;
			case '*':
				PushStack(head, operand1 * operand2);
				break;
			case '/':
				PushStack(head, operand1 / operand2);
				break;
			default:
				printf("\r\nGreska!\r\n");
				break;
			}
		}
		buffer += offset;
	}
	printf("\r\nRezultat je: %d\r\n\r\n", PopStack(head));
	return 0;
}
int PushStack(Position head, int broj) {
	Position temp;
	temp = CreateNewElement(broj);
	if (temp == NULL)
		printf("\r\nDoslo je do greske prilikom alokacije memorije!\r\n");
	else
	{
		temp->next = head->next;
		head->next = temp;
	}
	printf("\r\nPushed number: %d\r\n", broj);
	return 0;
}
Position CreateNewElement(int broj) {
	Position temp;
	temp = (Position)malloc(sizeof(Cvor));
	if (temp == NULL)
		return NULL;
	else
	{
		temp->element = broj;
		temp->next = NULL;
	}
	return temp;
}
int PopStack(Position head) {
	Position temp;
	temp = head->next;
	if (temp==NULL)
		printf("\r\nLista je prazna!\r\n");
	else
	{
		head->next = temp->next;
		printf("\r\nPopped element: %d", temp->element);
		free(temp);
	}
	return 0;
}
int PrintStack(Position head) {
	while (head!=NULL)
	{
		printf(" %d", head->element);
		head = head->next;
	}
	return 0;
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
