#include "debugger.h"
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * start_debugger - Starts a debugger session for a program
 * @program: Path to the program to debug
 *
 * Forks a child process, attaches a tracer to it, and executes the program.
 *
 * Return: The process ID of the debugged program
 */
pid_t start_debugger(char *program)
{
  pid_t pid = fork();

  if (pid == 0)
  {
    ptrace(PT_TRACE_ME, 0, (caddr_t)0, 0);
    execl(program, program, NULL);
    perror("execl");
    exit(1);
  }
  else
  {
    int status;
    waitpid(pid, &status, 0);
    printf("Debugger started, pid=%d\n", pid);
    return pid;
  }
}

/**
 * continue_execution - Continues execution of a traced process
 * @pid: Process ID of the debugged program
 *
 * Resumes execution of the traced process and waits for it to stop.
 * Prints the signal that caused the process to stop if applicable.
 *
 * Return: void
 */
void continue_execution(pid_t pid)
{
  int status;
  ptrace(PT_CONTINUE, pid, (caddr_t)1, 0);
  waitpid(pid, &status, 0);

  if (WIFSTOPPED(status))
  {
    printf("Stopped by signal %d\n", WSTOPSIG(status));
  }
}
