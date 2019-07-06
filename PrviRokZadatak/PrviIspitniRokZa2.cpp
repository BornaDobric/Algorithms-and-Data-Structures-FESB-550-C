#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#define ALLOCATION_ERROR "\r\nDoslo je do greske prilikom alokacije memorije!"
#define EMPTY_LIST "\r\nLista je prazna!"
#define FILE_OPEN_ERROR "\r\nDoslo je do greske prilikom otvaranja datoteke."
#define STRING_MAX_LENGTH 50
#define FILENAME "drzave.txt"
#define RAND_MIN 1
#define RAND_MAX 5

typedef struct _city* PositionCity;
typedef struct _city {
	char cityName[STRING_MAX_LENGTH];
	PositionCity nextCity;
}City;

typedef struct _state* PositionState;
typedef struct _state {
	char stateName[STRING_MAX_LENGTH];
	PositionState nextState;
}State;

int ReadFromFile(PositionState head);
int PushStateInList(PositionState head, PositionState temp);
int FindSpotForSortedInput(PositionState head, PositionState temp);
PositionState CreateNewElement();
int PrintList(PositionState head);
int DeleteAll(PositionState head);

int main(int argc, char *argv[]) {
	State head;
	char c = 0;
	head.nextState = NULL;
	ReadFromFile(&head);
	PrintList(head.nextState);
	scanf(" %c", &c);
	return 0;
}

int ReadFromFile(PositionState head) {
	FILE *fp;
	PositionState temp;
	char buffer[STRING_MAX_LENGTH];
	fp = fopen(FILENAME, "r");
	if (fp == NULL)
		printf(FILE_OPEN_ERROR);
	else
	{
		while (!feof(fp))
		{
			temp = CreateNewElement();
			if (temp == NULL)
				printf(ALLOCATION_ERROR);
			else
			{
				if (fgets(buffer,STRING_MAX_LENGTH,fp)!=NULL)
				{
					sscanf(buffer, " %s", temp->stateName);
					FindSpotForSortedInput(head, temp);
				}
			}
		}
		fclose(fp);
	}
	return 0;
}

PositionState CreateNewElement() {
	PositionState temp;
	temp = (PositionState)malloc(sizeof(State));
	if (temp == NULL)
		return NULL;
	else
		temp->nextState = NULL;
	return temp;
}

int FindSpotForSortedInput(PositionState head, PositionState temp) {
	while (head->nextState != NULL && _strcmpi(head->nextState->stateName, temp->stateName) < 0)
		head = head->nextState;
	PushStateInList(head, temp);
	return 0;
}

int PushStateInList(PositionState head, PositionState temp) {
	temp->nextState = head->nextState;
	head->nextState = temp;
	return 0;
}

int PrintList(PositionState head) {
	if (head == NULL)
		printf(EMPTY_LIST);
	else
	{
		while (head!=NULL)
		{
			printf(" %s\r\n", head->stateName);
			head = head->nextState;
		}
	}
	return 0;
}

int DeleteAll(PositionState head) {
	PositionState temp;
	printf("\r\nBrisanje liste...");
	while (head->nextState!=NULL)
	{
		temp = head->nextState;
		head->nextState = temp->nextState;
		free(temp);
	}
	printf("\r\nLista uspjesno izbrisana!\r\n");
	return 0;
}
