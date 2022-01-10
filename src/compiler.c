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
    fprintf(_program->output_file, "  push %d\n", _program->number_to_push);

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

bool
compile_program
(
  struct program *_program
)
{
  char output_file_path_without_termination[255];
  snprintf(output_file_path_without_termination, strlen(_program->output_file_path) - 3, "%s", _program->output_file_path);

  char compilation_subprocess[255];
  sprintf(compilation_subprocess,
          "nasm -f elf64 -o %s.o %s", output_file_path_without_termination, _program->output_file_path);
  printf("INFO: Running %s\n", compilation_subprocess);
  system(compilation_subprocess);

  char linking_subprocess[255];
  sprintf(linking_subprocess,
          "ld -o %s %s.o", output_file_path_without_termination, output_file_path_without_termination);
  printf("INFO: Running %s\n", linking_subprocess);
  system(linking_subprocess);

  return true;
}
