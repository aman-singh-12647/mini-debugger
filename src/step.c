#include "step.h"
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <stdio.h>
#include "status.h"

void single_step(pid_t pid) {
    int status;
    ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
    waitpid(pid, &status, 0);

    // if (WIFSTOPPED(status)) {
    //     printf("Single-step complete\n");
    // }
    print_status(status);

}
