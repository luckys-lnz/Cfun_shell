/*
 * File: env.c
 * Author: Deantosh Daiddoh & Lucky Archibong
 */

#include "main.h"

/**
 * print_env - Prints current environment.
 * @argv: A list of arguments to pass to function.
 *
 * Return: 0 (Success).
 */
int print_env(char **argv)
{
  int index;
  size_t nbyte;

  (void)argv;

  for (index = 0; environ[index]; index++)
  {
    nbyte = strlen(environ[index]);
    write(STDOUT_FILENO, environ[index], nbyte);
    write(STDOUT_FILENO, "\n", 1);
  }
  return (0);
}