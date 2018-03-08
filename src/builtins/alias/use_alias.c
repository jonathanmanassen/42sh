/*
** use_alias.c for 42sh.c in /home/manass_j/rendu/PSU_2015_42sh
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Mon May 23 17:40:20 2016 jonathan manassen
** Last update Sat Jun  4 19:02:03 2016 jonathan manassen
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "./include/alias.h"

int	check_alias_cmd(char *alias, char c)
{
  int	i;

  i = 0;
  while (alias[i] && alias[i] != ' ')
    i = i + 1;
  if (c == ' ')
    i = i + 1;
  while (alias[i] && alias[i] != c)
    i = i + 1;
  if (check_str_space(alias, i) == 1)
    return (-1);
  return (1);
}

int	check_correspondance(char *str, char *alias)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  while (str[i] && str[i] == ' ')
    i = i + 1;
  while (str[i] && alias[j])
    {
      if (str[i] != alias[j])
	return (-1);
      i = i + 1;
      j = j + 1;
    }
  if (alias[j] != '\0')
    return (-1);
  if (str[i] != '\0' && str[i] != ' ')
    return (-1);
  return (i);
}

char	*turn_str_into_alias(char **alias, char *str, int *l, int i)
{
  int	j;
  int	k;
  char	*tmp;

  while (alias[i] != NULL)
    {
      if ((k = check_correspondance(str, alias[i])) != -1 && *l != i)
	{
	  j = my_strlen(alias[i + 1]) + my_strlen(str) - k + 1;
	  if ((tmp = malloc(sizeof(char*) * j)) == NULL)
	    exit(0);
	  j = -1;
	  while (alias[i + 1][++j])
	    tmp[j] = alias[i + 1][j];
	  while (str[k])
	    tmp[j++] = str[k++];
	  tmp[j] = '\0';
	  free(str);
	  *l = i;
	  return (tmp);
	}
      i = i + 2;
    }
  return (str);
}

char	**add_alias(char **alias, char *str)
{
  char	*tmp;
  char	*a;
  int	j;

  if (check_alias_cmd(str, ' ') == -1)
    return (alias);
  j = -1;
  if ((tmp = malloc(sizeof(char*) * (my_strlen(str) + 1))) == NULL)
    exit(0);
  while (str[++j])
    tmp[j] = str[j];
  tmp[j] = '\0';
  tmp = take_away_alias(tmp);
  a = alias_short(tmp, ' ');
  tmp = alias_long(tmp, ' ');
  alias = realloc_alias(alias, a);
  alias = realloc_alias(alias, tmp);
  change_alias_file(alias);
  free(a);
  free(tmp);
  return (alias);
}

char	**launch_alias(char *str, char **alias)
{
  int	i;
  int	j;

  if ((j = check_builtin(str, "alias")) != -1)
    {
      i = 0;
      if (check_str_space(str, j) == 1)
	show_alias(alias);
      else
	{
	  if ((i = check_change_alias(str, alias)) != -1)
	    alias = change_alias(alias, str, i);
	  else
	    alias = add_alias(alias, str);
	}
    }
  return (alias);
}
