#include "stack.h"

bool
push_to_stack
(
  struct program *_program
)
{
  if (_program->stack_count + 1 >= MAX_OPERATION_COUNT)
  {
    printf("ERROR: Stack overflow.\n");

    return false;
  }

  _program->stack[_program->stack_index] = _program->number_to_push;
  _program->stack_index += _program->stack_direction;
  ++_program->stack_count;

  return true;
}

int
pop_from_stack
(
  struct program *_program
)
{
  if (_program->stack_count + 1 <= 0)
  {
    printf("ERROR: Stack underflow.\n");

    return 0;
  }

  _program->stack_index -= _program->stack_direction;
  --_program->stack_count;
  int popped_number = _program->stack[_program->stack_index];

  return popped_number;
}
