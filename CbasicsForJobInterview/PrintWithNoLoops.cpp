#include<stdio.h>
#include<stdlib.h>

int PrintNumbers(int n);
int main(int argc, char *argv[]) {
	int n = 100;
	PrintNumbers(100);
	printf("\r\n");
	return 0;
}
int PrintNumbers(int n) {
	if (n > 0) {
		PrintNumbers(n - 1);
		printf(" %d", n);
	}
	return 0;
}