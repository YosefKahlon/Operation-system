#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int handle = 1;

void sig_handler(int signum) {
    int i = 5;
    int j = 0;
    int k;
    switch (signum) {
        case SIGCHLD:
            printf("My child is dead ! \n ");
            fflush(stdout);
            raise(SIGUSR1);
            break;
        case SIGUSR1:
            printf(" i am sad \n");
            fflush(stdout);
            k = i / j;
            break;
        case SIGFPE:

            if (handle > 0) {
                printf("so I divided in zero \n");
                fflush(stdout);

                while (handle > 0) {

                    printf("please determent me with Ctrl + Z \n");
                    sleep(2);

                }
            }
            break;

        case SIGTSTP:
            printf("its not working !\n");
            handle = 0;
            printf("try maybe with Ctrl + c!\n ");

            break;
        case SIGINT:
            printf("My life its pointless \n");
            char *pointless = "Good Bye World";
            pointless[100] = 'z';
            break;
        case SIGSEGV:
            printf("and now i got Segmentation Fault...\n");
            kill(getpid(),SIGTERM);
            break;
    }
}


int main() {
    int status;
    signal(SIGCHLD, sig_handler);
    signal(SIGUSR1, sig_handler);
    signal(SIGFPE, sig_handler);
    signal(SIGTSTP, sig_handler);
    signal(SIGINT, sig_handler);
    signal(SIGSEGV, sig_handler);

    if (fork() == 0) {

        exit(1);
    }

    // wait until all your children die
    wait(&status);

}