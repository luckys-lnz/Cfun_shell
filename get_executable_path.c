/*
 * File: get_executable_path.c
 * Author: Deantosh Daiddoh & Lucky Archibong
 */

#include "main.h"

/**
 * get_full_path - Gets the file path where the system command is located.
 * @command: The command provided.
 *
 * Return: A pointer to the comand file path (exists) or NULL (not found).
 */
char *get_full_path(char *command)
{
  char *path, *path_copy, *path_token, *file_path;
  struct stat buffer;
  char *command_copy;

  command_copy = strdup(command); /*creates a copy of the command*/
  /*check if file path is provided as command*/
  if (stat(command_copy, &buffer) == 0)
  {
    return (command_copy);
  }
  else
    free(command_copy); /*free mem*/
  /*get lists of path*/
  path = getenv("PATH");
  if (path)
  {
    path_copy = strdup(path);

    path_token = strtok(path_copy, ":");
    while (path_token != NULL)
    {
      /*get the file path*/
      file_path = create_path(path_token, command);
      /*check if the file path contains the command*/
      if (stat(file_path, &buffer) == 0)
      {
        free(path_copy);
        return (file_path);
      }
      else
      {
        free(file_path);
        path_token = strtok(NULL, ":");
      }
    }
    free(path_copy);
  }
  return (NULL); /*if cmd not found*/
}

/**
 * create_path - creates a full path to the command.
 * @token: The path token from the path env variable.
 * @command: The command to execute.
 *
 * Return: A pointer to the command full path.
 */
char *create_path(char *token, char *command)
{
  char *full_path;

  /*Allocate memory to the file path*/
  full_path = malloc(strlen(token) + strlen(command) + 2);

  /*create file_path*/
  strcpy(full_path, token);
  strcat(full_path, "/");
  strcat(full_path, command);
  strcat(full_path, "\0");

  return (full_path);
}