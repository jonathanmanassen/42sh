/*
** get_args.c for minishell1 in /home/manass_j/rendu/PSU_2015_minishell1
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Fri Jan 15 13:01:06 2016 jonathan manassen
** Last update Sat Jun  4 17:36:34 2016 jonathan manassen
*/

#include <stdlib.h>
#include "my.h"
#include "./include/get_execute.h"

int	check_str_space(char *str, int i)
{
  while (str[i] != '\0')
    {
      if (str[i] != ' ')
	return (0);
      i = i + 1;
    }
  return (1);
}

char	**get_command_tab(char **exe, char *str, int k, int j)
{
  int	i;
  int	l;

  i = 0;
  while (str[i])
    {
      l = 0;
      if (check_str_space(str, i) == 1)
	return (exe);
      while (str[i++] == ' ')
	j = i;
      while (str[i] != ' ' && str[i] != '\0')
	i = i + 1;
      if ((exe[k] = malloc(sizeof(char*) * (i - j + 1))) == NULL)
	exit(0);
      while (j < i)
	exe[k][l++] = str[j++];
      exe[k][l] = '\0';
      k = k + 1;
    }
  return (exe);
}

char	**get_command(char *str)
{
  int	i;
  int	j;
  char	**exe;

  i = -1;
  j = 0;
  if (str == NULL || str[0] == '\0')
    return (NULL);
  while (str[++i])
    if (str[i] == ' ' && str[i + 1] != ' ' && str[i + 1] != '\0')
      j = j + 1;
  if (str[0] == ' ')
    j = j - 1;
  if ((exe = malloc(sizeof(char**) * (j + 2))) == NULL)
    exit(0);
  exe = get_command_tab(exe, str, 0, 0);
  exe[j + 1] = NULL;
  return (exe);
}

char	**get_path_tab(char **path, char *str, int k, int j)
{
  int	i;
  int	l;

  i = 0;
  while (str[i] && str[i] != '=')
    i = i + 1;
  while (str[i])
    {
      l = 0;
      while (str[++i] && str[i] == ':');
      j = i;
      while (str[i] != ':' && str[i] != '\0')
	i = i + 1;
      if (i != j)
	{
	  ((path[k] = malloc(sizeof(char*) * (i - j + 1))) == NULL) ? exit(0) : 0;
	  while (j < i)
	    path[k][l++] = str[j++];
	  path[k][l] = '\0';
	  k = k + 1;
	}
    }
  path[k] = NULL;
  return (path);
}

char	**get_path(char *str)
{
  int	i;
  int	j;
  char	**path;

  j = 0;
  i = -1;
  while (++i <= 5)
    if (str[i] == '\0')
      return (NULL);
  i = -1;
  while (str[++i])
    if (str[i] == ':' && str[i + 1] != ':' && str[i + 1] != '\0')
      j = j + 1;
  if (str[5] == ':')
    j = j - 1;
  if ((path = malloc(sizeof(char**) * (j + 2))) == NULL)
    exit(0);
  path = get_path_tab(path, str, 0, 0);
  return (path);
}
