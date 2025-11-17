#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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

    if (argc < 2) {
        fprintf(stderr, "file error\n");
        exit(1);
    }

    if ((fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0640)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    printf("%s %s %s %s %s %s\n",
           "id", "bookname", "author", "year", "numofborrow", "borrow");

    while (scanf("%d %23s %23s %d %d %5s",
                 &record.bnumber,
                 record.bname,
                 record.mn,
                 &record.my,
                 &record.bc,
                 record.borrow) == 6) {

        off_t offset = (record.bnumber - 1) * sizeof(record);
        lseek(fd, offset, SEEK_SET);
        write(fd, &record, sizeof(record));
    }

    close(fd);
    return 0;
}

