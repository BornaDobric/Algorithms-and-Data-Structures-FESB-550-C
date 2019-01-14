#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#define STRING_MAX_LENGHT 50
#define ALLOCATION_ERROR "\r\nDoslo je do greske prilikom alokacije memorije!\r\n"
#define FILE_OPEN_ERROR "\r\nDoslo je do greske prilikom otvaranja datoteke <%s>!\r\n"
#define FILENAME "drzave.txt"

typedef struct _cities* PositionCities;
typedef struct _cities {
	char cityName[STRING_MAX_LENGHT];
	PositionCities next;
}CitiesList;

typedef struct _states* PositionStates;
typedef struct _states {
	char stateName[STRING_MAX_LENGHT];
	PositionCities cityList;
	PositionStates next;
}StatesList;

int ReadFromFile(PositionStates head, char *fileName);
int FindPlaceForSortedInput(PositionStates head, PositionStates temp);
int InsertElement(PositionStates head, PositionStates temp);
int PrintList(PositionStates head);
int DeleteAll(PositionStates head);

int main(int argc, char *argv[]) {
	StatesList statesList;
	CitiesList cityList;

	statesList.next = NULL;
	cityList.next = NULL;

	ReadFromFile(&statesList, FILENAME);
	PrintList(statesList.next);

	DeleteAll(&statesList);
	PrintList(statesList.next);
	printf("\r\n");
	return 0;
}
int ReadFromFile(PositionStates head, char *fileName) {
	FILE *fp;
	PositionStates tempStates;
	fp = fopen(fileName, "r");
	if (fp == NULL)
		printf(FILE_OPEN_ERROR, fileName);
	else
	{
		while (!feof(fp))
		{
			tempStates = (PositionStates)malloc(sizeof(StatesList));
			fscanf(fp, " %s", tempStates->stateName);
			FindPlaceForSortedInput(head, tempStates);
		}
		fclose(fp);
	}

	return 0;
}
int FindPlaceForSortedInput(PositionStates head, PositionStates temp) {
	while (head->next != NULL && strcmpi(head->next->stateName, temp->stateName) > 0)
		head = head->next;
	InsertElement(head, temp);
	return 0;
}
int InsertElement(PositionStates head, PositionStates temp) {
	if (temp == NULL)
		printf(ALLOCATION_ERROR);
	else
	{
		temp->next = head->next;
		head->next = temp;
	}
	return 0;
}
int PrintList(PositionStates head) {
	if (head == NULL)
		printf("\r\nLista je prazna!\r\n");
	else
	{
		while (head!=NULL)
		{
			printf(" %s\r\n", head->stateName);
			head = head->next;
		}
	}
	return 0;
}
int DeleteAll(PositionStates head) {
	PositionStates temp;
	printf("\r\nBrisanje cijele liste...\r\n");
	while (head->next!=NULL)
	{
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
	printf("\r\nLista uspjesno obrisana!\r\n");
	return 0;
}