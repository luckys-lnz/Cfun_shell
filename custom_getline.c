#include "main.h"
#define BUFFER_SIZE 120
/**
 *custom_getline - Reads input from stream
 *@_lineptr: Stores the input to BUFFER_SIZE
 *@stream: where input is Read
 *@n: _lineptr size
 */

ssize_t custom_getline(char **_lineptr, size_t *n, FILE *stream)
{
  static size_t input_pos = 0;
  ssize_t ret_val;
  char cur_char = 'x', *input_buffer;
  int read_result;

  /*Flush the stream if it's the first call or return -1 if already in progress */
  if (input_pos == 0)
  {
    fflush(stream);
  }
  else
  {
    return (-1);
  }

  input_pos = 0;

  input_buffer = malloc(sizeof(char) * BUFFER_SIZE);
  if (!input_buffer)
  {
    return (-1); /*Return -1 if memory allocation fails */
  }

  while (cur_char != '\n')
  {
    read_result = fgetc(stream);
    if (read_result == -1 || (read_result == 0 && input_pos == 0))
    {
      free(input_buffer);
      return (-1); /*Return -1 on error or end of file */
    }

    if (read_result == 0 && input_pos != 0)
    {
      input_pos++;
      break; /*Break loop if end of file is reached */
    }

    if (input_pos >= BUFFER_SIZE)
    {
      char *new_buffer = realloc(input_buffer, input_pos + 1);
      if (new_buffer == NULL)
      {
        free(input_buffer);
        return (-1); /*Return -1 if memory reallocation fails */
      }

      input_buffer = new_buffer;
    }

    cur_char = (char)read_result;
    input_buffer[input_pos] = cur_char;
    input_pos++;
  }

  input_buffer[input_pos] = '\0';

  if (*_lineptr == NULL || *n < input_pos)
  {
    /*Allocate new memory for _lineptr */
    *n = input_pos;
    *_lineptr = input_buffer;
  }
  else
  {
    strcpy(*_lineptr, input_buffer);
    free(input_buffer); /*Reuse existing memory for _lineptr and free input_buffer */
  }

  ret_val = input_pos;
  if (read_result != 0)
  {
    input_pos = 0;
  }

  return (ret_val);
}