#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	char c;
	FILE *fp2, *fp3;
	int n;

	fp2	= fopen(argv[2], "r");
	fp3 = fopen(argv[3], "w");
	n = atoi(argv[1]);

	if(n == 0){
		while((c = fgetc(fp2)) != EOF)
			fputc(c, fp3);
	}
	if(n == 1){
		while((c = fgetc(fp2)) != EOF)
			if(c >= 65 && c <= 90){
				c += 32;
				fputc(c, fp3);
			}
			else{
				fputc(c, fp3);
			}
	}
	if(n == 2){
		while((c = fgetc(fp2)) != EOF)
			if(c >= 97){
				c -= 32;
				fputc(c, fp3);
			}
			else{
				fputc(c, fp3);
			}
	}

	fclose(fp2);
	fclose(fp3);
	return 0;
}
	
