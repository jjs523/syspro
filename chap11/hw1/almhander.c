#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

typedef void (*sighandler_t)(int);

sighandler_t my_signal(int signum, sighandler_t handler) {
    struct sigaction act, old_act;

    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART;

    if (sigaction(signum, &act, &old_act) < 0) {
        return SIG_ERR;
    }

    return old_act.sa_handler;
}

void alarm_handler(int signo) {
    printf("Wake up\n");
    exit(0);
}

int main() {
    int i = 0;

    if (my_signal(SIGALRM, alarm_handler) == SIG_ERR) {
        perror("signal error");
        return 1;
    }

    alarm(5);

    while (1) {
        sleep(1);
        i++;
        printf("%d second\n", i);
    }

    return 0;
}
