/*
** change_env.c for minishell1 in /home/manass_j/rendu/PSU_2015_minishell1
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Mon Jan 18 16:02:57 2016 jonathan manassen
** Last update Sat Jun  4 17:35:41 2016 jonathan manassen
*/

#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "./include/env.h"

extern int	leave;

char	**my_realloc_double_array(char **env, int j, int k)
{
  char	**tmp;

  while (env[j])
    j = j + 1;
  if ((tmp = malloc(sizeof(char**) * (j + 2))) == NULL)
    exit(0);
  j = 0;
  while (env[j])
    {
      k = 0;
      while (env[j][k])
	k = k + 1;
      if ((tmp[j] = malloc(sizeof(char*) * (k + 1))) == NULL)
	exit(0);
      k = -1;
      while (env[j][++k])
	tmp[j][k] = env[j][k];
      tmp[j][k] = '\0';
      free(env[j]);
      j = j + 1;
    }
  free(env);
  tmp[j] = NULL;
  return (tmp);
}

char	**change_env(char *str, char **env, int i, int j)
{
  int	k;

  env = check_realloc(env, j);
  if (j == -1)
    while (env[++j])
      j = j;
  env = malloc_env(env, str, i, j);
  k = 0;
  while (str[i])
    {
      if (str[i] == ' ' && check_str_space(str, i) == 0)
	env[j][k++] = '=';
      if (str[i] == ' ' && check_str_space(str, i++) == 0)
	while (str[i] == ' ')
	  i = i + 1;
      if ((check_str_space(str, i)) == 1)
	env[j][k] = '\0';
      if ((check_str_space(str, i)) == 1)
	return (env);
      else
	env[j][k++] = str[i++];
    }
  env[j][k] = '\0';
  return (env);
}

char	**change_env_no_equal(char *str, char **env, int i, int j)
{
  int	k;

  k = 0;
  if (j == -1)
    {
      while (env[++j])
	j = j;
      env = my_realloc_double_array(env, 0, 0);
      env[j + 1] = NULL;
    }
  else
    free(env[j]);
  if ((env[j] = malloc(sizeof(char*) * ((my_strlen(str) - i) + 2))) == NULL)
    exit(0);
  while (str[i] && str[i] != ' ')
    env[j][k++] = str[i++];
  env[j][k] = '=';
  env[j][k + 1] = '\0';
  return (env);
}

char	**launch_setenv(char *str, char **env, int i, int *work)
{
  char	*name;
  int	j;
  int	k;

  if ((i = check_builtin(str, "setenv")) != -1)
    {
      if (check_correct_change(str, i + 1, env, 0) == -1)
	{
	  *work = 1;
	  return (env);
	}
      while (str[++i] && str[i] == ' ');
      j = i;
      while (str[i] && str[i] != ' ')
	i = i + 1;
      name = get_line_name(str, j, i);
      j = i - j;
      k = find_line_in_env(name, env);
      if (check_str_space(str, i) == 1)
	env = change_env_no_equal(str, env, i - j, k);
      else
	env = change_env(str, env, i - j, k);
      free(name);
    }
  return (env);
}
