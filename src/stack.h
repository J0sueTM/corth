#ifndef CORTH_STACK_H
#define CORTH_STACK_H

#include "core.h"

bool
push_to_stack
(
  struct program *_program
);

int
pop_from_stack
(
  struct program *_program
);

#endif /* CORTH_STACK_H */
