#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAXARG 64
#define MAXCMD 1024

void execute_command(char **args, int background, char *infile, char *outfile) {
    int pid, child, status;
    int fd;
    
    pid = fork();
    
    if (pid == 0) {
        if (infile != NULL) {
            fd = open(infile, O_RDONLY);
            if (fd < 0) {
                perror("입력 파일 열기 실패");
                exit(1);
            }
            dup2(fd, 0);
            close(fd);
        }
        
        if (outfile != NULL) {
            fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0600);
            if (fd < 0) {
                perror("출력 파일 열기 실패");
                exit(1);
            }
            dup2(fd, 1);
            close(fd);
        }
        
        execvp(args[0], args);
        fprintf(stderr, "%s: 실행 불가\n", args[0]);
        exit(1);
    }
    else {
        if (background == 0) {
            child = wait(&status);
        }
        else {
            printf("[%d] 백그라운드로 실행\n", pid);
        }
    }
}

void parse_command(char *cmd, char **args, int *background, char **infile, char **outfile) {
    int i = 0;
    char *token;
    
    *background = 0;
    *infile = NULL;
    *outfile = NULL;
    
    token = strtok(cmd, " \t\n");
    while (token != NULL && i < MAXARG - 1) {
        if (strcmp(token, "&") == 0) {
            *background = 1;
            break;
        }
        else if (strcmp(token, ">") == 0) {
            token = strtok(NULL, " \t\n");
            if (token != NULL)
                *outfile = token;
        }
        else if (strcmp(token, "<") == 0) {
            token = strtok(NULL, " \t\n");
            if (token != NULL)
                *infile = token;
        }
        else {
            args[i++] = token;
        }
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
}

void process_commands(char *cmdline) {
    char *commands[MAXARG];
    int cmd_count = 0;
    char *token;
    char *saveptr;
    int i;
    
    token = strtok_r(cmdline, ";", &saveptr);
    while (token != NULL && cmd_count < MAXARG) {
        commands[cmd_count++] = token;
        token = strtok_r(NULL, ";", &saveptr);
    }
    
    for (i = 0; i < cmd_count; i++) {
        char *args[MAXARG];
        int background;
        char *infile, *outfile;
        char cmd_copy[MAXCMD];
        
        strncpy(cmd_copy, commands[i], MAXCMD - 1);
        cmd_copy[MAXCMD - 1] = '\0';
        
        parse_command(cmd_copy, args, &background, &infile, &outfile);
        
        if (args[0] != NULL) {
            execute_command(args, background, infile, outfile);
        }
    }
}

int main() {
    char cmdline[MAXCMD];
    
    while (1) {
        printf("[shell] ");
        fflush(stdout);
        
        if (fgets(cmdline, MAXCMD, stdin) == NULL)
            break;
        
        cmdline[strcspn(cmdline, "\n")] = '\0';
        
        if (strlen(cmdline) == 0)
            continue;
        
        if (strcmp(cmdline, "exit") == 0 || strcmp(cmdline, "quit") == 0)
            break;
        
        process_commands(cmdline);
        
        while (waitpid(-1, NULL, WNOHANG) > 0);
    }
    
    return 0;
}
