#ifndef CORTH_OPERATION_H
#define CORTH_OPERATION_H

#include "core.h"
#include "emulator.h"
#include "compiler.h"

#define parse_operation(_type, _program) \
  (_program->mode == EMULATION_MODE) \
    ? emulate_operation(_type, _program) \
    : compile_operation(_type, _program)

#endif /* CORTH_OPERATION_H */
