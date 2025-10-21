#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LEN 256

int main(int argc, char *argv[]){
	if (argc != 2){
		fprintf(stderr, "error!");
		return 1i;
	}

	FILE *fp = fopen(argv[1], "r");
	if (!fp) { perror(argv[1]); return 1;}

	char lines[MAX_LINES][MAX_LEN];
	int count = 0;

	while(fgets(lines[count], sizeof(lines[count]), fp) && count < MAX_LINES)
		count++;

	fclose(fp);
	
	for(int i = count - 1; i >= 0; i--){
		printf("%s", lines[i]);
	}

	return 0;
}
