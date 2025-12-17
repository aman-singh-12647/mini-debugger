#ifndef BREAKPOINTS_H
#define BREAKPOINTS_H

#include <stdint.h>
#include <sys/types.h>

struct breakpoint
{
  void *addr;
  uint8_t original_byte;
  int enabled;
};

void set_breakpoint(pid_t pid, struct breakpoint *bp);
void remove_breakpoint(pid_t pid, struct breakpoint *bp);
void handle_breakpoint(pid_t pid, struct breakpoint *bp);

#endif
