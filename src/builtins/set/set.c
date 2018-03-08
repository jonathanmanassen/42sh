/*
** set.c for 42sh in /home/manass_j/rendu/PSU_2015_42sh
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Fri Jun  3 17:30:15 2016 jonathan manassen
** Last update Sat Jun  4 17:36:25 2016 jonathan manassen
*/

#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "./include/set.h"

char	*get_other_str(char *str)
{
  char	*tmp;
  int	i;

  if (str == NULL)
    {
      if ((tmp = malloc(sizeof(char*) * 1)) == NULL)
	exit(0);
      tmp[0] = '\0';
      return (tmp);
    }
  if ((tmp = malloc(sizeof(char*) * (my_strlen(str) + 1))) == NULL)
    exit(0);
  i = -1;
  while (str[++i])
    tmp[i] = str[i];
  tmp[i] = '\0';
  return (tmp);
}

char	**get_change_set(char *str, int i, int j, int k)
{
  char	**change_set;

  if ((change_set = malloc(sizeof(char**) * 3)) == NULL)
    exit(0);
  while (str[i] == ' ')
    i = i + 1;
  j = i;
  while (str[i] && str[i] != '=')
    i = i + 1;
  if ((change_set[0] = malloc(sizeof(char*) * (i - j + 1))) == NULL)
    exit(0);
  while (j < i)
    change_set[0][k++] = str[j++];
  change_set[0][k] = '\0';
  while (str[++i]);
  if ((change_set[1] = malloc(sizeof(char*) * (i - j + 1))) == NULL)
    exit(0);
  k = -1;
  while (++j < i)
    change_set[1][++k] = str[j];
  change_set[1][k + 1] = '\0';
  change_set[2] = NULL;
  return (change_set);
}

char	**change_set_f(char **set, char **change_set)
{
  int	i;

  i = 0;
  while (set[i] != NULL)
    i = i + 1;
  set = my_realloc_double_array(set, 0, 0);
  set = my_realloc_double_array(set, 0, 0);
  set[i] = get_other_str(change_set[0]);
  set[i + 1] = get_other_str(change_set[1]);
  return (set);
}

char	**launch_set(char *str, char **set, int i, int *work)
{
  char	**change_set;

  if ((i = check_builtin(str, "set")) != -1 &&
      check_builtin(str, "setenv") == -1)
    {
      if (check_str_space(str, i) != 1)
	{
	  if (check_alphanumeric(str, i - 1, "set", '=') == -1)
	    {
	      *work = 1;
	      return (set);
	    }
	  change_set = get_change_set(str, i, 0, 0);
	  if ((i = find_line_in_set(change_set[0], set)) != -1)
	    {
	      free(set[i + 1]);
	      set[i + 1] = get_other_str(change_set[1]);
	      return (set);
	    }
	  set = change_set_f(set, change_set);
	}
      else
	show_alias(set);
    }
  return (set);
}

char	**launch_unset(char *str, char **set, int *work)
{
  int	i;

  if (check_builtin(str, "unsetenv") == -1)
    {
      if ((i = check_builtin(str, "unset")) != -1 &&
	  check_str_space(str, i) == 1)
	{
	  my_printf("unset: Too few arguments.\n");
	  *work = 1;
	  return (set);
	}
      if (check_builtin(str, "unset") != -1)
	set = launch_unalias(str, set, 1, work);
    }
  return (set);
}
