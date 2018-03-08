/*
** delete_env.c for minishell1 in /home/manass_j/rendu/PSU_2015_minishell1
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Thu Jan 21 15:20:39 2016 jonathan manassen
** Last update Sat Jun  4 17:35:50 2016 jonathan manassen
*/

#include <stdlib.h>
#include "my.h"
#include "./include/env.h"

char	**get_name_tab(char **name, char *str, int i, int j)
{
  int	k;
  int	l;

  k = 0;
  j = i + 1;
  while (str[i])
    {
      l = 0;
      while (str[i++] == ' ')
	j = i;
      while (str[i] != ' ' && str[i] != '\0')
	i = i + 1;
      if ((name[k] = malloc(sizeof(char*) * (i - j + 1))) == NULL)
	exit(0);
      while (j < i)
	{
	  name[k][l] = str[j];
	  j = j + 1;
	  l = l + 1;
	}
      name[k][l] = '\0';
      k = k + 1;
    }
  return (name);
}

char	**get_name(char *str, int i)
{
  int	k;
  int	j;
  char	**name;

  j = 0;
  if (str[i] != '\0')
    {
      while (str[i] == ' ' && str[i])
	i = i + 1;
      i = i - 1;
      k = i;
      while (str[++i])
	if (str[i] == ' ' && str[i + 1] != ' ' && str[i + 1] != '\0')
	  j = j + 1;
      if (str[0] == ':' && str[1] != ':')
	j = j - 1;
      if ((name = malloc(sizeof(char**) * (j + 2))) == NULL)
	exit(0);
      name = get_name_tab(name, str, k, 0);
      name[j + 1] = NULL;
    }
  return (name);
}

char	**malloc_tmp(char **tmp, char **env, int j, int l)
{
  int	k;

  k = 0;
  if (env[j] != NULL)
    {
      while (env[j][k])
	k = k + 1;
      if ((tmp[l] = malloc(sizeof(char*) * (k + 1))) == NULL)
	exit(0);
    }
  k = -1;
  if (env[j] != NULL)
    {
      while (env[j][++k])
	tmp[l][k] = env[j][k];
      free(env[j]);
      tmp[l][k] = '\0';
    }
  return (tmp);
}

char	**delete_env_line(char **env, int i, int j, int k)
{
  char	**tmp;
  int	l;

  while (env[j])
    j = j + 1;
  k = j;
  if ((tmp = malloc(sizeof(char**) * j)) == NULL)
    exit(0);
  j = -1;
  l = 0;
  if (env[j + 1] != NULL)
    while (k != j && env[++j] != NULL)
      {
	if (j == i)
	  free(env[j]);
	if (j == i)
	  j = j + 1;
	if (k != j)
	  tmp = malloc_tmp(tmp, env, j, l);
	if (k != j)
	  l = l + 1;
      }
  free(env);
  tmp[l] = NULL;
  return (tmp);
}

char	**launch_unsetenv(char *str, char **env, int *work)
{
  char	**name;
  int	i;
  int	j;
  int	k;

  j = -1;
  if ((i = check_builtin(str, "unsetenv") != -1) &&
      check_str_space(str, i) == 1)
    {
      *work = 1;
      my_printf("unsetenv: Too few arguments.\n");
      return (env);
    }
  if ((i = check_builtin(str, "unsetenv")) != -1)
    {
      name = get_name(str, i);
      while (name[++j])
	{
	  if ((k = find_line_in_env(name[j], env)) != -1)
	    env = delete_env_line(env, k, 0, 0);
	  free(name[j]);
	}
      free(name);
    }
  return (env);
}
