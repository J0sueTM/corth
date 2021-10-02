#include "compiler.h"

bool
compile_operation
(
  unsigned int    _type,
  struct program *_program
)
{
  switch (_type)
  {
  case PUSH_OPERATION:
    printf("Pushed %d", _program->number_to_push);

    break;
  case PLUS_OPERATION:
    printf("Plus\n");

    break;
  case MINUS_OPERATION:
    printf("Minus.\n");

    break;
  case DUMP_OPERATION:
    printf("Dump.\n");
  
    break;
  default:
    printf("ERROR: Unknown mode %d\n", _type);

    break;
  }

  return true;
}
