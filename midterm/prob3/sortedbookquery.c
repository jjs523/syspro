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
    int fd, mode;
    struct books list[100], temp;
    int count = 0;

    if (argc < 2) exit(1);
    if ((fd = open(argv[1], O_RDONLY)) == -1) exit(2);

    printf("0: list of all books, 1: list of available books ) ");
    scanf("%d", &mode);

    while (read(fd, &list[count], sizeof(struct books)) == sizeof(struct books)) {
        if (list[count].bnumber != 0) count++;
    }
    close(fd);

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (list[i].bc < list[j].bc) {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }

    printf("id bookname author year numofborrow borrow\n");

    for (int i = 0; i < count; i++) {
        if (mode == 1 && strcmp(list[i].borrow, "True") != 0)
            continue;

        printf("%d %s %s %d %d %s\n",
               list[i].bnumber,
               list[i].bname,
               list[i].mn,
               list[i].my,
               list[i].bc,
               list[i].borrow);
    }

    return 0;
}

