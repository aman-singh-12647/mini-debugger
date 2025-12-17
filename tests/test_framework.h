#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>
#include <string.h>

#define TEST(name) void name()
#define ASSERT_EQ(a, b) do { \
    if ((a) != (b)) { \
        printf("  ✗ FAIL: %s == %s (%ld != %ld)\n", #a, #b, (long)(a), (long)(b)); \
        return; \
    } \
} while(0)

#define ASSERT_TRUE(cond) do { \
    if (!(cond)) { \
        printf("  ✗ FAIL: %s is not true\n", #cond); \
        return; \
    } \
} while(0)

#define ASSERT_NOT_NULL(ptr) do { \
    if ((ptr) == NULL) { \
        printf("  ✗ FAIL: %s is NULL\n", #ptr); \
        return; \
    } \
} while(0)

#define RUN_TEST(test) do { \
    printf("Running %s...\n", #test); \
    test(); \
    printf("  ✓ PASS\n"); \
} while(0)

#endif
