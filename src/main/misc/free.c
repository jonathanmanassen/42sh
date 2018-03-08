/*
** free.c for minishell1 in /home/manass_j/rendu/PSU_2015_minishell1
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Wed Jan 20 15:04:45 2016 jonathan manassen
** Last update Sun Jun  5 20:15:37 2016 jonathan manassen
*/

#include <stdlib.h>
#include "my.h"
#include "./include/misc.h"

void	free_functions(char **exe, char **path, int j)
{
  int	i;

  if (path != NULL)
    {
      i = -1;
      while (path[++i])
	free(path[i]);
      free(path);
    }
  i = -1;
  while (exe[++i])
    free(exe[i]);
  free(exe);
  if (j == 1)
    exit(0);
}

void	free_my_env(char **env, int j)
{
  int	i;

  i = 0;
  while (env[i] != NULL)
    {
      free(env[i]);
      i = i + 1;
    }
  free(env);
  if (j == -1)
    exit(0);
}
