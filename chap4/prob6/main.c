#include <stdio.h>
#include "student.h"
#include <stdlib.h>

int main(int argc, char* argv[]){
	struct student rec;
	FILE *fp;

	if (argc != 2){
		fprintf(stderr, "How to use: %s FileName\n", argv[0]);
		return 1;
	}

	fp = fopen(argv[1], "a");
	if (!fp){
		perror("fopen");
		return 1;
	}

	char line[128];
	while(1){
		if(!fgets(line, sizeof(line), stdin)){
			break;
		}
		if(line[0] == '\n') {
			break;
		}

		int n = sscanf(line, "%d %19s %hd", &rec.id, rec.name, &rec.score);
		if (n == 3)
			fprintf(fp, "%d %s %hd\n", rec.id, rec.name, rec.score);
		else
			fprintf(stderr, "형식 에러\n");
	}


	fclose(fp);

	return 0;
}
