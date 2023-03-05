#include "DbgMacros.h"

void DbgMacros_error(char* in_cpFile, uint32_t in_u32Line) {
  printf("[ASSERT FAILURE] File: %s; Line: %d", in_cpFile, in_u32Line);
}
