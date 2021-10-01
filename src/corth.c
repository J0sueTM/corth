#include "corth.h"

void
usage
(
  void
)
{
  printf("USAGE:\n");
  printf("  EMULATION:   corth emul input_file\n");
  printf("  COMPILATION: corth comp input_file output_file\n");
}

bool
parse_arguments
(
  int             _argument_count,
  char          **_argument_values,
  struct program *_program
)
{
  if (_argument_count == 2 &&
      (!strcmp(_argument_values[1], "-h") ||
       !strcmp(_argument_values[1], "-?")))
  {
    usage();

    return false;
  }

  if (_argument_count < 3)
  {
    printf("ERROR: Too few arguments. Expected at least 2, got %d.\n", _argument_count - 1);
    usage();

    return false;
  }
  else if (_argument_count > 4)
  {
    printf("ERROR: Too much arguments. Expected at maximum 3, got %d\n", _argument_count - 1);

    return false;
  }
  else if (strcmp(_argument_values[1], "emul") &&
           strcmp(_argument_values[1], "comp"))
  {
    printf("ERROR: Unknown mode %s.\n", _argument_values[1]);
    usage();

    return false;
  }

  if (!strcmp(_argument_values[1], "emul"))
    _program->mode = EMULATION_MODE;
  else
    _program->mode = COMPILATION_MODE;

  /* Predefined values */
  strcpy(_program->input_file_path, "input.corth");
  strcpy(_program->output_file_path, "output");
  
  if (_program->mode == EMULATION_MODE &&
      _argument_count == 4)
    printf("WARNING: Provided output file on emulation mode. Ignoring.\n");
  else if (_program->mode == COMPILATION_MODE &&
           _argument_count < 4)
    printf("WARNING: Output file wasn't provided. Using default: output\n");
  else if (_argument_count == 4)
    strcpy(_program->output_file_path, _argument_values[3]);
  strcpy(_program->input_file_path, _argument_values[2]);

  return true;
}

bool
load_source_from_input_file
(
  struct program *_program
)
{
  _program->input_file = fopen(_program->input_file_path, "r");
  if (!_program->input_file)
  {
    printf("ERROR: Could not open input file to read.\n");

    return false;
  }

  fseek(_program->input_file, 0, SEEK_END);
  _program->source_file_size = ftell(_program->input_file);
  fseek(_program->input_file, 0, SEEK_SET);

  _program->source = malloc(_program->source_file_size + 1);
  if (!_program->source)
  {
    printf("ERROR: Could not allocate memory for input file source.\n");
    fclose(_program->input_file);

    return false;
  }

  fread((void *)_program->source, 1, _program->source_file_size, _program->input_file);
  fclose(_program->input_file);

  /* Replaces the last digit by a null termination */
  _program->source[_program->source_file_size] = '\0';
  
  return true;
}

bool
parse_current_word
(
  struct program *_program,
  char           *_current_word
)
{
  /* Push */
  if (_current_word[0] >= '0' &&
      _current_word[0] <= '9')
  {
    int number_to_push = (int)strtol((const char *)_current_word, NULL, 10);
    _program->number_to_push = number_to_push;

    parse_operation(PUSH_OPERATION, _program);
  }
  else if (strlen(_current_word) == 1 &&
           _current_word[0] == '+')
    parse_operation(PLUS_OPERATION, _program);
  else if (strlen(_current_word) == 1 &&
           _current_word[0] == '-')
    parse_operation(MINUS_OPERATION, _program);
  else if (strlen(_current_word) == 1 &&
           _current_word[0] == '.')
    parse_operation(DUMP_OPERATION, _program);
  else
  {
    printf("ERROR: Can't parse unknown word %s.\n", _current_word);

    return false;
  }

  ++_program->operation_count;
  return true;
}

bool
load_operations
(
  struct program *_program
)
{
  _program->operation_count = 0;
  _program->stack_index = 0;
  _program->stack_count = 0;
  _program->number_to_push = 0;
  _program->stack_direction = STACK_ITERATION_DIRECTION_RIGHT;

  /* Iterates through the source code, and reads word by word, separated by characters that aren't
   * in the range of 33 and 126, which are human readable characters.
   *
   * https://www.asciitable.com/
   */
  char current_word[255];
  bool is_reading_word = false;
  bool is_reading_comment = false;
  long word_begin = 0, word_end = 0;
  for (long i = 0; i <= _program->source_file_size; ++i)
  {
    if ((_program->source[i] >= '\'' &&
         _program->source[i] <= '~' ))
    {
      if (!is_reading_comment &&
          _program->source[i] == '#')
      {
        is_reading_comment = true;

        continue;
      }
      else if (is_reading_comment &&
               _program->source[i] == '\n')
      {
        is_reading_comment = true;

        continue;
      }
      else if (!is_reading_word)
      {
        is_reading_word = true;
        word_begin = i;
      }

      continue;
    }

    if (is_reading_word)
    {
      is_reading_word = false;
      word_end = i;

      memset(current_word, '\0', 255);
      strncpy(current_word, &_program->source[word_begin], word_end - word_begin);

      if (!parse_current_word(_program, current_word))
        return false;
    }
  }

  return true;
}

int
main
(
  int    _argument_count,
  char **_argument_values
)
{
  struct program program_data;
  if (!parse_arguments(_argument_count, _argument_values, &program_data))
    return 1;
  if (!load_source_from_input_file(&program_data))
    return 1;
  if (!load_operations(&program_data))
    return 1;

  return 0;
}
