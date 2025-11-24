#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXARG 64
#define MAXLINE 1024

int main() {
    char cmdline[MAXLINE];
    char *args[MAXARG];
    int background;
    int pid, child, status;
    char *token;
    char *saveptr;
    int i;
    
    while (1) {
        printf("Pls input cmd : ");
        fflush(stdout);
        
        if (fgets(cmdline, MAXLINE, stdin) == NULL)
            break;
        
        cmdline[strcspn(cmdline, "\n")] = '\0';
        
        if (strlen(cmdline) == 0)
            continue;
        
        if (strcmp(cmdline, "exit") == 0 || strcmp(cmdline, "quit") == 0) {
            printf("Exit\n");
            break;
        }
        
        background = 0;
        i = 0;
        
        token = strtok_r(cmdline, " \t", &saveptr);
        while (token != NULL && i < MAXARG - 1) {
            if (strcmp(token, "&") == 0) {
                background = 1;
                break;
            }
            args[i++] = token;
            token = strtok_r(NULL, " \t", &saveptr);
        }
        args[i] = NULL;
        
        if (args[0] == NULL)
            continue;
        
        pid = fork();
        
        if (pid == 0) {
            printf("[%d] child process start\n", getpid());
            fflush(stdout);
            execvp(args[0], args);
            fprintf(stderr, "%s: 실행 불가\n", args[0]);
            exit(1);
        }
        else if (pid > 0) {
            printf("[%d] Parent process start\n", getpid());
            if (background == 0) {
                child = wait(&status);
                printf("[%d] child process end %d\n", getpid(), child);
                printf("SUCCESS\n");
            }
        }
        else {
            perror("fork 실패");
        }
    }
    
    printf("Parent process end\n");
    return 0;
}
