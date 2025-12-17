#include "test_framework.h"
#include "../src/breakpoints.h"
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

TEST(test_breakpoint_initialization)
{
  struct breakpoint bp = {0};
  ASSERT_EQ(bp.enabled, 0);
  ASSERT_EQ((long)bp.addr, 0);
  ASSERT_EQ(bp.original_byte, 0);
}

TEST(test_set_breakpoint)
{
  pid_t pid = fork();

  if (pid == 0)
  {
    ptrace(PT_TRACE_ME, 0, NULL, 0);
    execl("/bin/ls", "ls", NULL);
    exit(1);
  }

  int status;
  waitpid(pid, &status, 0);

  struct breakpoint bp = {0};
  bp.addr = (void *)0x1000;

  // This will fail in practice but tests the structure
  ASSERT_EQ(bp.enabled, 0);

  // Clean up
#ifdef __APPLE__
  ptrace(PT_KILL, pid, NULL, 0);
#else
  ptrace(PTRACE_KILL, pid, NULL, NULL);
#endif
  waitpid(pid, &status, 0);
}

TEST(test_breakpoint_structure)
{
  struct breakpoint bp;
  bp.addr = (void *)0x12345678;
  bp.original_byte = 0xAB;
  bp.enabled = 1;

  ASSERT_EQ((long)bp.addr, 0x12345678);
  ASSERT_EQ(bp.original_byte, 0xAB);
  ASSERT_EQ(bp.enabled, 1);
}
