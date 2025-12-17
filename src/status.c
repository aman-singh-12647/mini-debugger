#include "status.h"
#include <sys/wait.h>
#include <stdio.h>

void print_status(int status) {
    if (WIFSTOPPED(status)) {
        printf("Process stopped by signal %d\n", WSTOPSIG(status));
    } else if (WIFEXITED(status)) {
        printf("Process exited with code %d\n", WEXITSTATUS(status));
    }
}
