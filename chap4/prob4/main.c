#include <stdio.h>
#include <stdlib.h>
#include "student.h"

int main(int argc, char* argv[]) {
    struct student rec;
	FILE *fp;

    if (argc != 2) {
        fprintf(stderr, "How to use : %s FileName\n", argv[0]);
        return 1;
    }

	fp = fopen(argv[1], "w");
	if(!fp){
		perror(argv[1]);
		return 2;
	}


	printf("%-9s, %-7s %-4s\n", "학번", "이름", "점수");

	char line[256];
	int saved = 0;

	while(fgets(line, sizeof(line), stdin) != NULL) {
		int n = sscanf(line, "%d %19s %hd", &rec.id, rec.name, &rec.score);

		if (n == 3) {
			fprintf(fp, "%d %s %hd\n", rec.id, rec.name, rec.score);
			saved++;
		}
		else{
			fprintf(stderr, "입력형식 오류 다시 ㅇ비력하세요\n");
		}
	}


    fclose(fp);
    return 0;
}
