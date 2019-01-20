#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#include<math.h>
#define STRING_MAX_LENGHT 50
#define INTERVAL_MIN 5
#define INTERVAL_MAX 500

int FindAllNumbers(int min, int max);

int main(int argc, char *argv[]) {
	int min, max;
	min = INTERVAL_MIN;
	max = INTERVAL_MAX;
	FindAllNumbers(min, max);
	return 0;
}
int FindAllNumbers(int min, int max) {
	int toThePowerOf = 4;
	printf("\r\nUnutar intervala brojevi koji su potencija na cetvrtu su: \r\n");
	while (min < max)
	{
		for (int base = 0; base < (max / 2); base++) {
			if (min == (int)pow(base, toThePowerOf)) {
				printf(" %d\r\n", (int)pow(base, toThePowerOf));
			}
		}
		min++;
	}
	printf("\r\n");
	return 0;
}