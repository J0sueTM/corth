#ifndef CORTH_CORE_H
#define CORTH_CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define EMULATION_MODE   0
#define COMPILATION_MODE 1

/* Useful when rotating the stack */
#define STACK_ITERATION_DIRECTION_RIGHT 1
#define STACK_ITERATION_DIRECTION_LEFT  -1

#define MAX_OPERATION_COUNT 16383
#define UNKNOWN_OPERATION 0

#define PUSH_OPERATION 3
#define POP_OPERATION  4

#define PLUS_OPERATION  1
#define MINUS_OPERATION 2

#define DUMP_OPERATION 5

struct program
{
  unsigned int mode;
  char input_file_path[255];
  char output_file_path[255];
  FILE *input_file;
  FILE *output_file;
  char *source;
  long source_file_size;

  unsigned int operation_count;
  unsigned int operations[MAX_OPERATION_COUNT];

  int number_to_push;

  int stack[MAX_OPERATION_COUNT];
  unsigned int stack_count;
  unsigned int stack_index;
  unsigned int stack_direction;
};

#endif /* CORTH_CORE_H */
