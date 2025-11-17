#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

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
    char input[24];
    char in2[24], bn2[24];
    int found = 0;

    if (argc < 2) exit(1);
    if ((fd = open(argv[1], O_RDONLY)) == -1) exit(2);

    printf("input name of book ) ");
    scanf("%23s", input);

    for (int i = 0; input[i]; i++) in2[i] = tolower(input[i]);
    in2[strlen(input)] = '\0';

    while (read(fd, &record, sizeof(record)) == sizeof(record)) {
        if (record.bnumber == 0) continue;

        for (int i = 0; record.bname[i]; i++) bn2[i] = tolower(record.bname[i]);
        bn2[strlen(record.bname)] = '\0';

        if (strcmp(in2, bn2) == 0) {
            printf("id bookname author year numofborrow borrow\n");
            printf("%d %s %s %d %d %s\n",
                   record.bnumber, record.bname, record.mn,
                   record.my, record.bc, record.borrow);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("not found book name : '%s'\n", input);

    close(fd);
    return 0;
}

