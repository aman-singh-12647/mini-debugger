#include "test_framework.h"
#include <stdio.h>

// Declare test functions
void test_breakpoint_initialization();
void test_breakpoint_structure();
void test_set_breakpoint();
void test_print_status_stopped();
void test_print_status_exited();
void test_wif_macros();
void test_debugger_start();
void test_continue_execution();

int main()
{
  printf("=== Mini Debugger Test Suite ===\n\n");

  printf("--- Breakpoint Tests ---\n");
  RUN_TEST(test_breakpoint_initialization);
  RUN_TEST(test_breakpoint_structure);
  RUN_TEST(test_set_breakpoint);

  printf("\n--- Status Tests ---\n");
  RUN_TEST(test_print_status_stopped);
  RUN_TEST(test_print_status_exited);
  RUN_TEST(test_wif_macros);

  printf("\n--- Integration Tests ---\n");
  RUN_TEST(test_debugger_start);
  RUN_TEST(test_continue_execution);

  printf("\n=== All Tests Passed ===\n");
  return 0;
}
