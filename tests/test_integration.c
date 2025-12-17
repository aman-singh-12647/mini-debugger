#include "test_framework.h"
#include "../src/debugger.h"
#include "../src/breakpoints.h"
#include "../src/step.h"
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

// Create a simple test program to debug
static void create_test_program()
{
  FILE *f = fopen("test_prog.c", "w");
  fprintf(f, "#include <stdio.h>\n");
  fprintf(f, "int main() {\n");
  fprintf(f, "    int x = 5;\n");
  fprintf(f, "    x = x + 10;\n");
  fprintf(f, "    printf(\"Result: %%d\\n\", x);\n");
  fprintf(f, "    return 0;\n");
  fprintf(f, "}\n");
  fclose(f);
  system("gcc -g test_prog.c -o test_prog");
}

TEST(test_debugger_start)
{
  create_test_program();
  pid_t pid = start_debugger("./test_prog");
  ASSERT_TRUE(pid > 0);

  // Clean up
#ifdef __APPLE__
  ptrace(PT_KILL, pid, NULL, 0);
#else
  ptrace(PTRACE_KILL, pid, NULL, NULL);
#endif
  int status;
  waitpid(pid, &status, 0);
  unlink("test_prog.c");
  unlink("test_prog");
}

TEST(test_continue_execution)
{
  create_test_program();
  pid_t pid = start_debugger("./test_prog");
  ASSERT_TRUE(pid > 0);

  continue_execution(pid);

  // Clean up
  int status;
  waitpid(pid, &status, 0);
  unlink("test_prog.c");
  unlink("test_prog");
}
