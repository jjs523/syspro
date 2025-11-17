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
    int cmd, id;
    off_t offset;

    if (argc < 2) {
        fprintf(stderr, "file error\n");
        exit(1);
    }

    if ((fd = open(argv[1], O_RDWR)) == -1) {
        perror(argv[1]);
        exit(2);
    }

    printf("0 bookId: borrow book, 1 bookId: return book ) ");
    if (scanf("%d %d", &cmd, &id) != 2) {
        close(fd);
        return 0;
    }

    offset = (id - 1) * sizeof(record);
    if (lseek(fd, offset, SEEK_SET) == -1) {
        perror("lseek");
        close(fd);
        exit(3);
    }

    if (read(fd, &record, sizeof(record)) != sizeof(record) ||
        record.bnumber != id) {
        printf("No such book.\n");
        close(fd);
        return 0;
    }

    if (cmd == 0) {              /* 대출 */
        if (strcmp(record.borrow, "False") == 0) {
            record.bc++;
            strcpy(record.borrow, "True");

            if (lseek(fd, offset, SEEK_SET) == -1) {
                perror("lseek");
                close(fd);
                exit(4);
            }
            if (write(fd, &record, sizeof(record)) != sizeof(record)) {
                perror("write");
                close(fd);
                exit(5);
            }

            printf("You've got bellow book..\n");
        } else {
            printf("You cannot borrow below book since it has been booked.\n");
            printf("id bookname author year numofborrow borrow\n");
            printf("%d %s %s %d %d %s\n",
                   record.bnumber,
                   record.bname,
                   record.mn,
                   record.my,
                   record.bc,
                   record.borrow);
            close(fd);
            return 0;
        }
    } else if (cmd == 1) {       /* 반납 */
        if (strcmp(record.borrow, "True") == 0) {
            strcpy(record.borrow, "False");

            if (lseek(fd, offset, SEEK_SET) == -1) {
                perror("lseek");
                close(fd);
                exit(6);
            }
            if (write(fd, &record, sizeof(record)) != sizeof(record)) {
                perror("write");
                close(fd);
                exit(7);
            }

            printf("You've returned bellow book..\n");
        } else {
            printf("You cannot return this book.\n");
            printf("id bookname author year numofborrow borrow\n");
            printf("%d %s %s %d %d %s\n",
                   record.bnumber,
                   record.bname,
                   record.mn,
                   record.my,
                   record.bc,
                   record.borrow);
            close(fd);
            return 0;
        }
    } else {
        close(fd);
        return 0;
    }

    printf("id bookname author year numofborrow borrow\n");
    printf("%d %s %s %d %d %s\n",
           record.bnumber,
           record.bname,
           record.mn,
           record.my,
           record.bc,
           record.borrow);

    close(fd);
    return 0;
}

