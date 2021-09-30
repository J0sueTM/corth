#ifndef CORTH_OPERATION_H
#define CORTH_OPERATION_H

#include "core.h"

#define UNKNOWN_OPERATION 0

#define PUSH_OPERATION 3
#define POP_OPERATION  4

#define SUM_OPERATION   1
#define MINUS_OPERATION 2

#define DUMP_OPERATION 5

#define parse_operation(_type, _program) \
  (_program->mode == EMULATION_MODE) \
    ? emulate_operation(_type, _program) \
    : compile_operation(_type, _program)

#endif /* CORTH_OPERATION_H */
