/*
 * Authors: Deantosh Daiddoh & Lucky Archibong.
 * File: command_args_parser.c
 */

#include "main.h"

/**
 * command_parser - Passes the argument list to builtin
 *                  and external execute command functions.
 * @argv: The argument list.
 *
 * Return: 0 Always (success) or 2 (exit shell).
 */
int command_parser(char **argv)
{
  /*declare variables*/
  int exec_status;

  /*execute command*/
  exec_status = execute_builtin_command(argv); /*execute builtin cmd*/
  if (exec_status == 0)                        /*success*/
  {
    free_pp(argv); /*free memory allocated*/
    return (0);
  }
  else if (exec_status == 2) /*exit is success*/
  {
    free_pp(argv);
    return (2);
  }
  else
  {
    exec_status = execute_external_command(argv); /*execute system command*/
    if (exec_status == 0)                         /*success*/
    {
      free_pp(argv); /*free memory allocated*/
      return (0);
    }
    else
    {
      /*command does not exists*/
      free_pp(argv); /*free--argv*/
    }
  }
  return (0);
}