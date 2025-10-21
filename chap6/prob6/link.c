#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	if(link(argv[1], argv[2]) == -1){
		perror(argv[1]);
		exit(1);
	}
	exit(0);
}

