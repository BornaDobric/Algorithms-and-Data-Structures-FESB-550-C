#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#define STRING_MAX_LENGHT 50

int KillCapitalLettersFromWordInput(char wordInput[]);

int main(int argc, char *argv[]) {
	char wordInput[STRING_MAX_LENGHT];
	printf("\r\nUnesite rijec iz koje izbacujemo velika slova: ");
	scanf(" %s", wordInput);
	KillCapitalLettersFromWordInput(wordInput);
	return 0;
}
int KillCapitalLettersFromWordInput(char wordInput[]) {
	char buffer;
	for (int i = 0; i < strlen(wordInput); i++) {
		buffer = wordInput[i];
		if (!isupper(buffer))
			printf("%c", buffer);
	}
	printf("\r\n");
	return 0;
}