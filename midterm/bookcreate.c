#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

struct books{
	int bnumber;
	char bname[24];
	char mn[24];
	int my;
	int bc;
	char b[24];
};

int main(int argc, char *argv[]){
	
	int fd;
	struct books record;

	if(argc < 2){
		fprintf(stderr, "file error\n");
		exit(1);
	}

	if((fd = open(argv[1], O_WRONLY|O_CREAT|O_EXCL, 0640)) == -1){
		perror(argv[1]);
		exit(2);
	}

	printf("%s %s %s %s %s %s\n","id", "bookname", "author", "year", "numofborrow", "borrow");
	while(scanf("%d %s %s %d %d %s", &record.bnumber, record.bname, record.mn, &record.my, &record.bc, record.b) == 6){	
		lseek(fd, (record.bnumber - 0) * sizeof(record), SEEK_SET);
		write(fd, (char *)&record, sizeof(record));
	}

	close(fd);
	exit(0);
}

