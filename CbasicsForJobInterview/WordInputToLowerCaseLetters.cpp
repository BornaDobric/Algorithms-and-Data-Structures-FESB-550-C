#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#define STRING_MAX_LENGHT 50

int WordInputToLowerCaseLetters(char wordInput[]);

int main(int argc, char *argv[]) {
	char wordInput[STRING_MAX_LENGHT];
	printf("\r\nUnesite rijec iz koje cemo izbaciti velika slova: ");
	scanf(" %s", wordInput);
	WordInputToLowerCaseLetters(wordInput);
	return 0;
}
int WordInputToLowerCaseLetters(char wordInput[]) {
	char buffer;
	for (int i = 0; i < strlen(wordInput); i++) {
		buffer = wordInput[i];
		if (isupper(wordInput[i]))
		{
			wordInput[i] = tolower(buffer);
		}
	}
	printf(" %s\r\n", wordInput);
	return 0;
}