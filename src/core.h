#ifndef CORTH_CORE_H
#define CORTH_CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define EMULATION_MODE   0
#define COMPILATION_MODE 1
#define MAX_OPERATION_COUNT 16383

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
} program;

#endif /* CORTH_CORE_H */
