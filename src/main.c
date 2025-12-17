#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debugger.h"
#include "breakpoints.h"
#include "step.h"
#include "regs.h"

/**
 * main - Entry point for the mini-debugger application
 * @argc: Argument count
 * @argv: Argument vector containing the program to debug
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Usage: %s <program>\n", argv[0]);
    return 1;
  }

  pid_t pid = start_debugger(argv[1]);
  struct breakpoint bp = {0};

  char command[64];

  while (1)
  {
    printf("\ndbg> ");
    fgets(command, sizeof(command), stdin);

    if (strncmp(command, "break", 5) == 0)
    {
      void *addr = (void *)strtoul(command + 6, NULL, 16);
      bp.addr = addr;
      set_breakpoint(pid, &bp);
    }
    else if (strncmp(command, "cont", 4) == 0)
    {
      continue_execution(pid);
      if (bp.enabled)
      {
        handle_breakpoint(pid, &bp);
      }
    }
    else if (strncmp(command, "step", 4) == 0)
    {
      single_step(pid);
    }
    else if (strncmp(command, "regs", 4) == 0)
    {
      print_registers(pid);
    }
    else if (strncmp(command, "exit", 4) == 0)
    {
      break;
    }
    else
    {
      printf("Unknown command\n");
    }
  }

  return 0;
}
