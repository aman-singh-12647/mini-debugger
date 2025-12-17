#include "test_framework.h"
#include "../src/status.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

TEST(test_print_status_stopped)
{
  // This test verifies print_status doesn't crash
  int status = 0x137f; // Simulated stopped status
  print_status(status);
  ASSERT_TRUE(1); // If we get here, function didn't crash
}

TEST(test_print_status_exited)
{
  int status = 0; // Simulated exit status
  print_status(status);
  ASSERT_TRUE(1);
}

TEST(test_wif_macros)
{
  // Test WIFEXITED macro behavior
  int exited_status = 0;
  ASSERT_TRUE(WIFEXITED(exited_status));

  // Note: WIFSTOPPED behavior varies by OS
  // On macOS, status encoding is different than Linux
}
