#ifndef CORTH_EMULATOR_H 
#define CORTH_EMULATOR_H 

#include "core.h"
#include "stack.h"

bool
emulate_operation
(
  unsigned int    _type,
  struct program *_program
);

#endif /* CORTH_EMULATOR_H */
