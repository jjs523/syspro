#include <stdio.h>
#include "student.h"

int main(int argc, char* argv[]){
	struct student rec;
	FILE *fp;
	if(argc != 2){
		fprintf(stderr, "How to use : %s FileName\n", argv[0]);
		return 1;
	}

	if((fp = fopen(argv[1], "rb")) == NULL){
		fprintf(stderr, "Error");
		return 2;
	}

	printf("%10s %6s %6s\n", "StudentID", "Name", "Score");

	while(fscanf(fp, "%d %19s %hd", &rec.id, rec.name, &rec.score) == 3){
		if(rec.id != 0)
			printf("%10d %6s %6d\n", rec.id, rec.name, rec.score);
	}
	fclose(fp);
	return 0;
}


