/*
 * File: memory.c
 * Author: Lucky Archibong & Deantosh Daiddoh
 */

#include "main.h"

/**
 * free_pp - frees list of arguments;
 * @pp: list of arguments.
 */
void free_pp(char **pp)
{
  char **a = pp;

  if (!pp)
    return;
  while (*pp)
    free(*pp++);
  free(a);
}