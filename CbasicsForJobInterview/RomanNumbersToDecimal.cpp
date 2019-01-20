#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#define STRING_MAX_LENGHT 50
int ValueOfRomanNumber(char c);
int RomanToDecimal(char input[]);

int main(int argc, char *argv[]) {
	char input[STRING_MAX_LENGHT];
	printf("\r\nUnesite rimski broj za pretvorbu u dekadski: ");
	scanf(" %s", input);
	printf("\r\nRoman to decimal: %d\r\n", RomanToDecimal(input));
	return 0;
}
int ValueOfRomanNumber(char c) {
	if (c == 'I')
		return 1;
	if (c == 'V')
		return 5;
	if (c == 'X')
		return 10;
	if (c == 'L')
		return 50;
	if (c == 'C')
		return 100;
	if (c == 'D')
		return 500;
	if (c == 'M')
		return 1000;
	return 0;
}
int RomanToDecimal(char input[]) {
	int result = 0;
	int s1 = 0;
	int s2 = 0;
	for (int i = 0; i < strlen(input); i++) {
		s1 = ValueOfRomanNumber(input[i]);
		if (i+1<strlen(input))
		{
			s2 = ValueOfRomanNumber(input[i + 1]);
			if (s1 >= s2)
				result = result + s1;
			else
			{
				result = result + s2 - s1;
				i++;
			}
		}
		else
		{
			result = result + s1;
			i++;
		}
	}
	return result;
}