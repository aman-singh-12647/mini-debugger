#include "regs.h"
#include <sys/ptrace.h>
#include <sys/user.h>
#include <stdio.h>

void print_registers(pid_t pid) {
    struct user_regs_struct regs;
    ptrace(PTRACE_GETREGS, pid, NULL, &regs);

    printf("RIP = 0x%llx\n", regs.rip);
    printf("RAX = 0x%llx\n", regs.rax);
    printf("RBX = 0x%llx\n", regs.rbx);
    printf("RCX = 0x%llx\n", regs.rcx);
    printf("RDX = 0x%llx\n", regs.rdx);
    printf("RSI = 0x%llx\n", regs.rsi);
    printf("RDI = 0x%llx\n", regs.rdi);
    printf("RSP = 0x%llx\n", regs.rsp);
    printf("RBP = 0x%llx\n", regs.rbp);
    printf("EFLAGS = 0x%llx\n", regs.eflags);
}

