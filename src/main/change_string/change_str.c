/*
** change_str.c for 42sh in /home/manass_j/rendu/PSU_2015_42sh
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Fri Jun  3 16:54:35 2016 jonathan manassen
** Last update Sun Jun  5 22:14:48 2016 jonathan manassen
*/

#include <stdlib.h>
#include "./include/change_string.h"
#include "my.h"

int	find_line_in_set(char *str, char **set)
{
  int	i;

  i = 0;
  while (set[i])
    {
      if (check_builtin(str, set[i]) != -1)
	return (i);
      i = i + 2;
    }
  return (-1);
}

char	*str_middle_realloc(char *str, char *env, int l[2], int k)
{
  char	*tmp;
  int	i;
  int	j;
  int	s;

  s = l[1] - 1;
  j = 0;
  if (k == 0)
    while (env[j] && env[j] != '=')
      j = j + 1;
  if (k == 0)
    j = j + 1;
  i = my_strlen(str) + s - l[0] + my_strlen(env) - j + 1;
  if ((tmp = malloc(sizeof(char*) * i)) == NULL)
    exit(0);
  i = -1;
  while (++i < s)
    tmp[i] = str[i];
  while (env[j])
    tmp[i++] = env[j++];
  while (str[l[0]])
    tmp[i++] = str[l[0]++];
  tmp[i] = '\0';
  free(str);
  return (tmp);
}

int	launch_change_str_env_variable(char *tmp, char **env, char **set)
{
  int	k;

  if ((k = find_line_in_env(tmp, env)) == -1)
    {
      if ((k = find_line_in_set(tmp, set)) == -1)
	{
	  my_fprintf(2, "%s: Undefined variable.\n", tmp);
	  free(tmp);
	  return (-1);
	}
      else
	return (1);
    }
  return (0);
}

char	*change_env_variable(char *str, int i, char **env, char **set)
{
  int	j[2];
  int	k;
  char	*tmp;

  j[0] = j[1] = ++i;
  while (str[i] && str[i] != ' ' && str[i] != ';' && str[i] != '|' &&
	 str[i] != '&' && str[i] != '$' && str[i] != '=')
    i = i + 1;
  if ((tmp = malloc(sizeof(char*) * (i - j[0] + 1))) == NULL)
    exit(0);
  k = 0;
  while (j[0] < i)
    tmp[k++] = str[j[0]++];
  tmp[k] = '\0';
  if ((k = launch_change_str_env_variable(tmp, env, set)) == -1)
    return (NULL);
  if (k == 1)
    str = str_middle_realloc(str, set[find_line_in_set(tmp, set) + 1], j, 1);
  else
    str = str_middle_realloc(str, env[find_line_in_env(tmp, env)], j, 0);
  free(tmp);
  return (str);
}

char	*change_special_str(char *str, char **env, t_shrc *shrc, int *work)
{
  int	i;

  i = -1;
  while (str[++i])
    if (str[i] == '$' && str[i + 1] != '\0')
      if ((str = change_env_variable(str, i, env, shrc->set)) == NULL)
	{
	  *work = 1;
	  return (NULL);
	}
  return (str);
}
