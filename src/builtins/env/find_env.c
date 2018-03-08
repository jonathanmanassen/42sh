/*
** find_env.c for minishell1 in /home/manass_j/rendu/PSU_2015_minishell1
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Sun Jan 24 16:54:52 2016 jonathan manassen
** Last update Sat Jun  4 17:35:55 2016 jonathan manassen
*/

#include <stdlib.h>
#include "my.h"
#include "./include/env.h"

char	**get_env(char **env)
{
  int	i;
  int	j;
  char	**my_env;

  i = 0;
  while (env[i])
    i = i + 1;
  if ((my_env = malloc(sizeof(char**) * (i + 3))) == NULL)
    exit(0);
  i = 0;
  while (env[i])
    {
      j = -1;
      if ((my_env[i] = malloc(sizeof(char*) *
			      (my_strlen(env[i]) + 1))) == NULL)
	exit(0);
      while (env[i][++j])
	my_env[i][j] = env[i][j];
      my_env[i][j] = '\0';
      i = i + 1;
    }
  my_env[i] = NULL;
  return (my_env);
}

int	find_line_in_env(char *str, char **env)
{
  int	i;
  int	j;
  int	k;

  i = 0;
  while (env[i])
    {
      j = 0;
      k = 0;
      while (str[j])
	{
	  if (str[j] == env[i][k])
	    k = k + 1;
	  j = j + 1;
	}
      if (k == j)
	return (i);
      i = i + 1;
    }
  return (-1);
}
