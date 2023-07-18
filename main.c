/*
 * File: main.c
 * Author: Deantosh Daiddoh & Lucky Archibong
 */

#include "main.h"

/**
 * main - Entry point.
 *
 * Return: 0 Always (success);
 */
int main(void)
{
  char **argv;
  const char *delim = " \n";
  char *str = NULL, *str_copy;
  size_t n = 0;
  ssize_t n_bytes;
  int num_tokens, exec_status;

  while (1)
  {
    if (isatty(STDIN_FILENO))
      printf("%s ", PROMPT);
    /*read from stdin stream*/
    n_bytes = getline(&str, &n, stdin);
    if (n_bytes == -1)
    {
      free(str);
      printf("\n");
      return (0);
    }
    str_copy = malloc(sizeof(char) * (n_bytes + 1));
    if (str_copy == NULL)
    {
      perror("Memory allocation failed");
      return (-1);
    }
    /*create a copy of str*/
    strcpy(str_copy, str);

    num_tokens = get_token(str, delim);
    argv = create_av(str_copy, num_tokens, delim); /*args list*/

    /*free memory after use*/
    free(str_copy);

    /*pass argv to the execute command functions*/
    exec_status = command_parser(argv);
    if (exec_status == 2) /*exit_shell*/
    {
      free(str);
      return (0);
    }
  }
  return (0);
}

/**
 * get_token - Gets the number of tokens in a string
 * @str: String to tokenize.
 * @delim: Character used to separate the tokens.
 *
 * Return: The number of tokens.
 */
int get_token(char *str, const char *delim)
{
  char *token;
  int num_tokens = 0;

  token = strtok(str, delim);
  while (token != NULL)
  {
    num_tokens++;
    token = strtok(NULL, delim);
  }
  num_tokens++;

  return (num_tokens);
}

/**
 * create_av - Converts a string into an array arguments.
 * @str: The string to convert.
 * @tokens: The number of string tokens.
 * @delim: The character used to separate arguments in a string.
 *
 * Return: A pointer to the allocated mem.
 */
char **create_av(char *str, int tokens, const char *delim)
{
  char **argv;
  char *token;
  int index;

  /*allocate mem for list of tokens*/
  argv = malloc(sizeof(char *) * tokens);

  token = strtok(str, delim);
  for (index = 0; token != NULL; index++)
  {
    /*allocate memory for each token*/
    argv[index] = malloc(sizeof(char) * (strlen(token) + 1));
    strcpy(argv[index], token);
    token = strtok(NULL, delim);
  }
  argv[index] = NULL;
  return (argv);
}