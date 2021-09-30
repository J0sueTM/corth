#ifndef CORTH_H
#define CORTH_H

#include "core.h"
#include "operation.h"

void
usage
(
  void
);

bool
parse_arguments
(
  int             _argument_count,
  char          **_argument_values,
  struct program *_program
);

bool
load_source_from_input_file
(
  struct program *_program
);

bool
parse_current_word
(
  struct program *_program,
  char           *_current_word
);

bool
load_operations
(
  struct program *_program
);

#endif /* CORTH_H */
