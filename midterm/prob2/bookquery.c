#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

struct books {
    int bnumber;
    char bname[24];
    char mn[24];
    int my;
    int bc;
    char borrow[6];
};

int main(int argc, char *argv[])
{
    int fd;
    struct books record;
    int mode;

    if (argc < 2) {
        fprintf(stderr, "file error\n");
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    printf("0: list of all books, 1: list of available books) ");
    scanf("%d", &mode);

    printf("id bookname author year numofborrow borrow\n");

    while (read(fd, &record, sizeof(record)) == sizeof(record)) {
        if (record.bnumber == 0)
            continue;
        if (mode == 1 && strcmp(record.borrow, "True") != 0)
            continue;

        printf("%d %s %s %d %d %s\n",
               record.bnumber,
               record.bname,
               record.mn,
               record.my,
               record.bc,
               record.borrow);
    }

    close(fd);
    return 0;
}

