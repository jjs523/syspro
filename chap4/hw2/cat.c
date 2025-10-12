#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_stream(FILE *fp, int show_numbers) {
    int ch;
    int line = 1;
    int bol = 1;

    while ((ch = getc(fp)) != EOF) {
        if (show_numbers && bol) {
            fprintf(stdout, "%6d\t", line);
            bol = 0;
        }
        putc(ch, stdout);
        if (ch == '\n') {
            bol = 1;
            line++;
        }
    }
}

static void usage(const char *prog) {
    fprintf(stderr, "Usage: %s [-n] [file1 file2 ...]\n", prog);
    fprintf(stderr, "  -n : 줄 번호를 함께 출력\n");
    fprintf(stderr, "  파일 인수가 없으면 표준입력(stdin)에서 읽기\n");
}

int main(int argc, char *argv[]) {
    int show_numbers = 0;
    int i = 1;

    while (i < argc && argv[i][0] == '-') {
        if (strcmp(argv[i], "-n") == 0) {
            show_numbers = 1;
            i++;
        } else if (strcmp(argv[i], "--") == 0) {
            i++;
            break;
        } else if (strcmp(argv[i], "-") == 0) {
            break;
        } else {
            usage(argv[0]);
            return 1;
        }
    }

    if (i >= argc) {
        print_stream(stdin, show_numbers);
        return 0;
    }

    for (; i < argc; i++) {
        const char *path = argv[i];
        FILE *fp;

        if (strcmp(path, "-") == 0) {
            fp = stdin;
        } else {
            fp = fopen(path, "r");
            if (!fp) {
                perror(path);
                continue;
            }
        }

        print_stream(fp, show_numbers);

        if (fp != stdin) fclose(fp);
    }

    return 0;
}

