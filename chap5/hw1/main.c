#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LEN   256

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage : %s filename\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("File open failed");
        return 1;
    }

    char lines[MAX_LINES][MAX_LEN];
    int count = 0;

    while (fgets(lines[count], sizeof(lines[count]), fp) && count < MAX_LINES)
        count++;
    fclose(fp);

    printf("File read success\n");
    printf("Total Line : %d\n", count);
    printf("You can choose 1 ~ %d Line\n", count);
    printf("Pls 'Enter' the line to select : ");

    char input[32];
    scanf("%31s", input);

    if (strcmp(input, "*") == 0) {
        for (int i = 0; i < count; i++)
            printf("%s", lines[i]);
    }
    else if (strchr(input, ',') != NULL) {
        int n1, n2;
        sscanf(input, "%d,%d", &n1, &n2);
        if (n1 >= 1 && n1 <= count)
            printf("%s", lines[n1 - 1]);
        if (n2 >= 1 && n2 <= count)
            printf("%s", lines[n2 - 1]);
    }
    else if (strchr(input, '-') != NULL) {
        int start, end;
        sscanf(input, "%d-%d", &start, &end);
        for (int i = start; i <= end && i <= count; i++)
            printf("%s", lines[i - 1]);
    }
    else {
        int line_no = atoi(input);
        if (line_no >= 1 && line_no <= count)
            printf("%s", lines[line_no - 1]);
    }

    return 0;
}

