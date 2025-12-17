#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <sys/types.h>

pid_t start_debugger(char *program);
void continue_execution(pid_t pid);

#endif
