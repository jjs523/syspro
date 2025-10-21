#include <stdio.h>

int main(int argc, char *argv[]){
	char c;
	FILE *fp1, *fp2;

	char cc = argv[1][0];
	printf("%d", cc);

	fp1 = fopen(argv[2], "r");
	if(fp1 == NULL) {
		fprintf(stderr, "File %s Open Error\n", argv[1]);
		return 2;
	}

	fp2 = fopen(argv[3], "w");

	if(cc == '2'){
		while((c = fgetc(fp1)) != EOF){
			if(c >= 97){
				c = c - 32;
			}
			fputc(c, fp2);
		}
	}
	else if(cc == '1'){
		while((c == fgetc(fp1)) != EOF){
			if(c <= 90){
				c = c + 32;
			}
			fputc(c, fp2);
		}
	}
	else{
		while((c = fgetc(fp1)) != EOF){
			fputc(c, fp2);
		}
	}

	fclose(fp1);
	fclose(fp2);
	return 0;
}
