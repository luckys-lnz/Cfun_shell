/*
 * File: execute_command.c
 * Author: Deantosh Daiddoh & Lucky Archibong
 */

#include "main.h"

/**
 * execute_builtin_command - Executes commands builtin
 *				to the program.
 * @argv: The list of arguments used by the command.
 *
 * Return: 0 (success) and 1 (fails).
 */
int execute_builtin_command(char **argv)
{
  /*declare variables*/
  int index, builtin_len, status, result;
  char *command = argv[0];
  builtin_s cmd_list[] = {
      {"exit", exit_shell},
      {"env", print_env},
      {NULL, NULL}};

  /*check if command provided exists*/
  if (command == NULL)
    return (1);

  /*get len of the cmd_list*/
  builtin_len = get_builtin_len(cmd_list);
  for (index = 0; index < builtin_len; index++)
  {
    status = strcmp(cmd_list[index].name, command);
    if (status == 0)
    {
      /*execute command*/
      result = cmd_list[index].func(argv);
      return (result);
    }
  }
  return (1);
}

/**
 * get_builtin_len - Gets the number of items in a list.
 * @cmd_list: The array of commands.
 *
 * Return: The length of the list or 0 (none);
 */
int get_builtin_len(builtin_s cmd_list[])
{
  /*declare variable*/
  int index = 0;

  while (cmd_list[index].name != NULL)
    index++;

  return (index);
}

/**
 * execute_external_command - Executes system commands.
 * @argv: The list of arguments used by the command.
 *
 * Return: 0 (success) or 1 (fails).
 */
int execute_external_command(char **argv)
{
  char *command = NULL, *full_command = NULL;
  int status;
  pid_t pid;

  if (argv)
  {
    command = argv[0];
    full_command = get_full_path(command);

    if (full_command)
    {
      /*create a child process*/
      pid = fork();

      if (pid == 0)
      {
        if (execve(full_command, argv, NULL) == -1)
          return (1);
      }
      wait(&status);
      free(full_command); /*free memory*/
    }
  }
  return (0);
}