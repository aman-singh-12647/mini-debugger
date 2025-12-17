#include "breakpoints.h"
#include <sys/ptrace.h>
#include <sys/user.h>
#include <stdio.h>

/**
 * set_breakpoint - Set a breakpoint at the specified address
 * @pid: Process ID of the target process
 * @bp: Pointer to the breakpoint structure
 *
 * Sets a breakpoint by replacing the first byte at the target address
 * with the INT3 instruction (0xCC). Saves the original byte for later
 * restoration and marks the breakpoint as enabled.
 */
void set_breakpoint(pid_t pid, struct breakpoint *bp)
{
  long data = ptrace(PTRACE_PEEKTEXT, pid, bp->addr, NULL);
  bp->original_byte = (uint8_t)(data & 0xFF);

  long patched = (data & ~0xFF) | 0xCC;
  ptrace(PTRACE_POKETEXT, pid, bp->addr, patched);

  bp->enabled = 1;
  printf("Breakpoint set at %p\n", bp->addr);
}

/**
 * remove_breakpoint - Remove a breakpoint from the specified address
 * @pid: Process ID of the target process
 * @bp: Pointer to the breakpoint structure
 *
 * Removes a breakpoint by restoring the original byte at the target address.
 * Marks the breakpoint as disabled.
 */
void remove_breakpoint(pid_t pid, struct breakpoint *bp)
{
  long data = ptrace(PTRACE_PEEKTEXT, pid, bp->addr, NULL);
  long restored = (data & ~0xFF) | bp->original_byte;
  ptrace(PTRACE_POKETEXT, pid, bp->addr, restored);
  bp->enabled = 0;
}

/**
 * handle_breakpoint - Handle a breakpoint hit
 * @pid: Process ID of the target process
 * @bp: Pointer to the breakpoint structure
 *
 * Handles a breakpoint hit by checking if the current instruction pointer
 * matches the breakpoint address. If matched, removes the breakpoint,
 * decrements the instruction pointer, and updates the registers.
 */
void handle_breakpoint(pid_t pid, struct breakpoint *bp)
{
  struct user_regs_struct regs;
  ptrace(PTRACE_GETREGS, pid, NULL, &regs);

  if (regs.rip - 1 == (unsigned long)bp->addr)
  {
    remove_breakpoint(pid, bp);
    regs.rip -= 1;
    ptrace(PTRACE_SETREGS, pid, NULL, &regs);
    printf("Hit breakpoint at %p\n", bp->addr);
  }
}
