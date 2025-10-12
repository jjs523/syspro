#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fd1, fd2, n;
    char buf[BUFSIZ];

    if (argc != 3) {
        fprintf(stderr, "How to use: %s file1.txt file2.txt\n", argv[0]);
        return 1;
    }

    /* file1: 읽기 전용 */
    if ((fd1 = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        return 2;
    }

    /* file2: 없으면 생성, 있으면 '끝에' 덧붙임 */
    if ((fd2 = open(argv[2], O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1) {
        perror(argv[2]);
        close(fd1);
        return 3;
    }

    /* file1에서 읽어 file2 끝에 계속 쓰기 */
    while ((n = read(fd1, buf, BUFSIZ)) > 0) {
        if (write(fd2, buf, n) != n) {
            perror("write");
            close(fd1);
            close(fd2);
            return 4;
        }
    }
    if (n < 0) {  // read 에러
        perror("read");
        close(fd1);
        close(fd2);
        return 5;
    }

    close(fd1);
    close(fd2);
    return 0;
}

