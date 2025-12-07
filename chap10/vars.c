#include <stdio.h>
#include <stdlib.h>

int a = 1;
static int b = 2;

void fun(int n){
	int m = 6;
}

int main(){
	int c = 3;
	static int d = 4;
	char *p;

	p = (char *)malloc(40);
	fun(5);
}

