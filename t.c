#include <stdio.h>

int main(void){
	int a = 0;
	char c;
	char c1;
	char c2;
	char c3;
	c = 'a';
	c1 = 'z';
	c2 = 'A';
	c3 = 'Z';

	printf("%d, %d, %d %d %d, %c\n", c, c1, c2, c3, c-c2, c2 + 32);

	return 0;
}

