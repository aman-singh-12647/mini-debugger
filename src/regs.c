#include "regs.h"
#include <sys/ptrace.h>
#include <sys/user.h>
#include <stdio.h>

void print_registers(pid_t pid) {
    struct user_regs_struct regs;
    ptrace(PTRACE_GETREGS, pid, NULL, &regs);

    printf("RIP = 0x%llx\n", regs.rip);
    printf("RSP = 0x%llx\n", regs.rsp);
    printf("RBP = 0x%llx\n", regs.rbp);
}

