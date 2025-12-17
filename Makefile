CC=gcc
CFLAGS=-Wall -g
SRC_DIR=src

SRCS=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(SRCS:.c=.o)

all: debugger

TEST_DIR = tests
TEST_SRC = $(TEST_DIR)/run_tests.c $(TEST_DIR)/test_breakpoints.c \
           $(TEST_DIR)/test_status.c $(TEST_DIR)/test_integration.c
TEST_BIN = run_tests

# Add test target
test: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(TEST_SRC) $(filter-out src/main.o, $(OBJS))
	$(CC) $(CFLAGS) -I$(TEST_DIR) -o $@ $^

clean-tests:
	rm -f $(TEST_BIN) test_prog test_prog.c

.PHONY: test clean-tests

debugger: $(OBJS)
	$(CC) $(CFLAGS) -o debugger $(OBJS)

clean:
	rm -f $(OBJS) debugger
	rm -f $(TEST_BIN) test_prog test_prog.c
