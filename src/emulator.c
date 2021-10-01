#include "emulator.h"

bool
emulate_operation
(
  unsigned int    _type,
  struct program *_program
)
{
  switch (_type)
  {
  case PUSH_OPERATION:
    if (!push_to_stack(_program))
      return false;

    break;
  case PLUS_OPERATION:
  {
    int a = pop_from_stack(_program);
    int b = pop_from_stack(_program);

    _program->number_to_push = (a + b);
    if (!emulate_operation(PUSH_OPERATION, _program))
      return false;

  } break;
  case MINUS_OPERATION:
    printf("Minus.\n");

    break;
  case DUMP_OPERATION:
  {
    int a = pop_from_stack(_program);
    printf("%d\n", a);

  } break;
  default:
    printf("ERROR: Unknown mode %li\n", _type);

    break;
  }

  return true;
} 
